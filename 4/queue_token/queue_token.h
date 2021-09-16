#pragma once
#ifndef ll
#define ll long long
#endif


#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "lab24_struct.h"


typedef struct 
{
    list_el * first;
    list_el * last;
}queue_list;


void queue_init( queue_list * a );

bool queue_is_empty( queue_list * a );

bool queue_push_back( queue_list * a, token to_add );

token queue_pop_front( queue_list * a );

void queue_destroy( queue_list * a );

void queue_print( queue_list * a );

bool queue_cpy( queue_list * to,  queue_list * from );