//
// c1.c ... 環境の基本操作の利用例
//

#include <stdio.h>
#include "environment.h"
#include "tree.h"

int main(void) {

  //【課題c1】環境の基本操作をテストする
  register_var("list", make_data_tree());
  register_var("a", make_number_tree(365));
  register_var("b", make_number_tree(24));

  printf("list = %s ", "list");
  print_tree(call_var("list")); printf("\n");
  printf("a = ");
  print_tree(call_var("a")); printf("\n");

  printf("\nAll var");
  print_Gvar();

/*
  push("c1", make_number_tree(2020));
  push("c2", make_number_tree(2));
  push("c3", make_number_tree(22));
  print_Lvar();
  pop();
  print_Lvar();
  pop();
  pop();
  print_Lvar(); */
  
  return 0;
}
