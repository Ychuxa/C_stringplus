#include "s21_string.h"

static void add_exponent(int *stringLength, char *resultString,
                         FlagType formatFlags, int exponentValue);

char *spec_exponent(char **buffer, FlagType FlagStruct, va_list *ptr,
                    unsigned int *count) {
  char *resultBuffer = S21_NULL;
  int flag = 1;

  if (!buffer || !ptr) {
    flag = 0;
  }

  if (flag) {
    long double origNum;

    if (FlagStruct.length == 'L') {
      origNum = va_arg(*ptr, long double);
    } else {
      origNum = (long double)va_arg(*ptr, double);
    }

    int power = 0;
    char powSign = '\0';

    int precisionValue = FlagStruct.precision ? FlagStruct.prec_val : 6;

    long double numCopy = find_exponent(origNum, &power, &powSign);

    int estimatedSize =
        1 + (int)log10l(fabsl(origNum)) + 1 + precisionValue + 5;

    if (estimatedSize < S21_MAX) {
      char prelimResult[S21_MAX] = "";

      util_double_to_str(numCopy, prelimResult, &precisionValue, estimatedSize);

      int charCounter = s21_strlen(prelimResult);

      s21_rounding_double(charCounter, precisionValue, prelimResult);
      add_exponent(&charCounter, prelimResult, FlagStruct, power);

      char *result = format_double_str(FlagStruct, prelimResult, origNum);

      s21_strncat(*buffer, result, s21_strlen(result));

      *buffer += s21_strlen(result);
      *count += s21_strlen(result);

      free(result);
      resultBuffer = *buffer;
    }
  }

  return resultBuffer;
}

static void add_exponent(int *stringLength, char *resultString,
                         FlagType formatFlags, int exponentValue) {
  *stringLength = s21_strlen(resultString);

  char exponentLetter = (formatFlags.specificator < 96) ? 'E' : 'e';
  char exponentValueString[5];

  resultString[(*stringLength)++] = exponentLetter;

  char sign = (exponentValue < 0) ? '-' : '+';

  resultString[(*stringLength)++] = sign;
  exponentValue = abs(exponentValue);

  util_uitoa(exponentValue, exponentValueString, 10);

  int valueLength = s21_strlen(exponentValueString);

  if (valueLength == 1) {
    resultString[(*stringLength)++] = '0';
  }

  for (int i = 0; i < valueLength; i++) {
    resultString[(*stringLength)++] = exponentValueString[i];
  }

  resultString[*stringLength] = '\0';
}
