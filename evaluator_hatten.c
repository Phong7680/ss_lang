//
// evaluator ... 評価器
//
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "base.h"
#include "tree.h"
#include "environment.h"

// 名前が等しいか否かの判定　　 
static int equal_name(char *name, char *str) { return strcmp(name, str) == 0; }
char *comad[] = {
    "def", "redef", "fun", "if", "data", "do", "or", "not", "and", "null?", "cons", "head", "rest",
    "number?", "name?", "list?", "+", "-", "*", "/", "=", "%", "<", ">", "Gvar", "Lvar", "Fvar", NULL
};
typedef enum comand_num {
    DEF, REDEF, FUN, IF, DATA, DO, OR, NOT, AND, NIL, CONS, HEAD, REST,
    NUM, NAME, LIST, ADD, SUB, MUL, DIV, EQU, MOD, LES, LAR, GVAR, LVAR, FVAR, NaN
}comad_num;

static int idx(char *op){
    comad_num i;
    for (i = DEF; i < NaN; i++)
        if (equal_name(op, comad[i]))
            return (int)i;
    return (int)NaN;
}

Tree* evaluate(Tree *);

Tree *copy_var(Tree *var){
    
    if (var != NULL){
        Tree *temp = make_list_tree();
        memcpy(temp, var, sizeof(Tree));
        if (var->head != NULL)
            temp->head = copy_var(var->head);
        if (var->rest != NULL)
            temp->rest = copy_var(var->rest);
        return temp;
    } else 
        return NULL;
} 

int evaluate_sentence(Tree *tree) {
    if (is_name_tree(tree) || is_number_tree(tree)){
        evaluate(tree);
        return 0;
    } else if (tree->head != NULL){
        Tree *head = tree->head;
        if (!strcmp("def", head->name)){
            if (num_subtree(tree) != 4 || !is_name_tree(get_subtree(tree, 1)) ){
                printf("syntax error: 定義が正しくない。\n");
                printf("hint: (def 名前 式)\nerror: ");
                print_tree(tree); putchar('\n'); exit(EXIT_FAILURE);
            } else {
                char *var_name = get_subtree(tree, 1)->name;
                Tree *value = evaluate(get_subtree(tree, 2));
                check_var(var_name);
                push(var_name, value);
            }
            return 1;
        } else if (!strcmp("fun", head->name)) {
            if (num_subtree(tree) != 4){
            printf("syntax error: 関数の定義が正しくない。\n");
            printf("hint: (fun (名前 名前*) 式) , 名前* : 名前の0個以上の並び。\nerror: ");
            print_tree(tree); putchar('\n'); exit(EXIT_FAILURE);
            } else {
                Tree *temp = get_subtree(tree, 1);
                int n = num_subtree(temp);
                if (n < 2 || !is_name_tree(temp->head)){
                    printf("syntax error: 関数名がない、または名前ではない。\n");
                    printf("hint: (def 名前 式)\nerror: ");
                    print_tree(tree); putchar('\n'); exit(EXIT_FAILURE);
                } else {
                    Tree *result = NULL;
                    char *fun_name = temp->head->name;
                    check_var(fun_name);
                    result = tree->rest;
                    result->type = FUN_TREE;
                    result->name = fun_name;
                    result->number = n - 2; //関数の引数の個数 
                    push(fun_name, result);
                }
            }
            return 1;
        } else {
            evaluate(tree);
        }
    }
    return 0;
}

