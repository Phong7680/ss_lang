//
// tree.c ... 構文木の基本操作
//

#include <stdio.h>
#include <assert.h>
#include "base.h"
#include "tree.h"

// 構文木のデータ構造　　 

//typedef enum { NUMBER_TREE, NAME_TREE, LIST_TREE } TreeType;
/*
typedef struct _tree {
  TreeType type;         // 木の種類
  int number;            // 節に格納する数
  char *name;            // 節に格納する名前
  struct _tree *head;    // 列の先頭
  struct _tree *rest;    // 残りの列
} Tree; */

// 木の節の生成　　 

static Tree *make_node(void) {
  Tree *tree = (Tree *) malloc_or_exit(sizeof(Tree));
  tree->type = NUMBER_TREE;
  tree->number = 0;
  tree->name = NULL;
  tree->head = NULL;
  tree->rest = NULL;
  return tree;
}

Tree *make_number_tree(int number) {
  Tree *tree = make_node();
  tree->type = NUMBER_TREE;
  tree->number = number;
  return tree;
}

Tree *make_name_tree(char *name) {
  assert(name != NULL);
  Tree *tree = make_node();
  tree->type = NAME_TREE;
  tree->name = name;
  return tree;
}

Tree *make_list_tree(void) {
  Tree *tree = make_node();
  tree->type = LIST_TREE;
  return tree;
}

Tree *make_data_tree(void) {
  Tree *tree = make_node();
  tree->type = DATA_TREE;
  return tree;
}

// 木の種類の判定　　 

int is_number_tree(Tree *tree) {
  assert(tree != NULL);
  return tree->type == NUMBER_TREE;
}

int is_name_tree(Tree *tree) {
  assert(tree != NULL);
  return tree->type == NAME_TREE;
}

int is_list_tree(Tree *tree) {
  assert(tree != NULL);
  return tree->type == LIST_TREE;
}

int is_data_tree(Tree *tree) {
  assert(tree != NULL);
  return tree->type == DATA_TREE;
}

int is_fun_tree(Tree *tree) {
  assert(tree != NULL);
  return tree->type == FUN_TREE;
}

char *type_tree(Tree *tree){
  int a = tree->type;
  if (a == NUMBER_TREE)
    return "Number";
  if (a == NAME_TREE)
    return "Name";
  if (a == DATA_TREE)
    return "Data";
  if (a == LIST_TREE)
    return "List";
  return "Function";
}

// メンバーの取得　　 

int get_number(Tree *tree) {
  assert(is_number_tree(tree));
  return tree->number;
}

char *get_name(Tree *tree) {
  assert(is_name_tree(tree));
  return tree->name;
}

// 木の操作　　 

void add_subtree(Tree *tree, Tree *subtree) {
  //【課題b1】関数を実装する
  Tree *tree_tmp = tree;
  while (tree_tmp->head != NULL)
    tree_tmp = tree_tmp->rest;
  tree_tmp->head = subtree;
  tree_tmp->rest = make_list_tree();
}

int num_subtree(Tree *tree) {
  //【課題b1】関数を実装する
  if (tree->head == NULL) 
    return 1;
  else
    return 1 + num_subtree(tree->rest);
}

Tree *get_subtree(Tree *tree, int n) {
  //【課題b1】関数を実装する
  Tree *temp = tree;
  int i;
  for (i= n; i >0; i--)
    temp = temp->rest;
  return temp->head;
}

void show_tree(Tree *tree) {
  if (tree == NULL) {
    printf("#");
  } else {
    if (is_number_tree(tree)) {
      printf("%d", get_number(tree));
    } else if (is_name_tree(tree)) {
      printf("\"%s\"", get_name(tree));
    } else {
      printf("List");
    }
    putchar('[');
    show_tree(tree->head);
    putchar(',');
    show_tree(tree->rest);
    putchar(']');
  }
}

void print_tree(Tree *tree) {
  if (tree == NULL) return;
  if (is_number_tree(tree)) {
    printf("%d", tree->number);
  } else if (is_name_tree(tree)) {
    printf("%s", tree->name);
  } else if (is_list_tree(tree) || is_data_tree(tree) || is_fun_tree(tree)) {
    putchar('(');
    while (tree->rest != NULL) {
      print_tree(tree->head);
      tree = tree->rest;
      if (tree->rest != NULL) putchar(' ');
    }
    putchar(')');
  } else {
    assert(0);
  }
}
