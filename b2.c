//
// b2.c ... 構文木の構築
//

#include <stdio.h>
#include "tokenizer.h"
#include "parser.h"
#include "tree.h"

// 構文木の表示　　 
static void print(char *str, Tree *t) {
  printf("%s: ", str); show_tree(t); putchar('\n');    // 内部構造を表示
  //printf("%s: ", str); print_tree(t); putchar('\n');    // 式の文字列を表示
}

int main(void) {

  // ソースコードの文字列
  char *source[] = {
    "(head (data ((X) (Y) Z)))",
    "(null? ())",
    "-123",
    "(data (data (a)))",
    "(def x -123)",
    "(if (< x 0) (- 0 x) x)",
    "(do (def a 1) (if a b c))", 
    // 必要に応じて例を追加
    NULL
  };

  // 構文解析と表示
  char **p;
  for (p = source; *p != NULL; p++) {
    printf("source: \"%s\"\n", *p);
    tokenize(*p);
    init_parser();
    Tree *tree = parse_expression();    // 構文解析と構文木の構築
    print("tree", tree);
    printf("%d\n\n", num_subtree(tree));
  }

  return 0;
}
