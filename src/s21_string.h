#ifndef s21_string_H
#define s21_string_H

#include <float.h>
#include <math.h>
#include <stdarg.h>
#include <stdlib.h>

#define S21_NULL ((void *)0)
#define S21_ERROR -1
#define S21_MAX 256
#define MAX_BUFFER_SIZE 1024
#define S21_NULL_STRING "(null)"
#define S21_NULL_STRING_LEN 6

#if defined(__linux__)
#define S21_NIL "0"
#elif defined(__APPLE__)
#define S21_NIL 0x0
#endif

typedef unsigned long s21_size_t;
typedef unsigned int s21_wchar_t;

typedef struct FlagStruct {
  int minus;
  int plus;
  int sharp;
  int space;
  int zero;
  int width;
  int prec_val;
  int precision;
  int length;
  int specificator;
} FlagType;

int s21_sscanf(const char *str, const char *format, ...);
void *s21_memchr(const void *str, int c, s21_size_t n);
int s21_memcmp(const void *str1, const void *str2, s21_size_t n);
void *s21_memcpy(void *dst, const void *src, s21_size_t n);
void *s21_memset(void *dst, int c, s21_size_t n);
char *s21_strchr(const char *str, int c);
s21_size_t s21_strlen(const char *str);
s21_size_t s21_strcspn(const char *str1, const char *str2);
char *s21_strerror(int errnum);
char *s21_strncat(char *dest, const char *src, s21_size_t n);
int s21_strncmp(const char *str1, const char *str2, s21_size_t n);
char *s21_strncpy(char *dest, const char *src, s21_size_t n);
char *s21_strpbrk(const char *str1, const char *str2);
char *s21_strrchr(const char *str, int c);
char *s21_strstr(const char *haystack, const char *needle);
char *s21_strtok(char *str, const char *delim);

int s21_sprintf(char *buffer, const char *format, ...);

char *spec_char(char **buffer, FlagType FlagStruct, va_list *ptr,
                unsigned int *count);

char *spec_int(char **str, FlagType FlagStruct, va_list *ptr,
               unsigned int *count);
char *spec_uint(char **buffer, FlagType FlagStruct, va_list *ptr,
                unsigned int *count);

char *spec_string(char **buffer, FlagType FlagStruct, va_list *ptr,
                  unsigned int *count);

char *spec_double(char **str, FlagType FlagStruct, va_list *ptr,
                  unsigned int *count);

char *spec_exponent(char **buffer, FlagType FlagStruct, va_list *ptr,
                    unsigned int *count);

char *spec_float(char **buffer, FlagType FlagStruct, va_list *ptr,
                 unsigned int *count);

char *spec_pointer(char **buffer, FlagType FlagStruct, va_list *ptr,
                   unsigned int *count);

void util_flags_clean(FlagType *FlagStruct);

char *scan_char(char **str, va_list *ptr, unsigned int *count);
char *scan_int(char **buffer, FlagType FlagStruct, va_list *ptr,
               unsigned int *count);

char *scan_str(char **buffer, va_list *ptr, unsigned int *count);

char *scan_float(char **buffer, FlagType FlagStruct, va_list *ptr,
                 unsigned int *count);

char *scan_pointer(char **buffer, va_list *ptr, unsigned int *count);

int util_hex_to_dec(char c);

char *util_reverse(char s[]);
char *util_itoa(int inputNumber, char *resultString, int base);
char *util_uitoa(unsigned long long value, char *result, int base);

void util_adjust_width(char *formatted_string, FlagType FlagStruct,
                       int *current_index, int string_length);

void util_add_minus(char *str, int i);
void util_add_plus_or_space(FlagType FlagStruct, char *str, int i);
void util_double_to_str(long double origNum, char *number, int *lengthValue,
                        int maxSize);
void s21_rounding_double(int lenIntDot, int precisionValue, char *number);

char *format_double_str(FlagType FlagStruct, char *initialResult,
                        long double originalNum);

double find_exponent(double originalNumber, int *exponentPower,
                     char *exponentSign);

void count_digits(long double number, int *digitsBefore, int *digitsAfter);

void *s21_insert(const char *src, const char *str, size_t startIndex);

void *s21_to_upper(const char *str);
void *s21_to_lower(const char *str);
char to_lower_char(char c);

void *s21_trim(const char *src, const char *trimChars);

#endif
