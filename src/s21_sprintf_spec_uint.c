#include "s21_string.h"

static void add_base(char *numWithBase, char *num, FlagType FlagStruct);

char *spec_uint(char **buffer, FlagType FlagStruct, va_list *ptr,
                unsigned int *count) {
  unsigned long long int x;
  char num[S21_MAX] = {0};

  if (FlagStruct.length == 'h') {
    x = va_arg(*ptr, unsigned int);
  } else if (FlagStruct.length == 'l') {
    x = va_arg(*ptr, unsigned long int);
  } else if (FlagStruct.length == 'L') {
    x = va_arg(*ptr, unsigned long long int);
  } else {
    x = va_arg(*ptr, unsigned int);
  }

  if (FlagStruct.specificator == 'o') {
    util_uitoa(x, num, 8);
  } else if (FlagStruct.specificator == 'u') {
    util_uitoa(x, num, 10);
  } else {
    util_uitoa(x, num, 16);
  }

  char *transformed;

  if (FlagStruct.specificator == 'x') {
    transformed = s21_to_lower(num);
    if (transformed) {
      s21_strncpy(num, transformed, S21_MAX - 1);
      free(transformed);
    }
  } else if (FlagStruct.specificator == 'X') {
    transformed = s21_to_upper(num);
    if (transformed) {
      s21_strncpy(num, transformed, S21_MAX - 1);
      free(transformed);
    }
  }

  if (x == 0 && FlagStruct.precision && !FlagStruct.prec_val) {
    num[0] = '\0';
  }

  int maxSize = s21_strlen(num) + FlagStruct.prec_val + FlagStruct.width + 10;
  char *result = calloc(maxSize, sizeof(char));
  int i = 0;
  char pre_res[S21_MAX] = "";

  if ((!FlagStruct.zero && FlagStruct.sharp) ||
      (FlagStruct.zero && FlagStruct.sharp)) {
    add_base(pre_res, num, FlagStruct);
  } else {
    s21_strncat(pre_res, num, s21_strlen(num));
  }

  util_adjust_width(result, FlagStruct, &i, s21_strlen(pre_res));

  while (FlagStruct.prec_val - (int)s21_strlen(pre_res) > 0) {
    result[i] = '0';
    i++;
    FlagStruct.prec_val--;
  }

  result[i] = '\0';

  s21_strncat(result, pre_res, s21_strlen(pre_res));

  if (FlagStruct.minus) {
    while ((int)s21_strlen(result) < FlagStruct.width) {
      s21_strncat(result, " ", 1);
    }
  }

  s21_strncat(*buffer, result, s21_strlen(result));

  *buffer += s21_strlen(result);
  *count += s21_strlen(result);

  free(result);

  return *buffer;
}

static void add_base(char *numWithBase, char *num, FlagType FlagStruct) {
  switch (FlagStruct.specificator) {
    case 'o':
      s21_strncat(numWithBase, "0", 1);
      break;
    case 'x':
      s21_strncat(numWithBase, "0x", 2);
      break;
    case 'X':
      s21_strncat(numWithBase, "0X", 2);
      break;
  }
  s21_strncat(numWithBase, num, s21_strlen(num));
}
