#include "s21_string.h"

char *s21_strstr(const char *haystack, const char *needle) {
  char *result = S21_NULL;

  if (haystack != S21_NULL && needle != S21_NULL) {
    const char *haystack_pointer = haystack;
    const char *needle_pointer = needle;

    while (*haystack_pointer && result == S21_NULL) {
      const char *temp_haystack = haystack_pointer;
      const char *temp_needle = needle_pointer;

      while (*temp_needle && *temp_haystack && *temp_haystack == *temp_needle) {
        temp_haystack++;
        temp_needle++;
      }

      if (*temp_needle == '\0') {
        result = (char *)haystack_pointer;
      }

      haystack_pointer++;
    }
  }

  return result;
}
