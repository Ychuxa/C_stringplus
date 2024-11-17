#include "s21_string.h"

int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  unsigned char *str_1 = (unsigned char *)str1;
  unsigned char *str_2 = (unsigned char *)str2;
  int difference = 0;

  for (s21_size_t i = 0; i < n; i++) {
    difference = *str_1 - *str_2;

    if (*str_1 != *str_2) i = n;
    str_1++;
    str_2++;
  }

  return difference;
}
