//
// tokenizer.h ... 字句解析器のためのヘッダ
//

#ifndef _TOKENIZER_H_INCLUDED_
#define _TOKENIZER_H_INCLUDED_

void tokenize(const char *source);
// 文字列 source を内部の文字列バッファに複製後，字句列に分解

char *next_token(void);
// 次の字句 (入力終端なら NULL)

int equal_token(char *tok, const char *str);
// 字句 tok が文字列 str に一致するか否か

int is_number_token(char *tok);
// tok が数を表す字句か否か

int is_name_token(char *tok);
// tok が名前を表す字句か否か

int token_to_int(char *tok);
// tok が表す数を整数に変換

#endif // _TOKENIZER_H_INCLUDED_
