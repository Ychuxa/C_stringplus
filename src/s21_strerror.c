#include "s21_strerror.h"

#include "s21_string.h"

char errors_message[ERROR_SIZE] = {0};

char *s21_strerror(int errnum) {
  char *result = S21_NULL;

  if (errnum >= 0 && errnum < SUM_ERRORS) {
    result = errors[errnum];
  } else {
    s21_sprintf(errors_message, OUT_ERROR, errnum);

    result = errors_message;
  }

  return result;
}
