#include "structs.h"

char abc[] = "אבגדהוזחטיךכלםמןנסעףפץצקרûü‎‏ÿ";

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
    printf("ÝÒÓ ÌÀÒÐÈÖÓ È ÂÅÊÒÎÐ ÍÅËÜÇ‗ ÏÅÐÅÌÍÎÆÀÒÜ\n");
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

