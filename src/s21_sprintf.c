#include "s21_string.h"

static char *find_spec(char **str, FlagType FlagStruct, va_list *ptr,
                       unsigned int *count);

static const char *flags_parser(const char *str, FlagType *FlagStruct,
                                va_list *args);

int s21_sprintf(char *buffer, const char *format, ...) {
  FlagType FlagStruct = {0};
  unsigned int symb_counter = 0;
  va_list ptr;
  va_start(ptr, format);

  while (*format) {
    if (*format != '%') {
      *buffer = *format;
      buffer++;
      format++;
      symb_counter++;
    } else {
      *buffer = '\0';
      format++;
      format = flags_parser(format, &FlagStruct, &ptr);
      FlagStruct.specificator = *format;
      format++;

      if (format) {
        if (FlagStruct.specificator == '%') {
          *buffer = '%';
          buffer++;
          symb_counter++;
        } else
          buffer = find_spec(&buffer, FlagStruct, &ptr, &symb_counter);
      }
    }
    util_flags_clean(&FlagStruct);
  }
  va_end(ptr);

  return symb_counter;
}

static const char *flags_parser(const char *str, FlagType *FlagStruct,
                                va_list *args) {
  while (*str == '-' || *str == '+' || *str == ' ' || *str == '#' ||
         *str == '0') {
    switch (*str) {
      case '-':
        FlagStruct->minus = 1;
        break;
      case '+':
        FlagStruct->plus = 1;
        break;
      case ' ':
        FlagStruct->space = 1;
        break;
      case '#':
        FlagStruct->sharp = 1;
        break;
      default:
        FlagStruct->zero = 1;
        break;
    }
    str++;
  }

  if (*str == '*') {
    str++;
    FlagStruct->width = va_arg(*args, int);
  } else {
    while (*str >= '0' && *str <= '9') {
      FlagStruct->width *= 10;
      FlagStruct->width += *str - 48;
      str++;
    }
  }

  if (*str == '.') {
    str++;
    FlagStruct->precision = 1;
    if (*str == '*') {
      str++;
      FlagStruct->prec_val = va_arg(*args, int);
    } else {
      while (*str >= '0' && *str <= '9') {
        FlagStruct->prec_val *= 10;
        FlagStruct->prec_val += *str - 48;
        str++;
      }
    }
  }

  if (*str == 'h' || *str == 'l' || *str == 'L') {
    FlagStruct->length = *str;
    str++;
  }

  return str;
}

static char *find_spec(char **buffer, FlagType FlagStruct, va_list *ptr,
                       unsigned int *count) {
  switch (FlagStruct.specificator) {
    case 'c':
      *buffer = spec_char(buffer, FlagStruct, ptr, count);
      break;
    case 'd':
    case 'i':
      *buffer = spec_int(buffer, FlagStruct, ptr, count);
      break;
    case 'f':
      *buffer = spec_double(buffer, FlagStruct, ptr, count);
      break;
    case 's':
      *buffer = spec_string(buffer, FlagStruct, ptr, count);
      break;
    case 'o':
    case 'u':
    case 'x':
    case 'X':
      *buffer = spec_uint(buffer, FlagStruct, ptr, count);
      break;
    case 'e':
    case 'E':
      *buffer = spec_exponent(buffer, FlagStruct, ptr, count);
      break;
    case 'g':
    case 'G':
      *buffer = spec_float(buffer, FlagStruct, ptr, count);
      break;
    case 'p':
      *buffer = spec_pointer(buffer, FlagStruct, ptr, count);
      break;
  }

  return *buffer;
}

void count_digits(long double number, int *digitsBefore, int *digitsAfter) {
  number = fabsl(number);
  *digitsBefore = floorl(log10l(number)) + 1;

  long double fractionPart = number - floorl(number);
  int count = 0;

  while (count < 14) {
    fractionPart *= 10;
    fractionPart -= floorl(fractionPart);
    count++;
  }

  *digitsAfter = count;
}

double find_exponent(double originalNumber, int *exponentPower,
                     char *exponentSign) {
  double absoluteNumber = fabs(originalNumber);
  *exponentPower = 0;

  if (fabs(absoluteNumber) < DBL_EPSILON) {
    *exponentSign = '\0';
    return absoluteNumber;
  }

  while (absoluteNumber >= 10.0) {
    absoluteNumber /= 10.0;
    (*exponentPower)++;
  }

  while (absoluteNumber < 1.0) {
    absoluteNumber *= 10.0;
    (*exponentPower)--;
  }

  *exponentSign = (*exponentPower < 0) ? '-' : '\0';

  return absoluteNumber;
}

char *format_double_str(FlagType FlagStruct, char *initialResult,
                        long double originalNum) {
  s21_size_t formatSize = FlagStruct.width + 2;

  if ((s21_strlen(initialResult) + 2) > formatSize)
    formatSize = s21_strlen(initialResult) + 2;

  char *finalResult = calloc(formatSize + 1, sizeof(char));
  int i = 0;
  char fillChar = FlagStruct.zero ? '0' : ' ';

  int alreadyHasSign = (initialResult[0] == '-' || initialResult[0] == '+');

  if (FlagStruct.space && !alreadyHasSign && originalNum >= 0.0L) {
    finalResult[i++] = ' ';
  }

  while (!FlagStruct.minus &&
         i < (int)(FlagStruct.width - s21_strlen(initialResult) -
                   (FlagStruct.space && !alreadyHasSign))) {
    finalResult[i] = fillChar;
    i += 1;
  }

  if (!alreadyHasSign) {
    if (originalNum < 0.0L)
      util_add_minus(finalResult, i);
    else if (FlagStruct.plus)
      util_add_plus_or_space(FlagStruct, finalResult, i);
  }

  s21_strncat(finalResult, initialResult, s21_strlen(initialResult));

  if (FlagStruct.minus)
    while ((int)s21_strlen(finalResult) < FlagStruct.width)
      s21_strncat(finalResult, " ", 1);

  return finalResult;
}
