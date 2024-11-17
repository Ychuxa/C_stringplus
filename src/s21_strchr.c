#include "s21_string.h"

char *s21_strchr(const char *str, int c) {
  const char *res = S21_NULL;
  if (str != S21_NULL) {
    for (s21_size_t i = 0; i <= s21_strlen(str); i++) {
      if (str[i] == c) {
        res = str + i;
        i = s21_strlen(str) + 1;
      }
    }
  }

  return (char *)res;
}
