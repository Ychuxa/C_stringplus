#include "s21_string.h"

char *s21_strrchr(const char *str, int c) {
  char *match = S21_NULL;

  if (str) {
    while (*str != '\0') {
      if (*str == c) {
        match = (char *)str;
      }
      str++;
    }
  }

  if (c == '\0') {
    match = (char *)str;
  }

  return match;
}
