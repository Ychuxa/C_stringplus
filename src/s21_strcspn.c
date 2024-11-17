#include "s21_string.h"

s21_size_t s21_strcspn(const char *str1, const char *str2) {
  s21_size_t i, j, result = 0;
  int found = 0;

  if (str1 != S21_NULL && str2 != S21_NULL) {
    for (i = 0; str1[i] != '\0' && !found; ++i) {
      for (j = 0; str2[j] != '\0' && !found; ++j) {
        if (str1[i] == str2[j]) {
          --i;
          found = 1;
        }
      }
    }

    if (found || str1[i] == '\0') {
      result = i;
    }
  }

  return result;
}
