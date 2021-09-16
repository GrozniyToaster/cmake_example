

#include "lab24_struct.h"

#define ll long long


void print_token( token a )
{
    switch ( a.type )
    {
    case T_OPERATOR:
        switch ( a.op )
        {
        case O_ADD:
            printf("+ ");
            break;

            case O_MINUS:
            printf("- ");
            break;

            case O_PROD:
            printf("* ");
            break;
        
            case O_DIV:
            printf("/ ");
            break;

            case O_EXP:
            printf("^ ");
            break;

            case O_UN_MINUS:
            printf("~ ");
            break;
        
            
        }
        break;
    
    case T_BRACKET:
        switch ( a.br )
        {
        case BR_BEGIN:
            printf("( ");
            break;
        
        case BR_END:
            printf(")");
            break;
        }
        break;
    
    case T_CONSTANT:
        printf("%lld ", a.const_ch);
        break;

    case T_VARIABLE:
        printf("%s ", a.variable);
        break;
    break;

    default:
        printf("__err__");
    }
    
}


void printerr ( enum errors a )
{
    switch ( a )
    {
    case ERR_MEM:
        fprintf(stderr, "not enough memory\n");
        break;
    
    case ERR_TOK:
        fprintf(stderr, "not valid token\n");
        break;

    case ERR_EXPRES:
    fprintf(stderr, "not valid expression\n");
    break;
    }
    _Exit( a );
}
