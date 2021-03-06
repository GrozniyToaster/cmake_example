#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>


#define ll long long


#include "lab24_struct.h"
#include "stack_token.h"
#include "queue_token.h"
#include "tree_token.h"

#include "version.h" // will be generated by Cmake



token parse_token( char  ch , token * prev )
{
    token res;
    
    if( ch == '_' || ('a' <= ch  && ch <= 'z') ||  ('A' <= ch  && ch <= 'Z' ) )  
    {
        res.type = T_VARIABLE;
        ungetc( ch, stdin );
        char str[50];
        scanf( "%[_A-Za-z0-9]", str );
        strcpy( res.variable, str );
        
        *prev = res;
        return res;

    }
    if ( '0' <= ch && ch <= '9' ){
        res.type = T_CONSTANT;
        ungetc( ch, stdin );
        char str[50];
        scanf( "%[0-9]", str );
        res.const_ch = atoi( str );

        *prev = res;
        return res;

    }
    switch ( ch )
    {
    case '+':
        res.type = T_OPERATOR;
        res.op = O_ADD;
        break;
    
    case '-':
        res.type = T_OPERATOR;
        if ( prev->type == T_NOT_TOKEN ||  ( prev->type == T_BRACKET && prev->br == BR_BEGIN ) )
        {
            res.op = O_UN_MINUS;
        }else{
            res.op = O_MINUS;
        }
        break;

    case '*':
        res.type = T_OPERATOR;
        res.op = O_PROD;
        break;
    
    case '/':
        res.type = T_OPERATOR;
        res.op = O_DIV;
        break;
    
    case '^':
        res.type = T_OPERATOR;
        res.op = O_EXP;
        break;
    
    case '(':
        res.type = T_BRACKET;
        res.br = BR_BEGIN;
        break;
    
    case ')':
        res.type = T_BRACKET;
        res.br = BR_END;
        break;
    default:
        res.type = T_NOT_TOKEN;
    }

    *prev = res;
    return res;

}





void make_rev_poland( token tk, stack_list * st , queue_list * out  )
{

    switch ( tk.type )
    {
    case T_OPERATOR:
        //if ( tk.op == O_UN_MINUS ) return queue_push_back( out, tk );
        for( token to_queue = stack_top( st ); to_queue.op > tk.op && to_queue.type == T_OPERATOR; to_queue = stack_top( st ) )
        {
            stack_pop( st );
            if ( !queue_push_back( out, to_queue ) ) printerr( ERR_MEM );
        }
        if (! stack_push( st, tk )) printerr( ERR_MEM );
        break;

    case T_BRACKET:
        if ( tk.br == BR_BEGIN )
        {
            if (! stack_push( st, tk )) printerr( ERR_MEM );
            return;
        }
        else
        {
            
            for( token to_queue = stack_pop( st ); to_queue.type != T_BRACKET ; to_queue = stack_pop( st ) ){
                if ( to_queue.type == T_NOT_TOKEN ) printerr( ERR_EXPRES );
                if ( !queue_push_back( out, to_queue ) ) printerr( ERR_MEM );
            }
            
            
        }
        break;

    case T_NOT_TOKEN:
        printerr( ERR_TOK );

    default:
        if( !queue_push_back( out, tk ) ) printerr( ERR_MEM );
    
    }
    
}


