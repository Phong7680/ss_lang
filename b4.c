//
// b3.c ... 式の評価
//

#include <stdio.h>
#include "tokenizer.h"
#include "parser.h"
#include "evaluator.h"

// 結果の表示　　 
void print(char *str, Tree *t) {
  printf("%s: ", str); print_tree(t); putchar('\n');
}

int main(void) {

  // ソースコードの文字列
  char *source[] = {
    "(data (a b c))",
    
    "(null? (data (a)))",
    "(null? (data ()))",
    //"(null? (+ 1 2))",

    "(cons 1 (data (2 3)) )",
    "(cons (data (a)) (data (2 3)) )",
    "(cons a (data(2 0)) )",
    //"(cons 1 2)",

    "(head ())",
    "(head (data (a)))",
    "(head (data ((X) (Y) (Z))))",
    //"(head )",

    "(rest (data ((X) (Y) (Z))))", 
    //"(rest ())",
    //"(rest )",

    "(number? ())",
    "(number? (+ 1 2))",
    //"(number? )",

    "(name? ())",
    "(name? (null? ()))",
    "(name? a)",
    "(list? (data (a b c)))",
    "(list? 1)",
    // 必要に応じて例を追加
    NULL
  };

  // 構文解析と式の値の評価
  char **p;
  for (p = source; *p != NULL; p++) {
    printf("source: \"%s\"\n", *p);
    tokenize(*p);
    init_parser();
    Tree *tree = parse_expression();    // 構文解析と構文木の構築
    print("tree", tree);
    //int val = evaluate(tree);
    //printf("%d\n", val);
    Tree* val = evaluate(tree);    // 構文木が表す式の値の評価
    print_tree(val); printf("\n");
  }
  return 0;
}
