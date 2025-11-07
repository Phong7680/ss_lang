#include <stdio.h>
#include "base.h"
#include "tokenizer.h"

char *tok = NULL;    // 先読み字句

void parse_expression(void){
    // expression -> NUMBER | NAME | "(" expression* ")"
    static int tab_num = 0;
    if (is_name_token(tok) || is_number_token(tok)){
        printf("%*s%s\n", tab_num*3,"", tok);
        tok = next_token();
    } else if (equal_token(tok, "(")){
        printf("%*s%s\n", tab_num*3,"", tok);
        tab_num++;
        tok = next_token();

        while (tok != NULL && ! equal_token(tok, ")")) {
            parse_expression(); 
        }

        if (tok != NULL && equal_token(tok, ")")) {
            tab_num--;
            printf("%*s%s\n", tab_num*3,"", tok);
            tok = next_token();
        } else error_exit("syntax error ')'が足りない。"); 
    } else
        error_exit("syntax error: 式ではない。");
}


int main(void){

    // 入力文字列
    //char source[] = "(if (< x 0) (- 0 x) x)";
    //char source[] = "(if (< x 0) (- 0 x) x()";
    char source[] = "(if (< x 0) (- 0 x) x)";
    //char source[] = "(if (< x 0) (- 0 x) x) xの絶対値";

    // 文字列の構文解析
    char *p = source;
    printf("source: \"%s\"\n", p);

    tokenize(p);
    tok = next_token();
    if (tok != NULL)
        parse_expression();

    return 0;
}