void make_tree(  tree_token * tree, queue_list * rpn  )
{
    stack_list  tmp_st;
    
    stack_list * st = &tmp_st;
    stack_init( st );
    for( ; !queue_is_empty( rpn );  )
    {
        token tk = queue_pop_front( rpn );
        list_el * new_el;
        switch ( tk.type )
        {
        case T_CONSTANT:
            if ( (new_el= malloc( sizeof( list_el ) ) ) == NULL ) printerr( ERR_MEM );
            new_el->value = tk;
            new_el->prev = NULL;
            new_el->next = NULL;

            stack_push( st , tk );
            st->first->prev = new_el;

            break;

        case T_VARIABLE:
            if ( (new_el= malloc( sizeof( list_el ) ) ) == NULL ) printerr( ERR_MEM );
            new_el->value = tk;
            new_el->prev = NULL;
            new_el->next = NULL;

            if (!stack_push( st , tk )) printerr ( ERR_MEM );
            st->first->prev = new_el;

            break;

        case T_OPERATOR:
            if ( (new_el= malloc( sizeof( list_el ) ) ) == NULL ) printerr( ERR_MEM );
            new_el->value = tk;
            if ( st->first == NULL ) printerr( ERR_EXPRES );
            new_el->next = st->first->prev;
            stack_pop( st );
            if ( tk.op == O_UN_MINUS )
            {
                new_el->prev = NULL;
            }
            else
            {
                if ( st->first == NULL ) printerr( ERR_EXPRES );
                new_el->prev = st->first->prev;
                stack_pop( st );
            }
            if ( !stack_push( st , tk ) ) printerr( ERR_MEM );
            st->first->prev = new_el;
            break;

        
        default:
            printerr( ERR_EXPRES );
        }
    }
    if ( st->first == NULL ) printerr( ERR_EXPRES );
    if ( st->first->next != NULL ) printerr( ERR_EXPRES );
    tree->root = st->first->prev;
}


void find_prods( tree_token * tree, stack_list * prods )
{
    queue_list tmp;
    queue_init( &tmp );
    token tr;
    tr.type = T_NOT_TOKEN;
    if(!queue_push_back( &tmp, tr )) printerr( ERR_MEM );
    tmp.first->prev = tree->root;
    while( !queue_is_empty( &tmp ) )
    {
        if ( tmp.first->prev->value.type == T_OPERATOR && tmp.first->prev->value.op == O_PROD)        
        {
            if (!stack_push( prods, tr )) printerr ( ERR_MEM );
            prods->first->prev = tmp.first->prev;
        }
        if ( tmp.first->prev->prev != NULL  )
        {
            if(!queue_push_back( &tmp, tr )) printerr( ERR_MEM );
            tmp.last->prev = tmp.first->prev->prev;
        }
        if ( tmp.first->prev->next != NULL  )
        {
            if(!queue_push_back( &tmp, tr )) printerr( ERR_MEM );
            tmp.last->prev = tmp.first->prev->next;
        }
        queue_pop_front( &tmp );
    }

}

bool equal_tok( token a ,token b )
{
    if ( a.type == b.type )
    {
        switch ( a.type )
        {
        case T_VARIABLE:
            return ( strcmp( a.variable, b.variable ) == 0 );
            
        case T_CONSTANT:
            return ( a.const_ch == b.const_ch );

        case T_OPERATOR:
            return ( a.op == b.op );
        
        case T_BRACKET:
            return ( a.br == b.br );
        default:
            return false;
        }
    }
    
    return false;
}

bool equals( token a_minus,token minus_b, token f_plus, token plus_g )
{
    if ( equal_tok( a_minus, minus_b ) )
    {
        return (
                equal_tok( f_plus, plus_g ) &&
                equal_tok( a_minus , f_plus )
                );
    }
    else
    {
        return (
                !equal_tok( f_plus, plus_g ) &&
                ( equal_tok( a_minus, f_plus ) || equal_tok( a_minus, plus_g ) ) &&
                ( equal_tok( minus_b, f_plus ) || equal_tok( minus_b, plus_g ) )
                );
    }
}

