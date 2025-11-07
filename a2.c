//
// a2.c ... 構文解析器の例
//

#include <stdio.h>
#include "base.h"
#include "tokenizer.h"

char *tok = NULL;    // 先読み字句

//【課題a2】
//・文法(生成規則の集まり)により正しい字句の並びを定めることを理解する
//・文法に沿った構文解析手続きの書き方を理解する
//・関数 parse_op() と parse_exp() と parse_seq() の開始時と終了時の表示を
//　有効にして，解析木の走査と構文解析の動作を対応させる

// 演算子の構文解析　　 
void parse_op(void) {
  // op -> "+" | "-"
  printf("[op");
  if (equal_token(tok, "+")) {    // 選択肢には条件文
    printf("+");
    tok = next_token();    // 字句を処理したら次の字句を先読み
  } else if (equal_token(tok, "-")) {
    printf("-");
    tok = next_token();
  } else {
    error_exit("syntax error");    // 照合に失敗したら誤り処理
  }
  printf("op]");
}

// 字句の検査と表示　　 
void process_token(int test) {
  if (! test) error_exit("syntax error");   // 照合に失敗したら誤り処理
  printf("%s", tok);
}

// 式の構文解析　　 
void parse_exp(void) {
  // exp -> "(" NAME op NUMBER ")"
  printf("[exp");
  process_token(equal_token(tok, "("));
  tok = next_token();    // 字句を処理したら次の字句を先読み
  process_token(is_name_token(tok));
  tok = next_token();
  parse_op();    // 左辺の記号には解析処理の呼び出し
  process_token(is_number_token(tok));
  tok = next_token();
  process_token(equal_token(tok, ")"));
  tok = next_token();
  printf("exp]");
}

// 式の列の構文解析　　 
void parse_seq(void) {
  // seq -> exp*
  printf("[seq\n");
  while (tok != NULL) {    // 繰り返しには反復文
    parse_exp();
    printf("\n");
  }
  printf("seq]\n");
}

int main(void) {

  // ソースコードの文字列
  char *source[] = {
    "   ",
    " ( x + 0 ) ",
    "(ab + 12) (cde - 345)",
    "(a - 7) ( xyz + 9) (min + 7)",
    "(0 + x)",
    "((a + 2))",
    "(a * 5)",
    "(5 + 1)",
    // 正しい例や誤った例を追加
    NULL
  };

  // 各文字列の構文解析
  char **p;
  for (p = source; *p != NULL; p++) {
    printf("source: \"%s\"\n", *p);
    tokenize(*p);
    tok = next_token();    // 1字句先読みして解析手続きを呼ぶ
    parse_seq();
  }

  return 0;
}
