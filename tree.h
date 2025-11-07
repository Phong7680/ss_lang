//
// tree.h ... 構文木の基本操作のためのヘッダ
//

#ifndef _TREE_H_INCLUDED_
#define _TREE_H_INCLUDED_

// 構文木のデータ構造　　 

typedef enum { NUMBER_TREE, NAME_TREE, DATA_TREE, LIST_TREE, FUN_TREE} TreeType;

//typedef struct _tree Tree;    // 構文木の型
typedef struct _tree {
  TreeType type;         // 木の種類
  int number;            // 節に格納する数
  char *name;            // 節に格納する名前
  struct _tree *head;    // 列の先頭
  struct _tree *rest;    // 残りの列
} Tree;

Tree *make_number_tree(int number);    // 数の節の生成
Tree *make_name_tree(char *name);    // 名前の節の生成
Tree *make_list_tree(void);    // 空の部分木列の生成
Tree *make_data_tree(void);

int is_number_tree(Tree *tree);    // 数か否かの判定
int is_name_tree(Tree *tree);    // 名前か否かの判定
int is_list_tree(Tree *tree);    // 列か否かの判定
int is_data_tree(Tree *tree);
char *type_tree(Tree *tree);

int get_number(Tree *tree);    // 数の節から数を取得
char *get_name(Tree *tree);    // 名前の節から名前を取得
void add_subtree(Tree *tree, Tree *subtree);    // 部分木列の最後に追加
int num_subtree(Tree *tree);    // 子の個数を取得
Tree *get_subtree(Tree *tree, int n);    // n番目の子を取得 (n≧0)

void show_tree(Tree *tree);    // 木をデータ構造確認用の文字列で表示
void print_tree(Tree *tree);    // 木をプログラムの文字列で表示
 
#endif // _TREE_H_INCLUDED_
