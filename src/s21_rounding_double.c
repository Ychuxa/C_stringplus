#include "s21_string.h"

static int get_dot_location(const char *number);
static void round_up_position(char *number, int pos);
static void perform_bankers_rounding(char *number, int desiredLen);

void s21_rounding_double(int lenIntDot, int precisionValue, char *number) {
  unsigned int currLen = s21_strlen(number);
  unsigned int desiredLen = lenIntDot + precisionValue;

  int dotLocation = get_dot_location(number);

  if (dotLocation != -1) {
    desiredLen++;
  }

  if (currLen > desiredLen) {
    perform_bankers_rounding(number, desiredLen);

    if (precisionValue == 0) {
      number[dotLocation] = 0;
    } else {
      number[dotLocation + precisionValue + 1] = 0;
    }

    for (unsigned int sl = s21_strlen(number); sl < currLen; sl++) {
      number[sl] = 0;
    }
  }
}

static int get_dot_location(const char *number) {
  int dotLocation = 0;
  int result;

  while (number[dotLocation] != '.' && number[dotLocation] != '\0') {
    dotLocation++;
  }

  if (number[dotLocation] == '\0') {
    result = -1;
  } else {
    result = dotLocation;
  }

  return result;
}

static void round_up_position(char *number, int pos) {
  int completed = 0;

  while (pos >= 0 && !completed) {
    if (number[pos] != '.') {
      if (number[pos] == '9') {
        number[pos] = '0';
        pos--;
      } else {
        number[pos]++;
        completed = 1;
      }
    } else {
      pos--;
    }
  }

  if (pos < 0 && !completed) {
    for (int i = s21_strlen(number); i > 0; i--) {
      number[i] = number[i - 1];
    }
    number[0] = '1';
  }
}

static void perform_bankers_rounding(char *number, int desiredLen) {
  if (number[desiredLen] > '5') {
    round_up_position(number, desiredLen - 1);
  } else if (number[desiredLen] == '5') {
    int previousDigit = number[desiredLen - 1] - '0';
    int i = desiredLen + 1;

    while (number[i] != '\0' && number[i] == '0') {
      i++;
    }

    if (number[i] != '\0' || (previousDigit % 2 != 0)) {
      round_up_position(number, desiredLen - 1);
    }
  }
}
