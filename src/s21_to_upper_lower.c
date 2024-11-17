#include "s21_string.h"

static char to_upper_char(char c);
static char *transform_string(const char *str, char (*callback)(char));

void *s21_to_upper(const char *str) {
  return str ? transform_string(str, to_upper_char) : S21_NULL;
}

void *s21_to_lower(const char *str) {
  return str ? transform_string(str, to_lower_char) : S21_NULL;
}

static char *transform_string(const char *str, char (*callback)(char)) {
  char *result = (char *)malloc(s21_strlen(str) + 1);

  if (result) {
    for (size_t i = 0; str[i]; i++) {
      result[i] = callback(str[i]);
    }
    result[s21_strlen(str)] = '\0';
  }

  return result;
}

static char to_upper_char(char c) {
  char result = c;

  if (c >= 'a' && c <= 'z') {
    result = c - 32;
  }

  return result;
}

char to_lower_char(char c) {
  char result = c;

  if (c >= 'A' && c <= 'Z') {
    result = c + 32;
  }

  return result;
}
