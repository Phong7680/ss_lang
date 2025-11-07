//
// environment.c ... 環境の基本操作
//
#include <stdio.h>
#include <string.h>
#include "environment.h"
#include "base.h"
#include "tree.h"

//【課題c1】環境の基本操作を実装する　　 
//#define max_var_number 10

Var *Tree_var = NULL;

extern char *comad[];

int check_default_func(char *var){
    int i = 0;
    for (i = 0; comad[i] != NULL; i++){
        if (! strcmp(var, comad[i]))
            return 1;
    }
    return 0;
}

void check_var(char *var){
    if (check_default_func(var)){
        printf("syntax error: %sが組み込み関数の名前と一致する。\n", var);
        exit(EXIT_FAILURE);
    }
}


static Var *create_node(char *var_name, Tree *value){
    value->name = var_name;
    Var *temp = malloc(sizeof(Var));
    //temp->name = _name;
    temp->value = value;
    temp->left = temp->right = NULL;
    return temp;
}

int register_var(char *var_name, Tree *value){
    if (Tree_var == NULL){
        Tree_var = create_node(var_name, value);
        return 1;
    } else {
        Var *child, *parent;
        child = Tree_var;
        while(child != NULL){
            parent = child;
            int cmp = strcmp(var_name, child->value->name);
            if (cmp == 0){
                printf("%sが既に登録された。", parent->value->name);
                exit(EXIT_FAILURE);
                return 0;
            } else if (cmp > 0){
                child = child->right;
                if (child == NULL){
                    parent->right = create_node(var_name, value);
                    break;
                }
            } else {
                child = child->left;
                if (child == NULL){
                    parent->left = create_node(var_name, value);
                    break;
                }
            }
        }
    }
    return 1;
}

void re_register_var(char *var_name, Tree *value){
    if (Tree_var == NULL){
        Tree_var = create_node(var_name, value);
    } else {
        Var *child, *parent;
        child = Tree_var;
        while(child != NULL){
            parent = child;
            int cmp = strcmp(var_name, child->value->name);
            if (cmp == 0){
                value->name = var_name;
                parent->value = value;
                break;
            } else if (cmp > 0){
                child = child->right;
                if (child == NULL){
                    parent->right = create_node(var_name, value);
                    break;
                }
            } else {
                child = child->left;
                if (child == NULL){
                    parent->left = create_node(var_name, value);
                    break;
                }
            }
        }
    }
}

Tree *call_var(char *var){
    Tree *result = NULL;
    if (Tree_var == NULL){
        printf("syntax error: %sが定義されない。\n", var);
        printf("hint: (def 名前 式) | (fun (名前　名前*) 式)\n");
        exit(EXIT_FAILURE);
    }
    if (! strcmp(Tree_var->value->name, var)){
        result = Tree_var->value;
    } else {
        Var *child = Tree_var;
        while (child != NULL){
            int cmp = strcmp(var, child->value->name);
            if (cmp > 0){
                child = child->right;
            } else if (cmp < 0){
                child = child->left;
            } else {
                result = child->value;
                break;
            }
        }
        if (child == NULL){
            printf("syntax error: %sが定義されない。\n", var);
            printf("hint: (def 名前 式) | (fun (名前　名前*) 式)\n");
            exit(EXIT_FAILURE);
        }
    }
    return result;
}

static void print_tree_var(Var *tree){
    if (tree != NULL){
        print_tree_var(tree->left);
        printf("%8s |%5s : ", type_tree(tree->value), tree->value->name);
        print_tree(tree->value); putchar('\n');
        print_tree_var(tree->right);
    }
}

void print_Gvar(void){
    printf("\n%8s |%5s : %s\n", "Type", "Name", "Value");
    print_tree_var(Tree_var);
}

// Stack
LVar *stack = NULL;

static LVar *create_Lnode(char *name, Tree *value){
    value->name = name;
    LVar *temp = malloc(sizeof(LVar));
    temp->next = NULL;
    temp->value = value;
    return temp;
}

LVar *pop(){
    if (stack == NULL){
        return NULL;
    } else {
        LVar *temp = stack;
        stack = stack->next;
        return temp;
    }
}

void push(char *name, Tree *value){
    if (stack == NULL){
        stack = create_Lnode(name, value);
    } else {
        LVar *temp = stack;
        stack = create_Lnode(name, value);
        stack->next = temp;
    }

}

Tree *call_Lvar(char *name){
    LVar *temp = stack;
    Tree *result = NULL;

    while(temp != NULL){
        if (! strcmp(name, temp->value->name)){
            result = temp->value;
            break;
        }
        temp = temp->next;
    }
    return result;
}

void print_Lvar(void){
    LVar *temp = stack;
    printf("\n%8s |%5s : %s\n", "Type", "Name", "Value");
    while(temp != NULL){
        printf("%8s |%5s : ", type_tree(temp->value), temp->value->name);
        print_tree(temp->value); putchar('\n');
        temp = temp->next;
    }
}

// Queue

LVar *queue = NULL;

static LVar *create_Qnode(Tree *value){
    LVar *temp = malloc(sizeof(LVar));
    temp->next = NULL;
    temp->value = value;
    return temp;
}

void push_arg(Tree *value){
    if (queue == NULL){
        queue = create_Qnode(value);
    } else {
        LVar *temp = queue;
        queue = create_Qnode(value);
        queue->next = temp;
    }
}

Tree *pop_arg(){
    if (queue == NULL){
        return NULL;
    } else {
        LVar *temp = queue;
        queue = queue->next;
        return temp->value;
    }
}

void print_queue(void){
    LVar *temp = queue;
    printf("\n%8s | %10s\n", "Type","Value");
    while(temp != NULL){
        printf("%8s |%10s : ", type_tree(temp->value), temp->value->name);
        print_tree(temp->value); putchar('\n');
        temp = temp->next;
    }
}