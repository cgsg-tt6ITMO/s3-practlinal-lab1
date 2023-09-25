#include "structs.h"

char abc[] = "àáâãäåæçèéêëìíîïğñòóôõö÷øûüışÿ";

void print(size_t s) {
  printf("%zu ", s);
}

void print_int64_t(int64_t s) {
  printf("%" PRId64 " ", s);
}

void print_vec(struct vec* v) {
  for (size_t i = 0; i < v->n; i++) {
    printf("%zu ", *(v->v + i));
  }
  printf("\n");
}

void print_matr(struct square_matrix* M) {
  size_t** arr = M->arr;
  size_t n = M->n;
  for (size_t i = 0; i < n; i++) {
    print_vec(&((struct vec) { n, *(M->arr + i) }));
  }
  printf("\n");
}

struct vec vec2(size_t v[2]) {
  size_t n = 2;
  size_t* res = (size_t*)malloc(n * sizeof(size_t));
  for (size_t i = 0; i < n; i++) {
    res[i] = v[i];
  }
  return (struct vec) { n, res };
}

struct vec vec3(size_t v[3]) {
  size_t n = 3;
  size_t* res = (size_t*)malloc(n * sizeof(size_t));
  for (size_t i = 0; i < n; i++) {
    res[i] = v[i];
  }
  return (struct vec) { n, res };
}

struct vec vec4(size_t v[4]) {
  size_t n = 4;
  size_t* res = (size_t*)malloc(n * sizeof(size_t));
  for (size_t i = 0; i < n; i++) {
    res[i] = v[i];
  }
  return (struct vec) { n, res };
}

struct square_matrix matr2x2(size_t arr[2][2]) {
  size_t n = 2;
  size_t** res = (size_t**)malloc(n * sizeof(size_t*));
  for (size_t i = 0; i < n; i++)
    res[i] = (size_t*)malloc(n * sizeof(size_t));
  for (size_t i = 0; i < n; i++) {
    for (size_t j = 0; j < n; j++) {
      res[i][j] = arr[i][j];
    }
  }
  return (struct square_matrix) { n, res };
}

struct square_matrix matr3x3(size_t arr[3][3]) {
  size_t n = 3;
  size_t** res = (size_t**)malloc(n * sizeof(size_t*));
  for (size_t i = 0; i < n; i++)
    res[i] = (size_t*)malloc(n * sizeof(size_t));
  for (size_t i = 0; i < n; i++) {
    for (size_t j = 0; j < n; j++) {
      res[i][j] = arr[i][j];
    }
  }
  return (struct square_matrix) { n, res };
}

struct square_matrix matr4x4(size_t arr[4][4]) {
  size_t n = 4;
  size_t** res = (size_t**)malloc(n * sizeof(size_t*));
  for (size_t i = 0; i < n; i++)
    res[i] = (size_t*)malloc(n * sizeof(size_t));
  for (size_t i = 0; i < n; i++) {
    for (size_t j = 0; j < n; j++) {
      res[i][j] = arr[i][j];
    }
  }
  return (struct square_matrix) { n, res };
}

struct vec matr_mul_vec(struct square_matrix M, struct vec V) {
  size_t n = V.n;
  if (M.n != n) {
    printf("İÒÓ ÌÀÒĞÈÖÓ È ÂÅÊÒÎĞ ÍÅËÜÇß ÏÅĞÅÌÍÎÆÀÒÜ\n");
    return (struct vec) { 0, NULL };
  }
  size_t** m = M.arr, * v = V.v;
  size_t* res = (size_t*)malloc(n * sizeof(size_t));
  for (size_t i = 0; i < n; i++) {
    res[i] = 0;
    for (size_t j = 0; j < n; j++) {
      res[i] += (m[i][j] * v[j]) % abc_len;
    }
    res[i] %= abc_len;
  }
  return (struct vec) { n, res };
}

struct square_matrix minor(struct square_matrix *M, size_t x, size_t y) {
  size_t** a = M->arr;
  size_t n = M->n;
  size_t** res = (size_t**)malloc((n - 1) * sizeof(size_t*));
  for (size_t i = 0; i < n; i++)
    res[i] = (size_t*)malloc((n - 1) * sizeof(size_t));
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
  return (struct square_matrix) { n - 1, res };
}

int64_t det2x2(struct square_matrix *M) {
  size_t** a = M->arr;
  return (int64_t)a[0][0] * a[1][1] - a[0][1] * a[1][0];
}

int64_t det3x3(struct square_matrix *M) {
  size_t** a = M->arr;
  return (int64_t)a[0][0] * a[1][1] * a[2][2]
    + a[0][1] * a[1][2] * a[2][0]
    + a[0][2] * a[1][0] * a[2][1]
    - a[0][2] * a[1][1] * a[2][0]
    - a[0][1] * a[1][0] * a[2][2]
    - a[0][0] * a[1][2] * a[2][1];
}

int64_t det4x4(struct square_matrix* M) {
  size_t** a = M->arr;
  size_t n = 4;
  int64_t res = 0, coef = 1;
  for (size_t i = 0; i < n; i++) {
    struct square_matrix cur_minor = minor(M, 0, i);
    res += coef * a[0][i] * det3x3(&cur_minor);
    coef *= -1;
  }
  return res;
}

int64_t det(struct square_matrix* M) {
  if (M->n == 2) return det2x2(M);
  if (M->n == 3) return det3x3(M);
  if (M->n == 4) return det4x4(M);
  printf("ÎØÈÁÊÀ ÎÏĞÅÄÅËÈÒÅËß\n");
  return -1;
}

double** transpose(double** arr, size_t n) {
  double** res = (double**)malloc(n * sizeof(double*));
  for (size_t i = 0; i < n; i++)
    res[i] = (double*)malloc(n * sizeof(double));
  for (size_t i = 0; i < n; i++) {
    for (size_t j = 0; j < n; j++) {
      res[i][j] = arr[j][i];
    }
  }
  return res;
}

double** invert(struct square_matrix* M) {
  size_t n = M->n;
  double** res = (double**)malloc(n * sizeof(double*)), coef;
  for (size_t i = 0; i < n; i++)
    res[i] = (double*)malloc(n * sizeof(double));

  for (size_t i = 0; i < n; i++) {
    for (size_t j = 0; j < n; j++) {
      if (i % 2 != j % 2) {
        coef = -1.0;
      }
      else coef = 1.0;
      struct square_matrix minorr = minor(M, i, j);
      res[i][j] = det(&minorr) * coef;
    }
  }
  // transpose
  res = transpose(res, n);
  // multiply to 1/det
  double determ = (double)det(M);
  if (determ == 0) {
    printf("ÌÀÒĞÈÖÀ ÍÅÎÁĞÀÒÈÌÀ\n");
    return NULL;
  }
  determ = 1.0 / determ;
  for (size_t i = 0; i < n; i++) {
    for (size_t j = 0; j < n; j++) {
      res[i][j] = determ * (double)res[i][j];
    }
  }
  return res;
}