void replace_prod( tree_token * tree, queue_list * ab )
{
    stack_list prods;
    stack_init( &prods );
    find_prods( tree, &prods );
    while ( ! stack_is_empty( &prods ) )
    {
        list_el * a = prods.first->prev->prev;
        list_el * b = prods.first->prev->next;
        list_el * add;
        list_el * min;
        list_el * a_;
        list_el * b_;

        
        if ( a->value.type != T_OPERATOR || b->value.type != T_OPERATOR ) { stack_pop( &prods ); continue; }
        if ( a->value.op!= O_ADD ) 
        {
            add = b;
        }
        else
        {
            add = a;
        }
        if ( b->value.op!= O_MINUS ) 
        {
            min = a;
        }
        else
        {
            min = b;
        }
        if ( add->value.op != O_ADD || min->value.op != O_MINUS ) { stack_pop( &prods ); continue; }
        a = min->prev;
        b = min->next;
        a_ = add->prev;
        b_= add->next;
        
        if ( (a->value.type != T_VARIABLE && a->value.type != T_CONSTANT) || ( b->value.type != T_VARIABLE && b->value.type != T_CONSTANT) )
        { 
            stack_pop( &prods );
            continue; 
        }

        if ( !equals( a->value, b->value , a_->value, b_->value ) )
        {
            stack_pop( &prods );
            continue; 
        }
        

        token true_a = a->value;
        token true_b = b->value;
        tree_destroy_inside( a );
        tree_destroy_inside( b );

        queue_list copy_ab;
        if (!queue_cpy( &copy_ab, ab )) printerr( ERR_MEM );
        tree_token rep;
        tree_init( &rep );
        make_tree( &rep, &copy_ab);

        prods.first->prev->value.op = O_MINUS;
        prods.first->prev->next = rep.root->next;
        prods.first->prev->prev = rep.root->prev;
        
        rep.root->next->prev->value = true_b;
        rep.root->prev->prev->value = true_a;

        free ( rep.root );

        stack_pop( &prods );
    }
    
}


int main (){
    
    printf("%s version %s \n",name_project , version);

    stack_list st;
    stack_init( &st );

    queue_list out_str;
    queue_init( &out_str );

    token prev;
    prev.type = T_NOT_TOKEN;
    char ch;

    printf( "Enter expression: \n\t" );

    while( (ch = getc( stdin )) != EOF )
    {

        if( ch==' ' || ch=='\t' || ch=='\r' ) continue;
        if ( ch=='\n' ) break;
        
        parse_token( ch, &prev );
        
        if( prev.type == T_NOT_TOKEN ) printerr( ERR_TOK );
        
        make_rev_poland( prev, &st, &out_str );

    }


    while( ! stack_is_empty( &st ) )
    {
        token tmp = stack_pop( &st );
        
        if ( tmp.type == T_BRACKET ) printerr( ERR_EXPRES );
        
        if ( ! queue_push_back( &out_str, tmp  ) ) printerr( ERR_MEM );
    }

    printf("Reverse polish natation:\n\t");
    queue_print( &out_str );

    tree_token tree;
    tree_init( &tree );

    stack_destroy( &st );
    make_tree( &tree, &out_str);


    queue_destroy( &out_str );

    printf("Tree of expression:\n");
    print_tree( &tree );

    queue_list ab;
    queue_init( &ab );
    prev.type = T_NOT_TOKEN;

    fclose( stdin );

    char to_func[]="a^2-b^2";
    for ( int i = 0; to_func[i] != '\0'; i++  )
    {
        parse_token( to_func[i], &prev );
        if ( prev.type == T_CONSTANT ) prev.const_ch =  to_func[i]-'0' ;
        make_rev_poland( prev, &st, &ab );

    }

    while( ! stack_is_empty( &st ) )
    {
        if ( ! queue_push_back( &ab, stack_pop( &st )  ) ) printerr( ERR_MEM );
    }




    replace_prod( &tree, &ab );

    printf("Tree of expression after replacing multiplications  ( a + b ) * ( a - b ) -> ( a\u00B2 - b\u00B2 ):\n");

    print_tree( &tree );

    printf("Expression after replacing:\n\t");

    print_expression( &tree );

    return 0;
}


