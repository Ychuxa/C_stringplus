#include "s21_string.h"

void *s21_insert(const char *src, const char *str, size_t startIndex) {
  char *result = S21_NULL;
  int flag = 0;

  if (src == S21_NULL || str == S21_NULL || startIndex > s21_strlen(src)) {
    flag = 1;
  }

  if (!flag) {
    size_t src_len = s21_strlen(src);
    size_t str_len = s21_strlen(str);

    result = (char *)malloc((src_len + str_len + 1) * sizeof(char));

    if (result != S21_NULL) {
      s21_strncpy(result, src, startIndex);
      s21_strncpy(result + startIndex, str, str_len);
      s21_strncpy(result + startIndex + str_len, src + startIndex,
                  src_len - startIndex);

      result[src_len + str_len] = '\0';
    }
  }

  return flag ? S21_NULL : result;
}
