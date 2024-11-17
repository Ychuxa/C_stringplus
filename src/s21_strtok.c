#include "s21_string.h"

char *s21_strtok(char *str, const char *delim) {
  static char *temp;
  char *result = S21_NULL;
  int flag = 0;

  if (str != S21_NULL) {
    temp = str;
  }

  if (temp == S21_NULL || (delim != S21_NULL && *delim == '\0')) {
    flag = 1;
  } else {
    while (*temp && s21_strchr(delim, *temp)) {
      temp++;
    }

    if (*temp != '\0') {
      result = temp;

      while (*temp && !s21_strchr(delim, *temp)) {
        temp++;
      }

      if (*temp) {
        *temp++ = '\0';
      }
    }
  }

  return flag ? str : result;
}
