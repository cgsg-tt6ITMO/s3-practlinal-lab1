#include "headers/hill.h"

struct square_matrix matr_gen() {
  struct square_matrix
    m = matr2x2((size_t[2][2]) {
      {17, 3},
      { 2, 1 }});
  return m;
}

int main() {
  char* s1 = "недвенадцать",
    *s2 = "троицкаятома";
  struct square_matrix m = matr_gen();
  char* c1 = cypher(&m, s1),
    *c2 = cypher(&m, s2);

  // 1. разбить на функции кодирование и декодирование
  // 2. перевести в числа массивы c1, s1
  // 3. разбить их на векторы длины 2
  // 4. по шести уравнениям найти 4 числа обратной матрицы
  // 5. дешифровать второе сообщение (нужна только обратная матрица)
}