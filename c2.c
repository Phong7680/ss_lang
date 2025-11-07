//
// c2.c ... 評価器での環境の利用例
//

#include<stdio.h>
#include "tokenizer.h"
#include "parser.h"
#include "evaluator.h"
#include "environment.h"

int main(void) {

  // ソースコードの文字列
  char *source[] = {
    "(def year 2020)",
    "(def days (if (= (% year 4) 0) 366 365))",
    "(def hours (* days 24))",
    "hours",
    "(def list (data (1 2 3)))",
    "(def a (cons 0 list))",
    "a",
    // 必要に応じて例を追加
    NULL
  };

  // 評価器での環境の利用 (必要に応じて初期化や呼び出しを変更)
  char **p;
  for (p = source; *p != NULL; p++) {
    printf("source: \"%s\"\n", *p);
    tokenize(*p);
    init_parser();
    Tree *tree = parse_expression();
    Tree *val = evaluate(tree);
    print_tree(val); putchar('\n');
  }
  
  return 0;
}
