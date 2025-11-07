//
// environment.h ... 環境の基本操作のためのヘッダ
//

#ifndef _ENVIRONMENT_H_INCLUDED_
#define _ENVIRONMENT_H_INCLUDED_
#include "tree.h"

//【課題c1】環境の基本操作を設計する　　
// 木　(大域変数格納用)
typedef struct  var_{
    Tree *value;
    struct var_ *left;
    struct var_ *right;
} Var;

void check_var(char *var);
int check_default_func(char *var);
int register_var(char *var, Tree *value);
void re_register_var(char *var_name, Tree *value);
Tree *call_var(char *var);
void print_Gvar();


// Stack (局所変数格納用)
typedef struct  Lvar_{
    Tree *value;
    struct Lvar_ *next;
} LVar;

LVar *pop();
void push(char *name, Tree *value);
Tree *call_Lvar(char *);
void print_Lvar(void);

// Stack (関数の引数を評価した値を格納用)
void push_arg(Tree *value);
Tree *pop_arg();
void print_queue(void);

#endif // _ENVIRONMENT_H_INCLUDED_
