#include "global.h"
char lexbuf[BSIZE];
int lineno = 1;
int tokenval = NONE;

int lexan() {
    int t;
    while (1) {
        t = getchar();
        if (t == ' ' || t == '\t');
        else if (t == '\n')
            lineno = lineno + 1;
        else if (isdigit(t)) {
            ungetc(t, stdin);
            scanf("%d", &tokenval);
            if (tokenval > 32767 && tokenval <= 2147483647) {
                return INT32;
            } else if (tokenval > 127 && tokenval <= 32767) {
                return INT16;
            } else if (tokenval >= 0 && tokenval <= 127)
                return INT8;
        } else if (isalpha(t) || t == '_') {
            int p, b = 0;
            while (isalnum(t) || t == '_') {
                lexbuf[b] = t;
                t = getchar();
                b = b + 1;
                if (b >= BSIZE)
                    error("compiler error");
            }
            lexbuf[b] = EOS;
            if (t != EOF)
                ungetc(t, stdin);
            p = lookup(lexbuf);
            if (p == 0) {
                p = insert(lexbuf, ID);
            } if (p >= 52) {
                tokenval = p - 49;
            } else if (p > 0 && p < 52) {
                tokenval = NONE;
            }
            return symtable[p].token;
        } else if (t == EOF)
            return DONE;
        else {
            tokenval = NONE;
            return t;
        }
    }
}
