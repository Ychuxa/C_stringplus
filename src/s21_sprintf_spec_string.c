#include "s21_string.h"

static s21_size_t s21_wcslen(const s21_wchar_t *wcharStringStart);
static char *convert_wide_to_char(const s21_wchar_t *wideString);

char *spec_string(char **buffer, FlagType FlagStruct, va_list *ptr,
                  unsigned int *count) {
  char *string;
  s21_wchar_t *wideString;
  int length;
  char *returnBuffer = S21_NULL;

  if (FlagStruct.length == 'l') {
    wideString = va_arg(*ptr, s21_wchar_t *);

    if (wideString != S21_NULL) {
      string = convert_wide_to_char(wideString);
      if (string == S21_NULL) {
        returnBuffer = *buffer;
      }
    } else {
      string = S21_NULL;
    }
  } else {
    string = va_arg(*ptr, char *);
  }

  if (!returnBuffer) {
    length = (string == S21_NULL) ? S21_NULL_STRING_LEN : s21_strlen(string);

    if (FlagStruct.precision) {
      if (string == S21_NULL && FlagStruct.prec_val < S21_NULL_STRING_LEN) {
        length = 0;
      } else if (FlagStruct.prec_val < length) {
        length = FlagStruct.prec_val;
      }
    }

    int totalLength = (length > FlagStruct.width) ? length : FlagStruct.width;
    char stackBuffer[S21_MAX];
    char *result = totalLength < S21_MAX
                       ? stackBuffer
                       : calloc(totalLength + 1, sizeof(char));

    s21_memset(result, 0, totalLength + 1);

    int i = 0;

    if (!FlagStruct.minus) {
      char fill_char = FlagStruct.zero ? '0' : ' ';

      while (FlagStruct.width - length > 0) {
        result[i++] = fill_char;
        FlagStruct.width--;
      }
    }

    if (string != S21_NULL) {
      s21_strncpy(result + i, string, length);
      i += length;
    } else if (!FlagStruct.precision) {
      s21_strncat(result, S21_NULL_STRING, S21_NULL_STRING_LEN);
      i += S21_NULL_STRING_LEN;
    }

    if (FlagStruct.minus) {
      while (i < totalLength) {
        result[i++] = ' ';
      }
    }

    result[i] = '\0';

    s21_strncat(*buffer, result, i);
    *count += i;
    returnBuffer = *buffer + i;

    if (result != stackBuffer) {
      free(result);
    }

    if (FlagStruct.length == 'l' && string) {
      free(string);
    }
  }

  return returnBuffer;
}

static char *convert_wide_to_char(const s21_wchar_t *wideString) {
  char *result = S21_NULL;

  if (wideString != S21_NULL) {
    s21_size_t wideLength = s21_wcslen(wideString);
    char *tempResult = (char *)malloc(wideLength + 1);

    if (tempResult != S21_NULL) {
      s21_size_t i;
      int isValid = 1;

      for (i = 0; i < wideLength && isValid; i++) {
        const s21_size_t MaxAsciiValue = 127;

        if (wideString[i] > MaxAsciiValue) {
          free(tempResult);
          tempResult = S21_NULL;
          isValid = 0;
        } else {
          tempResult[i] = (char)wideString[i];
        }
      }

      if (tempResult != S21_NULL) {
        tempResult[i] = '\0';
        result = tempResult;
      }
    }
  }

  return result;
}

static s21_size_t s21_wcslen(const s21_wchar_t *wcharStringStart) {
  const s21_wchar_t *start = wcharStringStart;

  while (*wcharStringStart) {
    ++wcharStringStart;
  }

  return wcharStringStart - start;
}
