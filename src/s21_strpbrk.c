#include "s21_string.h"

char *s21_strpbrk(const char *str, const char *sym) {
  char *result = S21_NULL;

  if (!(str == S21_NULL || sym == S21_NULL)) {
    int flag = 1;

    for (s21_size_t i = 0; str[i] != '\0' && flag; i++) {
      for (s21_size_t j = 0; sym[j] != '\0' && flag; j++) {
        if (sym[j] == str[i]) {
          flag = 0;
          result = (char *)&str[i];
        }
      }
    }
  }

  return result;
}
