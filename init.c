//
// Created by sapbh on 2/2/2018.
//
#include "global.h"
struct entry keywords[] =
        {
                "if", IF,
                "else", ELSE,
                "abstract", ABSTRACT,
                "assert", ASSERT,
                "boolean", BOOLEAN,
                "break", BREAK,
                "byte", BYTE,
                "case", CASE,
                "catch", CATCH,
                "char", CHAR,
                "class", CLASS,
                "const", CONST,
                "continue", CONTINUE,
                "default", DEFAULT,
                "do", DO,
                "double", DOUBLE,
                "enum", ENUM,
                "extends", EXTENDS,
                "final", FINAL,
                "finally", FINALLY,
                "float", FLOAT,
                "for", FOR,
                "goto", GOTO,
                "implements", IMPLEMENTS,
                "import", IMPORT,
                "instanceof", INSTANCEOF,
                "int", INT,
                "interface", INTERFACE,
                "long", LONG,
                "native", NATIVE,
                "new", NEW,
                "package", PACKAGE,
                "private", PRIVATE,
                "protected", PROTECTED,
                "public", PUBLIC,
                "arg", ARG,
                "return", RETURN,
                "short", SHORT,
                "static", STATIC,
                "strictfp", STRICTFP,
                "super", SUPER,
                "switch", SWITCH,
                "this", THIS,
                "void", VOID,
                "while", WHILE,
                "try", TRY,
                "throw", THROW, "done", DONE,
                "id", ID,
                "int8", INT8,
                "int16", INT16,
                "int32", INT32,
                0, 0,
        };

void init() {
    //printf("inside insert\n");
    struct entry *p;

    for (p = keywords; p->token; p++) {
        insert(p->lexptr, p->token);
    }
}
