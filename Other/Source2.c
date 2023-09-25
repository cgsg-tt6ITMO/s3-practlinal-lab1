// нахождение определителя, обратной матрицы, ...
#include "auxil.h"

double det2x2(double** a) {
  return a[0][0] * a[1][1] - a[0][1] * a[1][0];
}

double** minor(struct matr m, size_t x, size_t y) {
  double** a = m.arr;
  size_t n = m.n;
  double** res = (double**)malloc((n-1) * sizeof(double*));
  for (size_t i = 0; i < n; i++)
    res[i] = (double*)malloc((n-1) * sizeof(double));
  size_t i_m = 0, j_m;
  for (size_t i = 0; i < n; i++) {
    if (i == x) continue;
    j_m = 0;
    for (size_t j = 0; j < n; j++) {
      if (j != y && i_m < n && j_m < n) {
        res[i_m][j_m] = a[i][j];
        j_m++;
      }
    }
    if (i != x) {
      i_m++;
    }
  }
  return res;
}

double det3x3(double** a) {
  struct matr m = (struct matr){ 3, 3, a };
  size_t n = 3;
  double res = 0, coef = 1;
  for (size_t i = 0; i < n; i++) {
    double** cur_minor = minor(m, 0, i);
    res += coef * a[0][i] * det2x2(cur_minor);
    coef *= -1;
  }
  return res;
}

struct matr cofactor(struct matr M) {
  size_t n = M.n, m = M.m;
  double** res = (double**)malloc(n * sizeof(double*));
  for (size_t i = 0; i < n; i++)
    res[i] = (double*)malloc(n * sizeof(double));
  for (size_t i = 0; i < n; i++){
    for (size_t j = 0; j < m; j++) {
      double** minorr = minor(M, i, j);
      res[i][j] = det2x2(minorr);
    }
  }
  return (struct matr) { n, m, res };
}

struct matr adjust(struct matr M) {
  size_t n = M.n, m = M.m;
  double** res = cofactor(M).arr;
  for (size_t i = 0; i < n; i++) {
    for (size_t j = 0; j < m; j++) {
      if (i % 2 != j % 2)
        res[i][j] = -res[i][j];
    }
  }

  return (struct matr) { n, m, res };
}

struct matr transpose(struct matr M) {
  size_t n = M.n, m = M.m;
  double** res = (double**)malloc(n * sizeof(double*));
  for (size_t i = 0; i < n; i++)
    res[i] = (double*)malloc(n * sizeof(double));
  for (size_t i = 0; i < n; i++) {
    for (size_t j = 0; j < m; j++) {
      res[i][j] = M.arr[j][i];
    }
  }
  return (struct matr) { n, m, res };
}

struct matr matr_mul_num(double a, struct matr M) {
  size_t n = M.n, m = M.m;
  double** res = (double**)malloc(n * sizeof(double*));
  for (size_t i = 0; i < n; i++)
    res[i] = (double*)malloc(n * sizeof(double));
  for (size_t i = 0; i < n; i++) {
    for (size_t j = 0; j < m; j++) {
      res[i][j] = a * M.arr[i][j];
    }
  }
  return (struct matr) { n, m, res };
}

struct matr inverse_matr(struct matr M) {
  double det = det3x3(M.arr);
  if (det == 0) {
    printf("МАТРИЦА НЕОБРАТИМА\n");
    return (struct matr) { 0, 0, NULL };
  }
  return matr_mul_num(
    1.0/det, transpose(adjust(M))
    );
}

int main2() {
  const size_t n = 3, m = 3;
  double** A = (double**)malloc(n * sizeof(double*));
  for (size_t i = 0; i < n; i++)
    A[i] = (double*)malloc(n * sizeof(double));

  double aa[3][3] = {
    {1,0,0},
    {4,5,0},
    {7,8,9}
  };

  for (size_t i = 0; i < n; i++)
    for (size_t j = 0; j < n; j++)
      A[i][j] = aa[i][j];

  struct matr M = (struct matr){ n, m, A };
  print_matr(M);
  print(det3x3(A));
  printf("\n\n");
  print_matr(
    inverse_matr(M)
  );
  return 0;
}

