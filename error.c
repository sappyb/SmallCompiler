//
// Created by sapbh on 2/2/2018.
//
#include "global.h"

void error(char *m)
{
    fprintf(stderr,"line %d: %s\n",lineno,m);
    exit(1);
}
