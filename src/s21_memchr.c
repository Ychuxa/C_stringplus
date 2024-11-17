#include "s21_string.h"

void *s21_memchr(const void *str, int c, s21_size_t n) {
  unsigned char *str_0 = (unsigned char *)str;
  unsigned char *res = S21_NULL;

  if (str != S21_NULL) {
    for (s21_size_t i = 0; i < n; i++) {
      if (str_0[i] == c) {
        res = str_0 + i;
        i = n + 1;
      }
    }
  }

  return (void *)res;
}
