#include "global.h"
int main() {
    int lex;
    init();
    lex = lexan();
    while (lex != DONE) {
        if (lex <128){
            printf("<%c, %d>\n",lex, tokenval);
        }
        else if (lex == 301)
            printf("<%s,%d>\n","ID", tokenval);
        else if (lex == 305)
            printf("<%s,%d>\n","ARGS", tokenval);
        else if (lex == 302)
            printf("<%s,%d>\n","INT8", tokenval);
        else if (lex == 303)
            printf("<%s,%d>\n","INT16", tokenval);
        else if (lex == 304)
            printf("<%s,%d>\n","INT32", tokenval);
        lex = lexan();
    }
    return 0;
}