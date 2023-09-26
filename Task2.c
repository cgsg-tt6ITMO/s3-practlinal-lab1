#include "hill.h"

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
  struct square_matrix m = matr_gen(m);
  char* c1 = cypher(m, s1),
    *c2 = cypher(m, s2);

}