//
// base.h ... 基本関数群のためのヘッダ
//

#ifndef _BASE_H_INCLUDED_
#define _BASE_H_INCLUDED_

#include <stdlib.h>

void error_exit(const char *str);
// 文字列をエラー出力に表示して異常終了

void *malloc_or_exit(size_t size);
// malloc() と同様だが確保失敗で異常終了

#endif // _BASE_H_INCLUDED_
