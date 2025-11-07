#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tokenizer.h"
#include "parser.h"
#include "evaluator.h"
#include "environment.h"

#define max_char 1024

int main(int argc, char *argv[]){
    char comd[max_char];
    if (argc > 1){
        FILE *fp;
        fp = fopen(argv[1], "r");
        char *type = strtok(argv[1], ".");
        type = strtok(NULL, ".");
        if (strcmp(type, "ss")){
            printf("ssファイルではない。\n");
            exit(1);
        }
        
        while (fgets(comd, max_char-1, fp) != NULL){
            printf("> %s", comd);
            tokenize(comd);
            init_parser();
            Tree *tree = parse_expression(); 
            print_tree(evaluate(tree)); printf("\n");
        }
        fclose(fp);
        printf("終了\n");
    } else {
        while(1){
            printf("> ");
            fgets(comd, max_char-1, stdin);
            tokenize(comd);
            init_parser();
            Tree *tree = parse_expression();
            print_tree(evaluate(tree)); printf("\n");
        } 
    }

    return 0;
}