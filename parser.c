//
// parser.c ... 構文解析器
//
#include <stdio.h>
#include <string.h>
#include "base.h"
#include "tokenizer.h"
#include "tree.h"

static char *tok = NULL;

void init_parser(void) {
  tok = next_token();
}

Tree *parse_statement(void) {
  return make_name_tree("not_implemented");
}

Tree *parse_expression(void){
  // exp ->  NUMBER | NAME | ( if exp exp exp ) | (name exp*)
	Tree *tree;
  	if (is_name_token(tok)){ // NAME
		if (equal_token(tok, "exit")){
			error_exit("終了");
		}
    	tree = make_name_tree(tok);
    	tok = next_token();
  	} else if (is_number_token(tok)){ // NUMBER
		tree = make_number_tree(atoi(tok));
		tok = next_token();
  	} else if (equal_token(tok, "(")){ // (
		tree = make_list_tree();
		tok = next_token();
		
		if (equal_token(tok, "if")) { // (if exp exp exp)
			add_subtree(tree, parse_expression());
	  		int i;
	  		for (i = 0; i < 3; i++){
				add_subtree(tree, parse_expression());
	  		}
	  
	  		if (tok != NULL && equal_token(tok, ")")) {
				tok = next_token();
	  		} else 
				error_exit("syntax error: if文に')'が足りない。"); 
		} else if(! strcmp(tok, "data")){ // data 式
			add_subtree(tree, parse_expression());

			add_subtree(tree, parse_expression());

			if (tok != NULL && equal_token(tok, ")")) {
				tok = next_token();
			} else 
				error_exit("syntax error: data文に')'が足りない。");
		} else if(! strcmp(tok, "do")){ // do　文* 式
			add_subtree(tree, parse_expression());
			add_subtree(tree, parse_expression());

			while (tok != NULL && ! equal_token(tok, ")")) {
				add_subtree(tree, parse_expression());
			}
			
			if (tok != NULL && equal_token(tok, ")")) {
				tok = next_token();
			} else error_exit("syntax error:  do文に')'が足りない。"); 		
		}else if (is_name_token(tok) || is_number_token(tok)){ // (name exp*)
			add_subtree(tree, parse_expression());
	  
	  		while (tok != NULL && ! equal_token(tok, ")")) {
				add_subtree(tree, parse_expression());
	  		}
	  
	  		if (tok != NULL && equal_token(tok, ")")) {
				tok = next_token();
	  		} else error_exit("syntax error: ')'が足りない。"); 
		} else if (! strcmp(tok, ")")){
			tree->type = DATA_TREE;
		} else{
			while (tok != NULL && ! equal_token(tok, ")")) {
      			add_subtree(tree, parse_expression());
    		}
	
    		if (tok != NULL && equal_token(tok, ")")) {
      			tok = next_token();
			} else error_exit("syntax error )");
		}
	} else
		error_exit("syntax error: 式ではない。");
	return tree;
}
