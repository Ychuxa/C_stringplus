#include "s21_string.h"

char *spec_double(char **str, FlagType FlagStruct, va_list *ptr,
                  unsigned int *count) {
  long double orig_num;

  if (FlagStruct.length == 'L') {
    orig_num = va_arg(*ptr, long double);
  } else {
    orig_num = va_arg(*ptr, double);
  }

  char number[S21_MAX] = "";
  int precision_value = FlagStruct.precision ? FlagStruct.prec_val : 6;

  util_double_to_str(orig_num, number, &precision_value, S21_MAX);

  int lengthValue = 0;

  while (number[lengthValue] != '.' && number[lengthValue] != '\0') {
    lengthValue++;
  }

  s21_rounding_double(lengthValue, precision_value, number);

  char *result = format_double_str(FlagStruct, number, orig_num);

  s21_strncat(*str, result, s21_strlen(result));

  int added_length = s21_strlen(result);
  *count += added_length;
  *str += added_length;

  free(result);

  return *str;
}
