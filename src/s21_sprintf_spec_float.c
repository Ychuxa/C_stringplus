#include "s21_string.h"

static void s21_trim_zeros(char *str);

char *spec_float(char **buffer, FlagType FlagStruct, va_list *ptr,
                 unsigned int *count) {
  va_list temp_ptr;
  va_copy(temp_ptr, *ptr);

  long double origNum;

  if (FlagStruct.length == 'L') {
    origNum = va_arg(*ptr, long double);
  } else {
    origNum = (long double)va_arg(*ptr, double);
  }

  int precisionValue = FlagStruct.precision ? FlagStruct.prec_val : 6;
  int digitsBefore =
      (fabsl(origNum) >= 1.0) ? (int)log10(fabsl(origNum)) + 1 : 0;

  FlagStruct.precision = 1;

  char *startNumber = *buffer;

  if (origNum == 0.0) {
    s21_strncat(*buffer, "0", 1);
    *count += 1;
    *buffer += 1;
  } else if ((fabsl(origNum) < 1e-4 ||
              fabsl(origNum) >= pow(10, precisionValue - 1)) &&
             ((digitsBefore - precisionValue) != 0)) {
    if (precisionValue > 0) {
      precisionValue -= 1;
      FlagStruct.prec_val = precisionValue;
    }
    spec_exponent(buffer, FlagStruct, &temp_ptr, count);
  } else {
    if (digitsBefore > 0) {
      precisionValue -= digitsBefore;
      FlagStruct.prec_val = precisionValue;
    }
    spec_double(buffer, FlagStruct, &temp_ptr, count);
  }

  va_end(temp_ptr);

  s21_trim_zeros(startNumber);

  return *buffer;
}

static void s21_trim_zeros(char *str) {
  char *dotPtr = S21_NULL;
  char *endPtr;
  char *trimPtr;
  int foundDot = 0;

  if (str != S21_NULL) {
    for (char *ptr = str; *ptr != '\0' && !foundDot; ++ptr) {
      if (*ptr == '.') {
        dotPtr = ptr;
        foundDot = 1;
      }
    }

    if (dotPtr != S21_NULL) {
      endPtr = dotPtr + 1;

      while (*endPtr >= '0' && *endPtr <= '9') {
        ++endPtr;
      }

      trimPtr = endPtr - 1;

      while (trimPtr > dotPtr && *trimPtr == '0') {
        *trimPtr = '\0';
        --trimPtr;
      }

      if (trimPtr == dotPtr) {
        *trimPtr = '\0';
      }
    }
  }
}
