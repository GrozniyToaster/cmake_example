


#include "tree_token.h"



#define ll long long



void tree_init( tree_token * a )
{
    a->root = NULL;
}


void print_tree_inside (list_el * a , ull level){
    
    printf( "( " );
    print_token( a->value );
    printf(") -- ");
    level += 1;
    if ( a->next == NULL )  { printf("||\n");    } else { print_tree_inside (a->next, level); }
    for ( ull t=level; t>0 ; t--  )
    {
        printf("\t");
    }
    printf("\\-"); 
    if ( a->prev == NULL )  { printf("||\n"); } else { print_tree_inside ( a->prev, level ); }


    

    
}

void print_tree (tree_token *a ){
    
    if ( a->root == NULL )
    {
        printf("\n");
        return;
    }
    printf("--------------------------------------------------------------------------------\n");
    print_tree_inside( a->root , 0 );
    printf("--------------------------------------------------------------------------------\n");
    
}


void print_expression_inside( treeptr  a )
{
    if ( a->value.type == T_OPERATOR ) printf("( ");
    if ( a->prev != NULL  ) print_expression_inside( a->prev );
    print_token( a->value );
    if ( a->next != NULL  ) print_expression_inside( a->next );
    if ( a->value.type == T_OPERATOR ) printf(") ");
}

void print_expression( tree_token * a )
{
    if ( a->root == NULL  ) return;
    print_expression_inside(  a->root );
    putchar('\n');
}


void tree_destroy_inside( treeptr a )
{
    if ( a->next != NULL ) tree_destroy_inside( a->next );
    if ( a->prev != NULL ) tree_destroy_inside( a->prev );
    free ( a );
}

void tree_destroy( tree_token * a)
{
    if ( a->root == NULL ) return;
    tree_destroy_inside( a->root );

}

