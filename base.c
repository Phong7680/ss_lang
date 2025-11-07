//
// base.c ... 基本関数群
//

#include <stdio.h>
#include <assert.h>
#include "base.h"

void error_exit(const char *str) {
  fprintf(stderr, "%s\n", str);
  exit(EXIT_FAILURE);
}

void *malloc_or_exit(size_t size) {
  assert(size > 0);
  void *p = malloc(size);
  if (p == NULL) error_exit("malloc() failed in malloc_or_exit()");
  return p;
}
