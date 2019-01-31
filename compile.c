#include "javaclass.h"
#include "bytecode.h"
#include "global.h"

int returnlocation = 0;
int lookahead;
struct ClassFile cf;

int main()
{
    int index1, index2, index3;
    int label1, label2;
    init_ClassFile(&cf);
    cf.access = ACC_PUBLIC;
    cf.name = "Code";
    cf.field_count = 0;
    cf.method_count = 1;
    cf.methods = (struct MethodInfo*)malloc(cf.method_count * sizeof(struct MethodInfo));
    cf.methods[0].access = ACC_PUBLIC | ACC_STATIC;
    cf.methods[0].name = "main";
    cf.methods[0].descriptor = "([Ljava/lang/String;)V";
    cf.methods[0].max_stack = 127;
    cf.methods[0].max_locals = 127;
    init_code();
    emit(aload_0);
    emit(arraylength);
    emit2(newarray, T_INT);
    emit(astore_1);
    emit(iconst_0);
    emit(istore_2);
    label1 = pc;
    emit(iload_2);
    emit(aload_0);
    emit(arraylength);
    label2 = pc;
    emit3(if_icmpge, PAD);
    emit(aload_1);
    emit(iload_2);
    emit(aload_0);
    emit(iload_2);
    emit(aaload);
    index1 = constant_pool_add_Methodref(&cf, "java/lang/Integer", "parseInt", "(Ljava/lang/String;)I");
    emit3(invokestatic, index1);
    emit(iastore);
    emit32(iinc, 2, 1);
    emit3(goto_, label1 - pc);
    backpatch(label2, pc - label2);

    init();
    predictiveParser();
    backpatch(returnlocation, pc - returnlocation);

    index2 = constant_pool_add_Fieldref(&cf, "java/lang/System", "out", "Ljava/io/PrintStream;");
    emit3(getstatic, index2);
    emit(iload_2);
    index3 = constant_pool_add_Methodref(&cf, "java/io/PrintStream", "println", "(I)V");
    emit3(invokevirtual, index3);
    emit(return_);
    cf.methods[0].code_length = pc;
    cf.methods[0].code = copy_code();
    save_classFile(&cf);
    return 0;
}

void predictiveParser()
{
    lookahead = lexan();
    stmt();
}

void stmt()
{
    int previousToken;
	if(lookahead == '{'){
		match('{');
        opt_stmts();
        match('}');
	}
    else if (lookahead == ID){
		previousToken = tokenval;
        match(ID);
        match('=');
        expr();
        emit2(istore, previousToken);
		match(';');
	}
    else if (lookahead == IF){
		match(IF);
        match('(');
        expr();
	 	match(')');
		emit(dup);
		emit(istore_1);
        emit(iconst_0);
        int loc1 = pc;
        emit3(if_icmpeq, 1);   
        stmt();
        int loc2 = pc;
        emit3(goto_, 1);
        backpatch(loc1, pc - loc1);
        match(ELSE);
        stmt();
        backpatch(loc2, pc - loc2);
	}
	else if (lookahead == WHILE){
		int loc;
		match(WHILE);
        match('(');
        int test = pc;
        expr();
        emit(iconst_0);
        loc = pc;
        emit3(if_icmpeq, 0);
        match(')');
        stmt();
        emit3(goto_, test - pc);
        backpatch(loc, pc - loc);
	}
	else if (lookahead == RETURN){
		match(RETURN);
        expr();
        match(';');
        emit(istore_2);
        if (returnlocation == 0)
        {
            returnlocation = pc;
            emit3(goto_, 0);
        }
	}
    else{
        error("Error");
    }
}

void opt_stmts()
{
    if (lookahead == '{' || lookahead == ID||lookahead == IF || lookahead == WHILE || lookahead == RETURN || lookahead==ELSE) {
        stmt();
        opt_stmts();
    }
    else {
		
    }
}

void expr()
{
    term();
    moreterms();
}

void moreterms()
{
    if (lookahead == '+') {
        match('+');
        term();
        emit(iadd);
        moreterms();
    }
    else if (lookahead == '-') {
        match('-');
        term();
        emit(isub);
        moreterms();
    }
    else {

    }
}

void term()
{
    factor();
    morefactors();
}

void morefactors()
{
    if (lookahead == '*') {
        match('*');
        factor();
        emit(imul);
        morefactors();
    }
    else if (lookahead == '/') {
        match('/');
        factor();
        emit(idiv);
        morefactors();
    }
    if (lookahead == '%') {
        match('%');
        factor();
        emit(irem);
        morefactors();
    }
    else {
       
    }
}

void factor()
{
	int previousToken;
    if (lookahead == '(') {
        match('(');
        expr();
        match(')');
	}
	else if (lookahead == '-') {
        match('-');
        factor();
        emit(ineg);
	}
	else if (lookahead == INT8) {
		previousToken = tokenval;
		match(INT8);	
        emit2(bipush, previousToken);
	}
	else if (lookahead == INT16) {
		previousToken = tokenval;
		match(INT16);
        emit3(sipush, previousToken);
	}
	else if (lookahead == INT32) {
		previousToken = tokenval;
        match(INT32);
		emit2(ldc,constant_pool_add_Integer(&cf,previousToken));
	}
	else if (lookahead == ID) {
		previousToken = tokenval;
		match(ID);
        emit2(iload, previousToken);
	}
	else if (lookahead == ARG) {
        match(ARG);
        match('[');
		previousToken = tokenval;
        match(INT8);
        match(']');
		emit(aload_1);
        emit2(bipush, previousToken);
        emit(iaload);
	}
  	else{
        error("Error");
    }
}

void match(int t)
{
    if (lookahead == t) {
        lookahead = lexan();
    }
    else {
        error("Error");
    }
}
