#include "s21_string.h"

char *spec_pointer(char **buffer, FlagType FlagStruct, va_list *ptr,
                   unsigned int *count) {
  void *pointer = va_arg(*ptr, void *);
  unsigned long long value = (unsigned long long)pointer;

  if (!value) {
    s21_strncat(*buffer, S21_NIL, 5);
    *buffer += 5;
    *count += 5;
    return *buffer;
  }

  char result[S21_MAX] = "0x";
  char preRes[S21_MAX / 2] = "";
  util_uitoa(value, preRes, 16);

  for (int i = 0; preRes[i]; i++) {
    preRes[i] = to_lower_char(preRes[i]);
  }
  s21_strncat(result, preRes, s21_strlen(preRes));

  int len = s21_strlen(result);
  int size = len > FlagStruct.width ? len + 1 : FlagStruct.width + 1;
  char *finalResult = calloc(size, sizeof(char));
  int finalResultIndex = 0;

  if (!FlagStruct.minus && (FlagStruct.width - len > 0)) {
    while (FlagStruct.width - len > 0) {
      if (FlagStruct.zero) {
        finalResult[finalResultIndex] = '0';
      } else {
        finalResult[finalResultIndex] = ' ';
      }
      finalResultIndex++;
      FlagStruct.width--;
    }
  }

  s21_strncat(finalResult, result, s21_strlen(result));

  if (FlagStruct.minus) {
    while ((int)s21_strlen(finalResult) < FlagStruct.width) {
      s21_strncat(finalResult, " ", 1);
    }
  }

  s21_strncat(*buffer, finalResult, s21_strlen(finalResult));

  *buffer += s21_strlen(finalResult);
  *count += s21_strlen(finalResult);

  if (finalResult) {
    free(finalResult);
  }

  return *buffer;
}
