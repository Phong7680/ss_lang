#include <stdio.h>
#include "base.h"
#include "tokenizer.h"

char *tok = NULL;    // 先読み字句

void parse_expression(void){
    // exp ->  NUMBER | NAME | ( if exp exp exp ) | (name exp*)
    static int tab_num = 0;
    if (is_name_token(tok) || is_number_token(tok)){ // NUMBER || NAME
        printf("%*s%s\n", tab_num*3,"", tok);
        tok = next_token();
    } else if (equal_token(tok, "(")){
        printf("%*s%s\n", tab_num*3,"", tok);
        tab_num++;
        tok = next_token();

        if (equal_token(tok, "if")) { // (if exp exp exp)
            printf("%*s%s\n", tab_num*3,"", tok);
            tok = next_token();
            int i;
            for (i = 0; i < 3; i++){
                parse_expression();
            }

            if (tok != NULL && equal_token(tok, ")")) {
                tab_num--;
                printf("%*s%s\n", tab_num*3,"", tok);
                tok = next_token();
            } else
                error_exit("syntax error: ')'が足りない。"); 
        }
        else if (is_name_token(tok)){ // (name exp*)
            printf("%*s%s\n", tab_num*3,"", tok);
            tok = next_token();

            while (tok != NULL && ! equal_token(tok, ")")) {
                parse_expression(); 
            }

            if (tok != NULL && equal_token(tok, ")")) {
            tab_num--;
            printf("%*s%s\n", tab_num*3,"", tok);
            tok = next_token();
            } else
                error_exit("syntax error: ')'が足りない。"); 
        } else
            error_exit("syntax error: 条件式でもなく呼出し式でもない。");
    } else
        error_exit("syntax error: 式ではない。");
}


int main(){

    // 入力文字列
    char *source = "(if)";
    //"(if 0)";
    //"(if 0 a)";
    //"(if 0 a b d)";
    //"(1)";
    //"()";

    // 文字列の構文解析
    char *p = source;
    printf("source: \"%s\"\n", p);
    tokenize(p);
    tok = next_token();
    if (tok != NULL)
        parse_expression(); 

    return 0;
}