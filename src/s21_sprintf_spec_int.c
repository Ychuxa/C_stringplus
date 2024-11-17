#include "s21_string.h"

char *spec_int(char **buffer, FlagType FlagStruct, va_list *ptr,
               unsigned int *count) {
  long int x = va_arg(*ptr, long int);
  int i = 0, maxLongInt = 30;

  char *array = calloc(maxLongInt, sizeof(char));
  char *tmp = array;

  if (FlagStruct.length == 'h') {
    x = (short)x;
  } else if (FlagStruct.length == 0) {
    x = (int)x;
  }

  util_itoa(x, array, 10);

  if (x == 0 && FlagStruct.precision && !FlagStruct.prec_val) {
    array[0] = '\0';
  }

  if (array[0] == '-') {
    array++;
  }

  int maxSize = s21_strlen(array) + FlagStruct.prec_val + FlagStruct.width + 10;

  char *result = calloc(maxSize, sizeof(char));
  util_adjust_width(result, FlagStruct, &i, s21_strlen(array));

  if (x < 0) {
    util_add_minus(result, i);
  } else {
    util_add_plus_or_space(FlagStruct, result, i);
  }

  while (FlagStruct.prec_val > (int)s21_strlen(array)) {
    s21_strncat(result, "0", 1);
    FlagStruct.prec_val--;
  }

  s21_strncat(result, array, s21_strlen(array));

  if (FlagStruct.minus) {
    while ((int)s21_strlen(result) < FlagStruct.width) {
      s21_strncat(result, " ", 1);
    }
  }

  s21_strncat(*buffer, result, s21_strlen(result));
  unsigned int check = s21_strlen(result);
  *count += check;

  if (result) {
    free(result);
  }

  if (tmp) {
    free(tmp);
  }

  return *buffer + check;
}
