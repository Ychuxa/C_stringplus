#include "s21_string.h"

int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  int result = 0;

  if (str1 == S21_NULL || str2 == S21_NULL) {
    result = S21_ERROR;
  } else {
    for (s21_size_t i = 0; i < n && result == 0; i++) {
      if (!*str1 && *str2) {
        result = -(*str2);
      } else if (*str1 && !*str2) {
        result = *str1;
      } else if (*str1 != *str2) {
        result = *str1 - *str2;
      }

      if (!*str1 && !*str2) {
        result = 0;
      }

      str1++;
      str2++;
    }
  }

  return result;
}
