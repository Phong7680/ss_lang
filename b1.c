//
// b1.c ... 構文木の基本操作の利用例
//

#include <stdio.h>
#include "tree.h"

// 構文木の表示　　 
void print(char *str, Tree *t) {
  printf("%s: ", str); show_tree(t); putchar('\n');    // 内部構造を表示
  //printf("%s: ", str); print_tree(t); putchar('\n');    // 式の文字列を表示
}

int main(void) {
  // 単純な木の生成
  Tree *tree_123, *tree_abc;
  tree_123 = make_number_tree(123); print("tree_123", tree_123);
  tree_abc = make_name_tree("abc"); print("tree_abc", tree_abc);
  putchar('\n');

  // リスト末尾への要素の追加
  Tree *list = make_list_tree(); print("list", list);
  add_subtree(list, make_name_tree("a")); print("list", list);
  add_subtree(list, make_name_tree("b")); print("list", list);
  add_subtree(list, make_name_tree("c")); print("list", list);
  putchar('\n');

  // 部分木の参照
  int num = num_subtree(list);
  printf("num=%d\n", num);
  int i;
  for (i = 0; i < num; i++) {
    printf("subtree(list, %d)", i);
    print("subtree(list)", get_subtree(list, i));
  }
  putchar('\n');

  // 式を表す構文木の生成
  //【課題b1】式 (* (+ x 1) 2) を表す構文木を生成して表示
  Tree *subtree = make_list_tree(); print("subtree", subtree);
  add_subtree(subtree, make_name_tree("+")); print("subtree", subtree);
  add_subtree(subtree, make_name_tree("x")); print("subtree", subtree);
  add_subtree(subtree, make_number_tree(1)); print("subtree", subtree);
  Tree *tree = make_list_tree(); print("tree", tree);
  add_subtree(tree, make_name_tree("*")); print("tree", tree);
  add_subtree(tree, subtree); print("tree", tree);
  add_subtree(tree, make_number_tree(2)); print("tree", tree);

  return 0;
}
