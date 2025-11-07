//
// tokenizer.c ... 字句解析器
//

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include "base.h"
#include "tokenizer.h"

#define TOKEN_BUFFER_CAPACITY 5000    // 字句の最大格納個数

static char *add_spaces(const char *src) {
  // 字句を ' ' で区切れるようにする前処理
  // '(' や ')' の前後に ' ' を追加し，空白類を ' ' に統一
  size_t len = strlen(src)*3 + 1;    // 最大長(前後に全て空白の入る場合)
  char *buf = (char *) malloc_or_exit(len);
  char *dst = buf;
  for ( ; *src != '\0'; src++) {
    char c = *src;
    if (c == '(' || c == ')') *dst++ = ' ';
    *dst++ = (isspace(c)) ? ' ' : c;    // isspace() は改行文字も検出
    if (c == '(' || c == ')') *dst++ = ' ';
  }
  *dst = '\0';
  return buf;
}

static char *source_buffer = NULL;
static char *current_token = NULL;

static void preprocess(const char *source) {
  source_buffer = add_spaces(source);    // '(' や ')' の前後に ' ' を追加
  current_token = strtok(source_buffer, " ");    // 空白文字までの字句を切り出す
}

static char *read_token(void) {
  char *tok = current_token;
  current_token = strtok(NULL, " ");    // 空白文字までの字句を切り出す
  return tok;
}

static char *token_buffer[TOKEN_BUFFER_CAPACITY];    // 複製・加工用
static int ntokens = 0;    // 切り出した字句数

void tokenize(const char *source) {
  assert(source != NULL);
  preprocess(source);
  char *tok;
  while ((tok = read_token()) != NULL) {
    if (! strcmp(tok, "//")) break; // 注釈機能
    if (ntokens >= TOKEN_BUFFER_CAPACITY) error_exit("token buffer is full");
    token_buffer[ntokens++] = tok;
  }
}

char *next_token(void) {
  static int token_index = 0;    // 読み出した字句数
  if (token_index < ntokens) {
    return token_buffer[token_index++];
  } else {
    return NULL;    // 入力終端
  }
}

int equal_token(char *tok, const char *str) {
  //assert(tok != NULL && str != NULL);
  return (strcmp(tok, str) == 0);
}

int is_number_token(char *tok) {
  // 数 ::= 符号? 数字 数字*    (省略可能な符号の後に数字が1個以上並んだもの)
  // 符号 ::= + | -
  // 数字 ::= 0 | 1 | … | 9
  assert(tok != NULL);
  if (*tok == '+' || *tok == '-') tok++;
  if (! isdigit(*tok)) return 0;
  while (isdigit(*tok)) tok++;
  return *tok == '\0';
}

static int issymbol(char c) {
  static char symbols[] = "*/%^=<>?!$&:_~.";
  char *p;
  for (p = symbols; *p != '\0'; p++) {
    if (*p == c) return 1;
  }
  return 0;
}

int is_name_token(char *tok) {
  // 名前 ::= 符号 | 開始文字 後続文字*
  // 開始文字 ::= 英字 | 記号
  // 後続文字 ::= 英字 | 数字 | 記号 | 符号
  // 符号 ::= + | -
  // 英字 ::= a | b | … | z | A | B | … | Z
  // 記号 ::= * | / | % | ^ | = | < | > | ? | ! | $ | & | : | _ | ~ | .
  // 数字 ::= 0 | 1 | … | 9
  assert(tok != NULL);
  if (equal_token(tok, "+") || equal_token(tok, "-")) return 1;
  if (! isalpha(*tok) && ! issymbol(*tok)) return 0;
  while (isalnum(*tok) || issymbol(*tok) || *tok == '+' || *tok == '-') tok++;
  return *tok == '\0';
}

int token_to_int(char *tok) {
  assert(is_number_token(tok));
  int num;
  sscanf(tok, "%d", &num);    // 正しく変換できるのは int の範囲内だけ
  return num;
}
