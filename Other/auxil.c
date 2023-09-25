#include "auxil.h"

void print(double a) {
  printf("%f ", a);
}

void print_arr(double* a, size_t n) {
  for (size_t j = 0; j < n; j++) {
    if ((a + j) != NULL)
      print(*(a + j));
  }
  printf("\n");
}

void print_matr(struct matr M) {
  double** arr = M.arr;
  size_t n = M.n, m = M.m;
  for (size_t i = 0; i < n; i++) {
    print_arr(*(arr + i), m);
  }
  printf("\n");
}
