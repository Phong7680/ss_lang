//
// b3.c ... 式の評価
//

#include <stdio.h>
#include "tokenizer.h"
#include "parser.h"
int evaluate(Tree *tree); 

// 結果の表示　　 
void print(char *str, Tree *t) {
  printf("%s: ", str); print_tree(t); putchar('\n');
}

int main(void) {

  // ソースコードの文字列
  char *source[] = {     
    "123",
    "x",
    "(+ 123 456)",
    "(if 1 012 345)",
    "(if (= 67 0) (/ x 0) (* x 89))",
    "(/ (* (+ x 10) (- y 20)) -30)",
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
    int val = evaluate(tree);    // 構文木が表す式の値の評価
    printf("value: %d\n", val);
    putchar('\n');
  }
  return 0;
}
