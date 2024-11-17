#include "s21_string.h"

char *util_reverse(char s[]) {
  char *result = s;

  if (s != S21_NULL) {
    char temp;
    int i = 0, j = s21_strlen(s) - 1;

    while (i < j) {
      temp = s[i];
      s[i] = s[j];
      s[j] = temp;
      i += 1;
      j -= 1;
    }
  } else {
    result = S21_NULL;
  }

  return result;
}

char *util_itoa(int inputNumber, char *resultString, int base) {
  int isError = 0;
  char *outputString = resultString;

  if (base < 2 || base > 36) {
    isError = 1;
    outputString = S21_NULL;
  }

  if (isError == 0) {
    int absoluteValue = abs(inputNumber);
    int stringIndex = 0;

    while (absoluteValue) {
      int remainder = absoluteValue % base;
      if (remainder >= 10) {
        resultString[stringIndex++] = 65 + (remainder - 10);
      } else {
        resultString[stringIndex++] = 48 + remainder;
      }
      absoluteValue /= base;
    }

    if (stringIndex == 0) {
      resultString[stringIndex++] = '0';
    }

    if (inputNumber < 0 && base == 10) {
      resultString[stringIndex++] = '-';
    }

    resultString[stringIndex] = '\0';
    outputString = util_reverse(resultString);
  }

  return outputString;
}

char *util_uitoa(unsigned long long value, char *outputString, int base) {
  unsigned long long valueCopy = value;
  int i = 0;

  if (valueCopy == 0) {
    outputString[i++] = '0';
  } else {
    while (valueCopy) {
      int remainder = valueCopy % base;

      if (remainder >= 10) {
        outputString[i++] = 65 + (remainder - 10);
      } else {
        outputString[i++] = 48 + remainder;
      }
      valueCopy /= base;
    }
  }
  outputString[i] = '\0';

  util_reverse(outputString);

  return outputString;
}

void util_flags_clean(FlagType *FlagStruct) {
  FlagStruct->minus = 0;
  FlagStruct->plus = 0;
  FlagStruct->sharp = 0;
  FlagStruct->space = 0;
  FlagStruct->zero = 0;
  FlagStruct->width = 0;
  FlagStruct->prec_val = 0;
  FlagStruct->precision = 0;
  FlagStruct->length = 0;
  FlagStruct->specificator = 0;
}

void util_adjust_width(char *formatted_string, FlagType FlagStruct,
                       int *current_index, int string_length) {
  int remaining_width = FlagStruct.width - (FlagStruct.prec_val > string_length
                                                ? FlagStruct.prec_val
                                                : string_length);

  while (!FlagStruct.minus && remaining_width > 0) {
    char padding_char = ' ';

    if (!FlagStruct.precision && FlagStruct.zero) {
      padding_char = '0';
    }

    formatted_string[(*current_index)] = padding_char;
    (*current_index)++;
    remaining_width--;
  }
}

void util_add_plus_or_space(FlagType FlagStruct, char *str, int position) {
  int positionToInsert = (str[0] == '0' || position == 0) ? 0 : position - 1;

  if (FlagStruct.plus) {
    str[positionToInsert] = '+';
  } else if (FlagStruct.space) {
    str[positionToInsert] = ' ';
  }
}

void util_add_minus(char *str, int position) {
  int positionToInsert = (str[0] == '0' || position == 0) ? 0 : position - 1;

  str[positionToInsert] = '-';
}

void util_double_to_str(long double origNum, char *number, int *lengthValue,
                        int maxSize) {
  long double origNumInt = 0, origNumDouble = 0;
  s21_size_t maxSize_t = (s21_size_t)maxSize;
  int isMaxSizeReached = 0;

  if (origNum < 0) {
    origNum *= -1;
    s21_strncat(number, "-", s21_strlen("-"));
  }

  origNumDouble = modfl(origNum, &origNumInt);

  char paddingStr[S21_MAX] = {'\0'};
  util_uitoa(origNumInt, paddingStr, 10);

  s21_strncat(number, paddingStr, s21_strlen(paddingStr));

  if (*lengthValue != 0 && !isMaxSizeReached) {
    s21_strncat(number, ".", 1);
    long double multiplier = powl(10, *lengthValue);
    unsigned long long int fracPartAsInt =
        roundl(origNumDouble * multiplier + 0.0000000001L);

    util_uitoa(fracPartAsInt, paddingStr, 10);
    int padLength = s21_strlen(paddingStr);
    for (int i = 0; i < (*lengthValue - padLength) && !isMaxSizeReached; i++) {
      if (s21_strlen(number) + 1 >= maxSize_t) {
        isMaxSizeReached = 1;
      } else {
        s21_strncat(number, "0", 1);
      }
    }
    if (!isMaxSizeReached) {
      s21_strncat(number, paddingStr, padLength);
    }
  }
}

int util_hex_to_dec(char c) {
  int result = 0;

  if (c >= '0' && c <= '9') {
    result = c - 48;
  } else {
    if (c >= 'A' && c <= 'F') {
      result = 10 + c - 65;
    } else if (c >= 'a' && c <= 'f') {
      result = 10 + c - 97;
    } else {
      result = -1;
    }
  }

  return result;
}
