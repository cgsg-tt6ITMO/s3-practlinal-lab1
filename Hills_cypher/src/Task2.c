#include "headers/hill.h"

size_t equal_vec(struct vec cyph, struct vec orig) {
  if (cyph.n != orig.n) return 0;
  for (size_t i = 0; i < cyph.n; i++) {
    if (cyph.v[i] != orig.v[i]) return 0;
  }
  return 1;
}

struct square_matrix matr_gen() {
  struct square_matrix
    m = matr2x2((size_t[2][2]) {
      {17, 3},
      { 2, 1 }});
  return m;
}

struct square_matrix hack_key_dumb_edition(struct vec* cyph, struct vec* orig) {
  size_t flag = 1;
  for (size_t i1 = 0; i1 < abc_len; i1++) {
    for (size_t i2 = 0; i2 < abc_len; i2++) {
      for (size_t i3 = 0; i3 < abc_len; i3++) {
        for (size_t i4 = 0; i4 < abc_len; i4++) {
          flag = 1;
          struct square_matrix mbres = matr2x2((size_t[2][2]) { {i1, i2}, { i3, i4 } });
          for (size_t i5 = 0; i5 < message_len / 2; i5++) {
            struct vec mul = matr_mul_vec(&mbres, (cyph + i5));
            if (!equal_vec(mul, *(orig + i5))) flag = 0;
          }
          if (flag)
            return mbres;
        }
      }
    }
  }
  printf("NO RESULT\n");
  return (struct square_matrix) { 0, NULL };
}

int main() {
  system("chcp 1251");
  size_t vec_size = 2;
  char* s1 = "недвенадцать",
    *s2 = "троицкаятома";
  struct square_matrix m = matr_gen();
  char* c1 = cypher(&m, s1),
    *c2 = cypher(&m, s2);

  struct vec* cyf1 = vectors(s1, vec_size, message_len / vec_size),
    * decyf1 = vectors(c1, vec_size, message_len / vec_size);

  struct square_matrix inv = hack_key_dumb_edition(decyf1, cyf1);
  print_matr(&inv);
  print_string(cypher(&inv, c2));
  return 0;
}
