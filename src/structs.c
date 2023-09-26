#include "headers/structs.h"

char abc[] = "àáâãäåæçèéêëìíîïğñòóôõö÷øûüışÿ";

void print(size_t s) {
  printf("%zu ", s);
}

void print_int64_t(int64_t s) {
  printf("%" PRId64 " ", s);
}

void print_string(char* s) {
  for (size_t i = 0; i < message_len; i++) {
    printf("%c", *(s + i));
  }
  printf("\n\n");
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
    printf("matr %zu vec %zu\n", M.n, n);
    return (struct vec) { 0, NULL };
  }
  size_t** m = M.arr, * v = V.v;
  size_t* res = (size_t*)malloc(n * sizeof(size_t));
  for (size_t i = 0; i < n; i++) {
    res[i] = 0;
    for (size_t j = 0; j < n; j++) {
      res[i] += mod_abc_len((m[i][j] * v[j]));
    }
    res[i] = mod_abc_len(res[i]);
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
  if (M->n == 1) return (M->arr)[0][0];
  if (M->n == 2) return det2x2(M);
  if (M->n == 3) return det3x3(M);
  if (M->n == 4) return det4x4(M);
  printf("ÎØÈÁÊÀ ÎÏĞÅÄÅËÈÒÅËß\n");
  return -1;
}

int64_t** transpose(int64_t** arr, size_t n) {
  int64_t** res = (int64_t**)malloc(n * sizeof(int64_t*));
  for (size_t i = 0; i < n; i++)
    res[i] = (int64_t*)malloc(n * sizeof(int64_t));
  for (size_t i = 0; i < n; i++) {
    for (size_t j = 0; j < n; j++) {
      res[i][j] = arr[j][i];
    }
  }
  return res;
}

int64_t mod_abc_len(int64_t a) {
  if (a >= 0) return a % abc_len;
  while (a < 0) a += abc_len;
  return a % abc_len;
}

int64_t inv_mod(int64_t a) {
  for (size_t i = 0; i < abc_len; i++) {
    if (mod_abc_len(a * i) == 1)
      return i;
  }
  return -1;
}

struct square_matrix invert(struct square_matrix* M) {
  size_t n = M->n;
  int64_t** res = (int64_t**)malloc(n * sizeof(int64_t*)), coef;
  for (size_t i = 0; i < n; i++)
    res[i] = (int64_t*)malloc(n * sizeof(int64_t));
  // adjusted
  for (size_t i = 0; i < n; i++) {
    for (size_t j = 0; j < n; j++) {
      if (i % 2 != j % 2) {
        coef = -1;
      }
      else coef = 1;
      struct square_matrix minorr = minor(M, i, j);
      res[i][j] = mod_abc_len(det(&minorr) * coef);
    }
  }
  // transpose
  res = transpose(res, n);
  // multiply to inv to det
  int64_t determ = inv_mod(mod_abc_len(det(M)));
  if (determ == -1) {
    printf("ÌÀÒĞÈÖÀ ÍÅÎÁĞÀÒÈÌÀ\n");
    return (struct square_matrix) { 0, NULL };
  }
  for (size_t i = 0; i < n; i++) {
    for (size_t j = 0; j < n; j++) {
      res[i][j] = mod_abc_len(determ * res[i][j]);
    }
  }
  return (struct square_matrix) { n, res };
}

