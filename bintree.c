//
// bintree.c ... 2分木の生成と走査
//
// 使い方： gcc bintree.c -o bintree && ./bintree && rm bintree
//

#include <stdio.h>
#include <stdlib.h>

// 2分木のデータ構造　　 
typedef struct _tree {
  char node;              // 節のデータ(1文字)
  struct _tree *left;     // 右の部分木
  struct _tree *right;    // 左の部分木
} Tree;

// 2分木の節の生成　　 
Tree *branch(int node, Tree *left, Tree* right) {
  Tree *tree = (Tree *) malloc(sizeof(Tree));
  if (tree == NULL) exit(1);
  tree->node = node;
  tree->left = left;
  tree->right = right;
  return tree;
}

// 2分木のメモリ配置の表示　　 
void show_memory(Tree *tree) {
  if (tree == NULL) return;
  printf("%p: %c[%p,%p]\n", tree, tree->node, tree->left, tree->right);
  show_memory(tree->left);
  show_memory(tree->right);
}

// 2分木の図による表示　　 
void display_tree(Tree *tree) {
  static int depth = 0;
  depth++;
  if (tree == NULL) {
    printf("%*s\n", depth*4, "#");
  } else {
    display_tree(tree->right);
    printf("%*c\n", depth*4, tree->node);
    display_tree(tree->left);
  }
  depth--;
}

// 2分木の文字列による表示　　 
void print_tree(Tree *tree) {
  if (tree == NULL) {
    putchar('#');
  } else {
    printf("%c", tree->node);
    putchar('[');
    print_tree(tree->left);
    putchar(',');
    print_tree(tree->right);
    putchar(']');
  }
}

// 2分木の走査と節数の計数　　 
int num_nodes(Tree *tree) {
  if (tree == NULL) return 0;
  printf("node: %c\n", tree->node);    // 先行順(行きがけ)の走査
  int num_left = num_nodes(tree->left);
  int num_right = num_nodes(tree->right);
  return 1 + num_left + num_right;
}

int main(void) {

  // 2分木の生成
  Tree *t1 = branch('a', branch('b', NULL, NULL), NULL);
  Tree *t2 = branch('c', t1, branch('d', NULL, NULL));
  Tree *t3 = branch('e', NULL, branch('f', NULL, NULL));
  Tree *t  = branch('g', t2, t3);

  // メモリ配置の表示
  show_memory(t);
  putchar('\n');

  // 図による表示
  display_tree(t);
  putchar('\n');

  // 文字列による表示
  print_tree(t); putchar('\n');
  putchar('\n');

  // 走査と節数
  printf("num_nodes: %d\n", num_nodes(t));

  return 0;
}
