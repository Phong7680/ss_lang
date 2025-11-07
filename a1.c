//
// a1.c ... 字句解析器の利用例
//

#include <stdio.h>
#include "tokenizer.h"

// 字句を表示　　 
void print_token(char *tok) {
  //【課題a1】tokenizer.h の関数を使って，字句の種類や値を表示するよう実装
  if (is_name_token(tok)){
    printf("NAME(\"%s\")", tok);
  } else if (is_number_token(tok)){
    printf("NUMBER(%s)", tok);
  } else if (equal_token(tok, "(")){
    printf("LPAREN");
  } else if (equal_token(tok, ")")){
    printf("RPAREN");
  } else {
    printf("UNKNOWN");
  }
}

int main(void) {

  // 字句解析
  char *source = "(12345 +09876 -0123( if + x )temp [?])";
  printf("source: \"%s\"\n", source);
  tokenize(source);    // 入力の文字列を字句に分割

  // 各字句の表示
  int i;
  char *tok;
  for (i = 1; (tok = next_token()) != NULL; i++) {    // 次の字句を読み込む
    printf("token%d: \"%s\" ", i, tok);
    print_token(tok);
    printf("\n");
  }

  return 0;
}
