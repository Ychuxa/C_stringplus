#include "s21_string.h"

void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  unsigned char *dest_0 = (unsigned char *)dest;
  const unsigned char *src_0 = (unsigned char *)src;

  if (dest_0 && (src_0 || n == 0)) {
    for (s21_size_t i = 0; i < n; i++) {
      dest_0[i] = src_0[i];
    }
  } else {
    dest_0 = S21_NULL;
  }

  return dest_0;
}
