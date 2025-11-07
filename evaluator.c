//
// evaluator ... 評価器
//
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "base.h"
#include "tree.h"
//#include "environment.h"

// 名前が等しいか否かの判定　　 
static int equal_name(char *name, char *str) { return strcmp(name, str) == 0; }

int evaluate(Tree *tree) {
  // 式 -> 数 | 名前 | ( if 式 式 式 ) | ( 名前 式* )
  // 【課題b4 】式の評価器を完成させる (入力プログラムが正しいと仮定して実装)
  int result;
  if (is_number_tree(tree)) {
    result = tree->number;
  } else if (is_name_tree(tree)) {
    result = 1;
  } else /* (is_list_tree(tree)) */ {
    Tree *head = get_subtree(tree, 0);
    char *op = get_name(head);

    if (equal_name(op, "if")) {
      result = evaluate(get_subtree(tree, 1)) ? evaluate(get_subtree(tree, 2)) : evaluate(get_subtree(tree, 3));
    }  else {
      int a1 = evaluate(get_subtree(tree, 1));
      int a2;
      if (num_subtree(tree) == 4)
        a2 = evaluate(get_subtree(tree, 2));

      if (equal_name(op, "+")) result = a1 + a2;
      else if (equal_name(op, "-")) result = a1 - a2;
      else if (equal_name(op, "*")) result = a1 * a2;
      else if (equal_name(op, "/")){
        if (a2 == 0)
          error_exit("０の除算\n");
        result = a1 / a2;
      }
      else if (equal_name(op, "%")) result = a1 % a2;
      else if (equal_name(op, "=")) result = a1 == a2;
      else if (equal_name(op, "<")) result = a1 < a2;
      else if (equal_name(op, "not")) result = ! a1; 
      else if (equal_name(op, "and")) result = a1 && a2;
      else if (equal_name(op, "or")) result = a1 || a2;
    }
  }
  return result;
}
