#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define BSIZE 128
#define NONE -1
#define EOS '\0'
#define IF 256
#define ABSTRACT 257
#define ASSERT 258
#define BOOLEAN 259
#define BREAK 260
#define BYTE 261
#define CASE 262
#define CATCH 263
#define CHAR 264
#define CLASS 265
#define CONST 266
#define CONTINUE 267
#define DEFAULT 268
#define DO 269
#define DOUBLE 270
#define ELSE 271
#define ENUM 272
#define EXTENDS 273
#define FINAL 272
#define FINALLY 273
#define FLOAT 274
#define FOR 275
#define GOTO 276
#define IMPLEMENTS 277
#define IMPORT 278
#define INSTANCEOF 279
#define INT 280
#define INTERFACE 281
#define LONG 282
#define NATIVE 283
#define NEW 284
#define PACKAGE 285
#define PRIVATE 286
#define PROTECTED 287
#define PUBLIC 288
#define RETURN 289
#define SHORT 290
#define STATIC 291
#define STRICTFP 292
#define SUPER 293
#define SWITCH 294
#define THIS 295
#define VOID 296
#define WHILE 297
#define TRY 298
#define THROW 299
#define DONE 300
#define ID 301
#define INT8 302
#define INT16 303
#define INT32 304
#define ARG 305
#define NUM 306
#define OPR 307

//function declarations
void init();
int lexan();
void error(char *);
int lookup(char s[]);
int insert(char s[], int tok);
void predictiveParser();
void stmt();
void opt_stmts();
void expr();
void moreterms();
void term();
void factor();
void morefactors();
void match(int t);

int tokenval;
int lineno;

struct entry {
    char *lexptr;
    int token;
};
struct entry symtable[100];
