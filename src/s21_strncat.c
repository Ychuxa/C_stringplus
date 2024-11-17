#include "s21_string.h"

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  char *result = dest;
  s21_size_t i = 0, j = 0;

  if (!(dest == S21_NULL || src == S21_NULL)) {
    while (dest[i] != '\0') {
      i++;
    }

    while (src[j] != '\0' && j < n) {
      dest[i + j] = src[j];
      j++;
    }

    dest[i + j] = '\0';
  } else {
    result = S21_NULL;
  }

  return result;
}
