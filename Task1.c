#include "structs.h"

char get_letter(size_t s) {
  if (s >= 0 && s < abc_len)
    return abc[s];
  return -1;
}

size_t get_number(char letter) {
  for (size_t i = 0; i < 30; i++) {
    if (letter == abc[i]) {
      return i;
    }
  }
  printf("there is no such letter\n");
  return -1;
}

int main() {
  char secret[] = "великийаллах";
  size_t* nums = (size_t*) malloc(N * sizeof(size_t));
  for (size_t i = 0; i < N; i++) {
    nums[i] = get_number(secret[i]);
  }
  struct vec secr = (struct vec){ 12, nums };
  print_vec(&secr);

  size_t a3[3][3] = {
    {1,0,0},
    {4,7,0},
    {7,8,11}
  };
  size_t a4[4][4] = {
    {37, 0, 0, 0},
    {3, 47, 0, 0},
    {-1, 0, 57, 0},
    {90, 21, 1, 7}
  };

  struct square_matrix
    m2 = matr2x2((size_t[2][2]) { {239, 0}, {50, 1} }),
    m3 = matr3x3(a3),
    m4 = matr4x4(a4);

  struct square_matrix
    test1 = matr3x3((size_t[3][3]) {
      {6, 24, 1},
      {13, 16, 10},
      {20, 17, 15}
  });
  struct vec
    test2 = vec3((size_t[3]) {0, 2, 19});

  struct vec res = matr_mul_vec(test1, test2);
  printf("vec: \n");
  print_vec(&res);

  return 0;
}
