#include "s21_string.h"

char *spec_char(char **buffer, FlagType FlagStruct, va_list *ptr,
                unsigned int *count) {
  char symbol = va_arg(*ptr, int);

  if (!FlagStruct.minus) {
    while (FlagStruct.width > 1) {
      *(*buffer)++ = ' ';
      (*count)++;
      FlagStruct.width--;
    }
  }

  *(*buffer)++ = symbol;
  (*count)++;

  if (FlagStruct.minus) {
    while (FlagStruct.width > 1) {
      *(*buffer)++ = ' ';
      (*count)++;
      FlagStruct.width--;
    }
  }

  **buffer = '\0';

  return *buffer;
}
