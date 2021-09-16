#pragma once
#ifndef ll
#define ll long long
#endif


#include <stdlib.h>
#include <stdbool.h>
#include "lab24_struct.h"

typedef struct{

    list_el * first;
    
}stack_list;


void stack_init( stack_list * a );

bool stack_is_empty( stack_list  * a );

bool stack_push( stack_list * a , token to_add);

token stack_pop( stack_list * a );

token stack_top( stack_list * a );

void stack_destroy( stack_list * a );



