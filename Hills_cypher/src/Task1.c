#include "headers/structs.h"

// возвращает букву по номеру
char get_letter(size_t s) {
  if (s >= 0 && s < abc_len)
    return abc[s];
  return -1;
}

// возвращает номер буквы в заданном алфавите
size_t get_number(char letter) {
  for (size_t i = 0; i < 30; i++) {
    if (letter == abc[i]) {
      return i;
    }
  }
  printf("there is no such letter\n");
  return -1;
}

// перевести массив векторов в массив букв
char* nums_to_string(struct vec* vectors, size_t vec_size, size_t num_of_vec) {
  char* res = (char*)malloc(vec_size * sizeof(char));
  for (size_t i = 0; i < num_of_vec; i++) {
    for (size_t j = 0; j < vec_size; j++) {
      *(res + i * vec_size + j) = get_letter((vectors[i].v)[j]);
    }
  }
  return res;
}

// превратить массив char в массив векторов нужной длины
struct vec* vectors(char* s, size_t vec_size, size_t num_of_vec) {
  struct vec* vectors = (struct vec*)malloc(num_of_vec * sizeof(struct vec));
  for (size_t i = 0; i < num_of_vec; i++) {
    size_t* tmp = (size_t*)malloc(vec_size * sizeof(size_t));
    for (size_t j = 0; j < vec_size; j++) {
      tmp[j] = get_number(s[i * vec_size + j]);
    }
    *(vectors + i) = (struct vec){ vec_size, tmp };
  }
  return vectors;
}

// зашифровывает слово методом Хилла по заданной матрице-ключу
char* cypher(struct square_matrix *m, char* s) {
  size_t vec_size = m->n, num_of_vec = message_len / vec_size;
  struct vec* vecs = vectors(s, vec_size, num_of_vec);
  struct vec* multipied = (struct vec*)malloc(num_of_vec * sizeof(struct vec));
  for (size_t i = 0; i < num_of_vec; i++) {
    *(multipied + i) = matr_mul_vec(m, vecs + i);
  }
  return nums_to_string(multipied, vec_size, num_of_vec);
}

// обращает матрицу-ключ и дешифрует сообщение
char* decypher(struct square_matrix *m, char* cyphr) {
  struct square_matrix inv = invert(m);
  return cypher(&inv, cyphr);
}

// добавить 3 опечатки в сообщение
char* tree_typos(char* message) {
  size_t i1 = rand() % message_len, i2 = rand() % (message_len - i1 - 1), i3 = i2 + rand() % (message_len - i2);
  *(message + i1) = get_letter(rand() % abc_len);
  *(message + i2) = get_letter(rand() % abc_len);
  *(message + i3) = get_letter(rand() % abc_len);
  return message;
}

int main1() {
  // кодировка
  system("chcp 1251");
  // кодируемое слово
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
  char 
    *c2 = cypher(&m2, secret),
    *c3 = cypher(&m3, secret),
    *c4 = cypher(&m4, secret);
  // добавить по 3 опечатки в каждое сообщение
  char
    *t2 = tree_typos(c2),
    *t3 = tree_typos(c3),
    *t4 = tree_typos(c4);
  // напечатать строки с опечатками
  print_string(c2);
  print_string(c3);
  print_string(c4);
  // напечатать результат дешифровки строк с опечатками
  printf("дешифровка:\n");
  print_string(decypher(&m2, c2));
  print_string(decypher(&m3, c3));
  print_string(decypher(&m4, c4));

  return 0;
}
