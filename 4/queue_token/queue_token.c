

#include "queue_token.h"

#define ll long long


void queue_init( queue_list * a )
{
    a->first = NULL;
    a->last = NULL;
}

bool queue_is_empty( queue_list * a )
{
    return a->first == NULL;
}

bool queue_push_back( queue_list * a, token to_add )
{
    list_el * new_el = malloc ( sizeof( list_el ) );
    if ( new_el == NULL ) return false;

    if ( a->last == NULL ) 
    {
        a->last = new_el;
        a->first = new_el;
    }
    else
    {
        a->last->next = new_el;
        a->last = new_el;
    }
    new_el->value = to_add;
    return true;
}

token queue_pop_front( queue_list * a )
{   
    token res;
    res.type = T_NOT_TOKEN;
    if (a->first == NULL ) return res;
    if ( a->first == a->last )
    {
        res = a->first->value;
        free ( a->first );
        a->first = NULL;
        a->last = NULL;
    }
    else
    {
        list_el* to_dell = a->first;
        res = a->first->value;
        a->first = a->first->next;
        free ( to_dell );
    }
    return res;
}

void queue_destroy( queue_list * a )
{
    if (a->first == NULL ) return ;
    list_el * to_dell;
    while ( a->first != a->last ) 
    {
        to_dell = a->first;
        a->first = a->first->next;
        free ( to_dell );
    }

    free (a->first);
    a->first = NULL;
    a->last = NULL;
}

void queue_print( queue_list * a )
{
    if ( a->first == NULL ) return;
    list_el * tmp = a->first;
    while ( tmp != a->last  )
    {
        print_token( tmp->value );
        tmp = tmp->next;
    }
    print_token( tmp->value );
    putchar('\n');
}

bool queue_cpy( queue_list * to,  queue_list * from )
{
    list_el* coping = from->first;
    list_el** where_copy = &(to->first);
    while ( coping != NULL )
    {
        list_el * copy = malloc ( sizeof( list_el ) );
        if (copy ==  NULL) return false;
        *copy = *coping;
        *where_copy = copy;
        where_copy = &((*where_copy)->next);
        coping = coping->next;

    }
    return true;
}