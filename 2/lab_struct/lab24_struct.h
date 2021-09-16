#pragma once
#ifndef ll
#define ll long long
#endif


#include <stdio.h>

enum errors {
    ERR_MEM = 1,
    ERR_EXPRES,
    ERR_TOK,
};


enum operator {
    O_ADD,
    O_MINUS,
    O_PROD,
    O_DIV,
    O_EXP,
    O_UN_MINUS,

};

enum bracket {
    BR_BEGIN,
    BR_END
};


enum type_token{
    T_NOT_TOKEN,
    T_OPERATOR,
    T_CONSTANT,
    T_VARIABLE,
    T_BRACKET,
};

typedef struct 
{   
    
    enum type_token type;
    enum operator op;
    ll const_ch;
    char variable[50];
    enum bracket br;


} token;

struct list_el
{
    token value;
    struct list_el * next;
    struct list_el * prev;
    
};

typedef struct list_el list_el;

void print_token( token a );

void printerr ( enum errors a );