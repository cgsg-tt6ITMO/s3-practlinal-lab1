#include "auxil.h"

double** copy(double** a) {
  size_t n = 3;
  double** res = (double**)malloc(n * sizeof(double*));
  for (size_t i = 0; i < n; i++)
    res[i] = (double*)malloc(n * sizeof(double));
  for (size_t i = 0; i < n; i++)
    for (size_t j = 0; j < n; j++)
      res[i][j] = a[i][j];
  return res;
}

struct matr matr_mul_matr(struct matr* A, struct matr* B) {
  // validate:
  if (A->m != B->n) {
    printf("YOU CAN'T MULTIPLICATE THOSE MATRICES\n");
    return (struct matr) { -1, -1, NULL };
  }
  double **a = copy(A->arr), **b = copy(B->arr);
  size_t n = A->n, m = B->m, k = A->m;
  double** arr = (double**)malloc(n * sizeof(double*));
  for (size_t i = 0; i < n; i++) {
    arr[i] = (double*)malloc(n * sizeof(double));
  }
  // сам алгоритм перемножения матриц
  for (size_t i = 0; i < n; i++) {
    for (size_t j = 0; j < m; j++) {
      double el = 0;
      for (size_t l = 0; l < k; l++) {
        el += a[i][l] * b[l][j];
      }
      arr[i][j] = el;
    }
  }
  printf("\n");
  struct matr res = (struct matr){ n, m, arr };
  return res;
}

int main1() {
  const size_t n = 3, m = 3;
  double** A = (double**)malloc(n * sizeof(double*));
  double** B = (double**)malloc(n * sizeof(double*));
  for (size_t i = 0; i < n; i++) {
    A[i] = (double*)malloc(n * sizeof(double));
    B[i] = (double*)malloc(n * sizeof(double));
  }

  double aa[3][3] ={
    {1,4,3},
    {2,1,5},
    {3,2,1}
  },
    bb[3][3] = {
    {5,2,1},
    {4,3,2},
    {2,1,5}
  };

  for (size_t i = 0; i < n; i++) {
    for (size_t j = 0; j < n; j++) {
      A[i][j] = aa[i][j];
      B[i][j] = bb[i][j];
    }
  }
  print_matr((struct matr) { n, m, A });
  print_matr((struct matr) { n, m, B });
  struct matr a = (struct matr){ n, m, A }, b = (struct matr){ n, m, B };
  print_matr(matr_mul_matr(&a, &b));
  return 0;
}
