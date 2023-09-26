#include "headers/structs.h"

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

char* cypher(struct square_matrix m, char* s) {
  size_t* message = (size_t*)malloc(message_len * sizeof(size_t));
  for (size_t i = 0; i < message_len; i++) {
    message[i] = get_number(s[i]);
  }
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
  char* res = (char*)malloc(vec_size * sizeof(char));
  for (size_t i = 0; i < num_of_vec; i++) {
    for (size_t j = 0; j < vec_size; j++) {
      struct vec veci = multipied[i];
      *(res + i * vec_size + j) = get_letter((veci.v)[j]);
    }
  }
  return res;
}

char* decypher(struct square_matrix *m, char* cyphr) {
  size_t vec_size = m->n, num_of_vec = message_len / vec_size;
  // 0. сделать из сообщения массив чисел
  size_t* nums = (size_t*)malloc(message_len * sizeof(size_t));
  for (size_t i = 0; i < message_len; i++) {
    nums[i] = get_number(cyphr[i]);
  }
  // 1. найти матрицу, обратную к ключевой
  struct square_matrix inv = invert(m);
  // 2. разбить массив чисел в много маленьких
  // массив векторов шифра:
  struct vec* cypher_vecs = (struct vec*)malloc(num_of_vec * sizeof(struct vec));
  for (size_t i = 0; i < num_of_vec; i++) {
    size_t* tmp = (size_t*)malloc(vec_size * sizeof(size_t));
    for (size_t j = 0; j < vec_size; j++) {
      tmp[j] = nums[i * vec_size + j];
    }
    cypher_vecs[i] = (struct vec){vec_size, tmp};
  }
  // 3. умножить обратную матрицу на конечный вектор
  // массив векторов исходного сообщения
  struct vec* multipied = (struct vec*)malloc(num_of_vec * sizeof(struct vec));
  for (size_t i = 0; i < num_of_vec; i++) {
    *(multipied + i) = matr_mul_vec(inv, *(cypher_vecs + i));
  }
  // 4. декодировать полученный вектор
  char* res = (char*)malloc(vec_size * sizeof(char));
  for (size_t i = 0; i < num_of_vec; i++) {
    for (size_t j = 0; j < vec_size; j++) {
      struct vec veci = multipied[i];
      *(res + i * vec_size + j) = get_letter((veci.v)[j]);
    }
  }
  return res;
}

char* tree_typos(char* message) {
  size_t i1 = rand() % message_len, i2 = rand() % (message_len - i1 - 1), i3 = i2 + rand() % (message_len - i2);
  *(message + i1) = get_letter(rand() % abc_len);
  *(message + i2) = get_letter(rand() % abc_len);
  *(message + i3) = get_letter(rand() % abc_len);
  return message;
}

int main1() {
  system("chcp 1251");
  char* secret = "великийаллах";

  size_t a3[3][3] = {
    {1,0,0},
    {4,7,0},
    {7,8,11}
  };
  size_t a4[4][4] = {
    {7, 0, 0, 0},
    {3, 11, 0, 0},
    {-1, 0, 13, 0},
    {8, 21, 1, 29}
  };

  struct square_matrix
    m2 = matr2x2((size_t[2][2]) { {29, 0}, {20, 1} }),
    m3 = matr3x3(a3),
    m4 = matr4x4(a4);

  // зашифровать три раза тремя путями
  char* c2 = cypher(m2, secret);
  char* c3 = cypher(m3, secret);
  char* c4 = cypher(m4, secret);

  char* t2 = tree_typos(c2);
  char* t3 = tree_typos(c3);
  char* t4 = tree_typos(c4);

  print_string(c2);
  print_string(c3);
  print_string(c4);

  printf("дешифровка:\n");
  print_string(decypher(&m2, t2));
  print_string(decypher(&m3, t3));
  print_string(decypher(&m4, t4));

  return 0;
}
