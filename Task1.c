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

void cypher(struct square_matrix m, size_t* message) {
  // 1. разбить вектор на векторы нужной длины
  size_t vec_size = m.n, num_of_vec = message_len / vec_size;
  struct vec* vectors = (struct vec*) malloc(num_of_vec * sizeof(struct vec));
  for (size_t i = 0; i < num_of_vec; i++) {
    size_t* tmp = (size_t*) malloc(vec_size * sizeof(size_t));
    for (size_t j = 0; j < vec_size; j++) {
      tmp[j] = message[i * vec_size + j];
    }
    *(vectors + i) = (struct vec){vec_size, tmp};
  }
  // 2. провести умножение
  struct vec* multipied = (struct vec*)malloc(num_of_vec * sizeof(struct vec));
  for (size_t i = 0; i < num_of_vec; i++) {
    *(multipied + i) = matr_mul_vec(m, *(vectors + i));
  }
  // 3. декодировать полученный вектор
  // 4. вывести результат
  char* res = (char*)malloc(vec_size * sizeof(char));
  for (size_t i = 0; i < num_of_vec; i++) {
    for (size_t j = 0; j < vec_size; j++) {
      struct vec veci = multipied[i];
      *(res + i * vec_size + j) = get_letter((veci.v)[j]);
      printf("%c", get_letter((veci.v)[j]));
    }
  }
  printf("\n\n");
}

int main() {
  system("chcp 1251");
  char secret[] = "великийаллах";
  size_t* nums = (size_t*) malloc(message_len * sizeof(size_t));
  for (size_t i = 0; i < message_len; i++) {
    nums[i] = get_number(secret[i]);
    //printf("%c", secret[i]);
  }
  printf("\n");
  struct vec secr = (struct vec){ 12, nums };

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

  // зашифровать три раза тремя путями
  cypher(m2, nums);
  cypher(m3, nums);
  cypher(m4, nums);
  getchar();
  return 0;
}
