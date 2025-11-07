//
// parser.h ... 構文解析器のためのヘッダ
//

#ifndef _PARSER_H_INCLUDED_
#define _PARSER_H_INCLUDED_

#include "tree.h"

void init_parser(void);    // 構文解析を開始(事前に1回だけ実行)
Tree *parse_expression(void);    // 式を構文解析
Tree *parse_statement(void);    // 文を構文解析

#endif // _PARSER_H_INCLUDED_
