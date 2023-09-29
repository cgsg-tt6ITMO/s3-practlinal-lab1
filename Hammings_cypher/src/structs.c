#include "headers/structs.h"

// вывести в консоль массив size_t длины n
void print_str(size_t* s, size_t n) {
  for (size_t i = 0; i < n; i++) {
    printf("%zu", *(s + i));
  }
  printf(" ");
}

// вывести в консоль массив символов длины 4
void print_string(char* s) {
  for (size_t i = 0; i < 4; i++) {
    printf("%c", *(s + i));
  }
  printf("\n\n");
}

// вывести в консоль значени€ координат вектора (struct vec)
void print_vec(struct vec* v) {
  for (size_t i = 0; i < v->n; i++) {
    printf("%zu ", *(v->v + i));
  }
  printf("\n");
}

size_t equals(size_t* a, size_t* b) {
  for (size_t i = 0; i < 5; i++) {
    if (a[i] != b[i]) return 0;
  }
  return 1;
}

// функци€ дл€ более быстрого создани€ пары код - буква
struct map map(char* c, char letter) {
  size_t* code = (size_t*)malloc(sizeof(size_t) * code_len);
  for (size_t i = 0; i < code_len; i++) {
    if (c[i] == '0') {
      code[i] = 0;
    }
    else if (c[i] == '1')
      code[i] = 1;
  }
  return (struct map) { code, letter };
}

// умножает по модулю 2 неквадратную матрицу на вектор
struct vec nonsquare_matr_mul_vec(struct matrix* M, struct vec* V) {
  size_t res_n = M->n;
  size_t* res = (size_t*)malloc(res_n * sizeof(size_t));
  // проверка совместимости размеров матрицы и вектора
  size_t n = V->n;
  if (M->m != n) {
    printf("Ё“” ћј“–»÷” » ¬≈ “ќ– Ќ≈Ћ№«я ѕ≈–≈ћЌќ∆ј“№\n");
    printf("matr %zu vec %zu\n", M->m, n);
    return (struct vec) { 0, NULL };
  }
  size_t** m = M->arr, * v = V->v;
  for (size_t i = 0; i < res_n; i++) {
    res[i] = 0;
    for (size_t j = 0; j < n; j++) {
      res[i] += m[i][j] * v[j];
    }
    res[i] = (res[i]) % 2;
  }
  return (struct vec) { res_n, res };
}

// возвращает транспонированную матрицу
struct matrix transpose(struct matrix m) {
  // выделить пам€ть
  size_t** res = (size_t**)malloc(m.m * sizeof(size_t*));
  for (size_t i = 0; i < m.n; i++)
    res[i] = (size_t*)malloc(m.n * sizeof(size_t));
  // найти транспонированную матрицу
  for (size_t i = 0; i < m.m; i++) {
    for (size_t j = 0; j < m.n; j++) {
      res[i][j] = m.arr[j][i];
    }
  }
  return (struct matrix) { m.m, m.n, res };
}

