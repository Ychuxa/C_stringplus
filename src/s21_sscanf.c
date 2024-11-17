#include <ctype.h>
#include <stdarg.h>
#include <stdlib.h>

#include "s21_string.h"

static void s21_skip_spaces(const char **str) {
  while (isspace(**str)) {
    (*str)++;
  }
}

static int s21_parse_int(const char **str) {
  s21_skip_spaces(str);
  int value = 0;
  while (isdigit(**str)) {
    value = value * 10 + (**str - '0');
    (*str)++;
  }
  return value;
}
static float s21_parse_float(const char **str) {
  s21_skip_spaces(str);
  float value = 0.0f;
  float divisor = 10.0f;
  int sign = 1;

  if (**str == '-') {
    sign = -1;
    (*str)++;
  } else if (**str == '+') {
    (*str)++;
  }

  while (isdigit(**str)) {
    value = value * 10 + (**str - '0');
    (*str)++;
  }

  if (**str == '.') {
    (*str)++;
    while (isdigit(**str)) {
      value += (**str - '0') / divisor;
      divisor *= 10;
      (*str)++;
    }
  }

  return value * sign;
}

static void s21_parse_string(const char **str, char *buffer, int buffer_size) {
  s21_skip_spaces(str);
  int i = 0;
  while (!isspace(**str) && **str != '\0' && i < buffer_size - 1) {
    buffer[i++] = **str;
    (*str)++;
  }
  buffer[i] = '\0';
}

int s21_sscanf(const char *str, const char *format, ...) {
  va_list args;
  va_start(args, format);

  int matched = 0;
  const char *fmt = format;

  while (*fmt != '\0') {
    if (isspace(*fmt)) {
      while (isspace(*str)) {
        str++;
      }
      fmt++;
      continue;
    }

    if (*fmt == '%') {
      fmt++;
      if (*fmt == 'd') {
        int *int_arg = va_arg(args, int *);
        *int_arg = s21_parse_int(&str);
        matched++;
      } else if (*fmt == 'f') {
        float *float_arg = va_arg(args, float *);
        *float_arg = s21_parse_float(&str);
        matched++;
      } else if (*fmt == 's') {
        char *char_arg = va_arg(args, char *);
        s21_parse_string(&str, char_arg, MAX_BUFFER_SIZE);
        matched++;
      }
      fmt++;
    } else {
      if (*fmt == *str) {
        fmt++;
        str++;
      } else {
        break;
      }
    }
  }

  va_end(args);
  return matched;
}
