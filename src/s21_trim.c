#include "s21_string.h"

static void right_side(char *result, const char *trimChars);
static void left_side(char *result, const char *src, const char *trimChars);

void *s21_trim(const char *src, const char *trimChars) {
  char *result = S21_NULL;

  if (src) {
    char default_chars[10] = " \t\n\v\r\f\0";
    s21_size_t length = s21_strlen(src) + 2;

    if (trimChars == S21_NULL || s21_strlen(trimChars) == 0) {
      trimChars = default_chars;
    }

    result = (char *)malloc(length * sizeof(char));

    if (result != S21_NULL) {
      s21_strncpy(result, (char *)src, length);
      left_side(result, src, trimChars);
      right_side(result, trimChars);
    }
  }

  return (void *)result;
}

static void right_side(char *result, const char *trimChars) {
  s21_size_t trim_length = s21_strlen(trimChars);
  s21_size_t result_length = s21_strlen(result);

  int i = (int)result_length - 1;
  int continueOuterLoop = 1;

  while (i >= 0 && continueOuterLoop) {
    int foundTrimChar = 0;

    for (s21_size_t j = 0; j < trim_length && !foundTrimChar; j++) {
      if (result[i] == trimChars[j]) {
        result[i] = '\0';
        foundTrimChar = 1;
      }
    }

    if (!foundTrimChar) {
      continueOuterLoop = 0;
    }

    i--;
  }
}

static void left_side(char *result, const char *src, const char *trimChars) {
  s21_size_t trim_length = s21_strlen(trimChars);
  s21_size_t str_length = s21_strlen(src);
  s21_size_t i = 0;

  int continueOuterLoop = 1;

  while (i < str_length && continueOuterLoop) {
    int foundTrimChar = 0;

    for (s21_size_t j = 0; j < trim_length && !foundTrimChar; j++) {
      if (src[i] == trimChars[j]) {
        foundTrimChar = 1;
      }
    }

    if (!foundTrimChar) {
      continueOuterLoop = 0;
    } else {
      i++;
    }
  }

  if (i < str_length) {
    s21_size_t counter = 0;

    while (i < str_length) {
      result[counter++] = src[i++];
    }

    result[counter] = '\0';
  } else {
    result[0] = '\0';
  }
}