Tree* evaluate(Tree *tree) {
  // 式 -> 数 | 名前 | ( if 式 式 式 ) | ( 名前 式* )
  // 【課題b4】式の評価器を完成させる (入力プログラムが正しいと仮定して実装)
  Tree *result = NULL;
    if (is_number_tree(tree)) { // Number
        result = tree;
    } else if (is_name_tree(tree)) { // Name
        check_var(tree->name);
        result =  call_Lvar(tree->name);
        if (result == NULL){
            result = call_var(tree->name);
        }
    } else if (is_data_tree(tree)) { // Data
        return tree;
    } else/* (is_list_tree(tree)) */ { // List
    Tree *head = get_subtree(tree, 0);
    if (is_number_tree(head)){
        printf("syntax error: 式ではない。\n");
        printf("hint: (data 式) \nerror: ");
        print_tree(tree); putchar('\n'); exit(EXIT_FAILURE);
    }
    char *op = get_name(head);
    if (get_subtree(tree, 1) == NULL && check_default_func(op) == 0){
        result = evaluate(head);
    } else { 
    switch (idx(op))
    {
    case DEF:
        if (num_subtree(tree) != 4 || !is_name_tree(get_subtree(tree, 1)) ){
            printf("syntax error: 定義が正しくない。\n");
            printf("hint: (def 名前 式)\nerror: ");
            print_tree(tree);putchar('\n'); exit(EXIT_FAILURE);
        } else {
            char *var_name = get_subtree(tree, 1)->name;
            Tree *value = evaluate(get_subtree(tree, 2));

            check_var(var_name);
            if(register_var(var_name, value))
                result = value;
        }
        break;
    case REDEF:
        do{
            char *var_name = get_subtree(tree, 1)->name;
            Tree *value = evaluate(get_subtree(tree, 2));
            check_var(var_name);
            re_register_var(var_name, value);
            result = value;
        } while(0);
        break;
    case FUN:
        if (num_subtree(tree) != 4){
            printf("関数の定義が正しくない。\n");
        } else {
            Tree *temp = get_subtree(tree, 1);
            int n = num_subtree(temp);
            if (n < 2 || !is_name_tree(temp->head)){
                printf("syntax error: 関数名がない、または名前ではない。\n");
                printf("hint: (def 名前 式)\nerror: ");
                print_tree(tree); putchar('\n'); exit(EXIT_FAILURE);
            } else {
                char *fun_name = temp->head->name;
                check_var(fun_name);
                result = tree->rest;
                result->type = FUN_TREE;
                result->name = fun_name;
                result->number = n - 2; //関数の引数の個数 
                if (! register_var(fun_name, result))
                    result = NULL;
            }
        }
        break;
    case NaN:
        do{
            Tree *temp1 = tree->head;
            temp1 = call_Lvar(temp1->name);
            if (temp1 == NULL){
                temp1 = tree->head;
                temp1 = call_var(temp1->name);
                
            }
            int n = temp1->number, i;
            Tree *temp2 = get_subtree(temp1, 1);
            temp1 = get_subtree(temp1, 0);
            
            for (i = 1; i <= n; i++){
                push_arg(evaluate(get_subtree(tree, i))); 
            }
            for (i = n; i >= 1; i--){
                Tree *temp = copy_var(pop_arg());
                push(get_subtree(temp1, i)->name, temp);
            }
            result = evaluate(temp2);
            for (i = 1; i <= n; i++){
                pop();
            } 
        } while (0);
        break;
    case IF:
        result = (evaluate(get_subtree(tree, 1))->number ? evaluate(get_subtree(tree, 2)) : evaluate(get_subtree(tree, 3)));
        break;
    case DATA:
        result = get_subtree(tree, 1);
        if (num_subtree(result) == 1 && !is_list_tree(result) && !is_data_tree(result)){
            result = make_data_tree();
            result->head = get_subtree(tree, 1);
            result->rest = make_list_tree();
        } else{
            result->type = DATA_TREE;
        }
        break;
    case DO:
        ;
        int n = num_subtree(tree);
        if (n <= 2){
            printf("syntax error: do文には式がない。\n");
            printf("hint: (do 文* 式), 文* : 文の0個以上の並び。\nerror: ");
            print_tree(tree); putchar('\n'); exit(EXIT_FAILURE);
        } else if (n == 3){
            if (evaluate_sentence(get_subtree(tree, 1))){
                printf("syntax error: do文には式がない。\n");
                printf("hint: (do 文* 式), 文* : 文の0個以上の並び。\nerror: ");
                print_tree(tree); putchar('\n'); exit(EXIT_FAILURE);
            } else 
                result = evaluate(get_subtree(tree, 1));
        } else {
            int i, count = 0;
            for(i = 1; i <= n-3; i++){
                count += evaluate_sentence(get_subtree(tree, i));
            }
            result = evaluate(get_subtree(tree, n-2));
            for (i = 0; i < count; i++){
                pop();
            }
        }
        break;
    case CONS:
        do {
            if (num_subtree(tree) != 4){
                printf("syntax error: cons関数の引数が足りない。\n");
                printf("hint: (cons 数|名前|リスト リスト)。\nerror: ");
                print_tree(tree); putchar('\n'); exit(EXIT_FAILURE);
           }
            Tree *temp1, *temp2;
            result = make_data_tree();
            temp1 = get_subtree(tree, 1);
            temp2 = get_subtree(tree, 2);

            if (is_list_tree(temp1)){
                temp1 = evaluate(temp1);
            }
            if (! is_data_tree(temp2)){
                temp2 = evaluate(temp2);
            }
            if (! is_data_tree(temp2)){
                printf("syntax error: cons関数の第2引数はリストではない。\n");
                printf("hint: (cons 数|名前|リスト リスト)。\nerror: ");
                print_tree(tree); putchar('\n'); exit(EXIT_FAILURE);
            }
            result->head = temp1;
            result->rest = temp2;
        } while (0);     
        break;
    case HEAD:
        do{
            Tree *temp = get_subtree(tree, 1);
            if (temp == NULL){
                printf("syntax error: head関数に引数がない。\n");
                printf("hint: (head リスト)。\nerror: ");
                print_tree(tree); putchar('\n'); exit(EXIT_FAILURE);
            }

            if (is_data_tree(temp)){
                result = num_subtree(temp) == 1? temp : get_subtree(temp, 0);
            } else {
                temp = evaluate(temp);
                if (! is_data_tree(temp)){
                    printf("syntax error: head関数の引数はリストではない。\n");
                    printf("hint: (cons 数|名前|リスト リスト)。\nerror: ");
                    print_tree(tree); putchar('\n'); exit(EXIT_FAILURE);
                }
                temp = get_subtree(temp, 0);
                result = temp;
            }
        } while (0);
        break;
    case REST:
        do {
            Tree *temp = get_subtree(tree, 1);
            if (temp == NULL){
                printf("syntax error: rest関数に引数がない。\n");
                printf("hint: (rest リスト)。\nerror: ");
                print_tree(tree); putchar('\n'); exit(EXIT_FAILURE);
            }

            if (temp->head == NULL && is_data_tree(temp)){
                printf("syntax error: rest関数の引数が空リストである。\n");
                printf("hint: (rest リスト)。\nerror: ");
                print_tree(tree); putchar('\n'); exit(EXIT_FAILURE);
            } else {
                temp = evaluate(temp);
                if (! is_data_tree(temp)){
                    printf("syntax error: rest関数の引数はリストではない。\n");
                    printf("hint: (rest リスト)。\nerror: ");
                    print_tree(tree); putchar('\n'); exit(EXIT_FAILURE);
                }
                if (temp->head == NULL){
                    printf("syntax error: rest関数の引数が空リストである。\n");
                    printf("hint: (rest リスト)。\nerror: ");
                    print_tree(tree); putchar('\n'); exit(EXIT_FAILURE);
                }
                temp = temp->rest;
                temp->type = DATA_TREE;
                result = temp;
            }
        } while (0);
        
        break;
    case NIL:
        do {
            Tree *temp = get_subtree(tree, 1);
            if (temp == NULL){
                printf("syntax error: rest関数の引数がない。\n");
                printf("hint: (null? リスト)。\nerror: ");
                print_tree(tree); putchar('\n'); exit(EXIT_FAILURE);
            }
            else if (temp->head == NULL && is_data_tree(temp)){
                result = make_number_tree(1);
            } else {
                temp = evaluate(temp);
                if (is_data_tree(temp) == 0){
                    printf("syntax error: rest関数の引数はリストではない。\n");
                    printf("hint: (null? リスト)。\nerror: ");
                    print_tree(tree); putchar('\n'); exit(EXIT_FAILURE);
                }
                result = temp->head == NULL ? make_number_tree(1) : make_number_tree(0);
            }
        } while (0);
        break;
        
    case NOT:
        ;
        do {
            
            if (num_subtree(tree) != 3){
                printf("syntax error: not関数の引数が多すぎるまたは少なすぎる。\n");
                printf("hint: (not 数)。\nerror: ");
                print_tree(tree); putchar('\n'); exit(EXIT_FAILURE);
            }
            Tree *temp = evaluate(get_subtree(tree, 1));
            if (!is_number_tree(temp)){
                error_exit("not演算関数の引数が数ではない。");
                printf("syntax error: not演算関数の引数が数ではない。\n");
                printf("hint: (not 数)。\nerror: ");
                print_tree(tree); putchar('\n'); exit(EXIT_FAILURE);
            } 
            result = make_number_tree(!temp->number); 
        } while (0);
        
        break;
    case NUM:
        do {
            Tree *temp = tree->rest->head;
            if (temp == NULL){
                printf("syntax error: number?関数の引数がない。\n");
                printf("hint: (nummber? 式)。\nerror: ");
                print_tree(tree); putchar('\n'); exit(EXIT_FAILURE);
            }
            
            if (is_number_tree(temp)){
                result = make_number_tree(1);
            } else {
                temp = evaluate(temp);
                result = is_number_tree(temp) ? make_number_tree(1) : make_number_tree(0);
            }
        } while (0);
        break;
    case NAME:
        do {
            Tree *temp = tree->rest->head;
            if (temp == NULL){
                printf("syntax error: name?関数の引数がない。\n");
                printf("hint: (name? 式)。\nerror: ");
                print_tree(tree); putchar('\n'); exit(EXIT_FAILURE);
            }
            
            if (is_name_tree(temp)){
                result = make_number_tree(1);
            } else {
                temp = evaluate(temp);
                result = is_name_tree(temp) ? make_number_tree(1) : make_number_tree(0);
            }
        } while (0);
        break;
    case LIST:
        do {
            Tree *temp = tree->rest->head;
            if (temp == NULL){
                printf("syntax error: list?関数の引数がない。\n");
                printf("hint: (list 式)。\nerror: ");
                print_tree(tree); putchar('\n'); exit(EXIT_FAILURE);
            }
            
            if (is_data_tree(temp)){
                result = make_number_tree(1);
            } else {
                temp = evaluate(temp);
                result = is_data_tree(temp) ? make_number_tree(1) : make_number_tree(0);
            }
        } while (0);
        break;
    case GVAR:
        print_Gvar();
        break;
    case LVAR:
        print_Lvar();
        break;
    case FVAR:
        print_queue();
        break;
    default: 
        do {
            int a1, a2;
            Tree *temp1, *temp2;
            if (num_subtree(tree) != 4){
                printf("syntax error: 二項演算関数の引数が多すぎるまたは少なすぎる。\n");
                printf("hint: (二項演算 数　数)。\nerror: ");
                print_tree(tree); putchar('\n'); exit(EXIT_FAILURE);
            } else {
                temp1 = evaluate(get_subtree(tree, 1));
                temp2 = evaluate(get_subtree(tree, 2));
                if (!is_number_tree(temp1) || !is_number_tree(temp2)) {
                    printf("syntax error: 二項演算関数の引数が数ではない。\n");
                    printf("hint: (二項演算 数　数)。\nerror: ");
                    print_tree(tree); putchar('\n'); exit(EXIT_FAILURE);
                }
                a1 = temp1->number;
                a2 = temp2->number;
            }
                switch (idx(op))
            {   
            case OR:
                result = make_number_tree(a1 || a2);
                break;
            case AND:
                result = make_number_tree(a1 && a2);
                break;
            case ADD:
                result = make_number_tree(a1 + a2);
                break;
            case SUB:
                result = make_number_tree(a1 - a2);
                break;
            case MUL:
                result = make_number_tree(a1 * a2);
                break;
            case DIV:
                if (a2 == 0){
                    printf("syntax error: 0での除算。\nerror: ");
                    print_tree(tree); putchar('\n'); exit(EXIT_FAILURE);
                }
                result = make_number_tree(a1 / a2);
                break;
            case EQU:
                result = make_number_tree(a1 == a2);
                break;
            case MOD:
                result = make_number_tree(a1 % a2);
                break;
            case LES:
                result = make_number_tree(a1 < a2);
                break;
            case LAR:
                result = make_number_tree(a1 > a2);
                break;
            }
        } while (0); 
        break;
    }
    }
  }
  return result;
}
