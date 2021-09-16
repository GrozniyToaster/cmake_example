

#include "stack_token.h"

#define ll long long











void stack_init( stack_list * a )
{
    a->first = NULL;
}

bool stack_is_empty( stack_list  * a )
{
    return a->first == NULL;
}

bool stack_push( stack_list * a , token to_add)
{
    list_el * new_el = malloc ( sizeof( list_el ) );
    if ( new_el == NULL ) return false;
    new_el->next = a->first;
    a->first = new_el;
    new_el->value = to_add;
    return true;
}

token stack_pop( stack_list * a )
{   
    token res;
    res.type = T_NOT_TOKEN;
    if ( a->first == NULL ) return res;
    res = a->first->value;
    list_el * to_free = a->first;
    a->first = a->first->next;
    free( to_free );
    return res;
}

token stack_top( stack_list * a )
{   
    token res;
    res.type = T_NOT_TOKEN;
    if ( a->first == NULL ) return res;
    return a->first->value;

}


void stack_destroy( stack_list * a )
{
    while ( a->first != NULL )
    {
        list_el * to_dell = a->first;
        a->first = a->first->next;
        free( to_dell );
    }
}
