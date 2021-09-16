#pragma once
#ifndef ll
#define ll long long
#endif

#ifndef ull
#define ull unsigned long long
#endif

#include <stdlib.h>
#include "lab24_struct.h"


typedef struct{
    list_el * root;
}tree_token;

typedef list_el* treeptr;

void tree_init( tree_token * a );

void print_tree (tree_token *a );

void print_tree_inside (list_el * a , ull level);

void print_expression( tree_token * a );

void print_expression_inside( treeptr  a );


void tree_destroy_inside( treeptr a );

void tree_destroy( tree_token * a);