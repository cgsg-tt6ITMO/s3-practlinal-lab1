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

char* cypher(struct square_matrix m, char* s) {
  size_t* message = (size_t*)malloc(message_len * sizeof(size_t));
  for (size_t i = 0; i < message_len; i++) {
    message[i] = get_number(s[i]);
    print(message[i]);
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

//char*
void decypher(struct square_matrix *m, char* cyphr) {
  size_t vect_len = m->n, num_vect = message_len / vect_len;
  // для дешифровки:
  // 0. сделать из сообщения массив чисел
  int64_t* nums = (int64_t*)malloc(message_len * sizeof(int64_t));
  for (size_t i = 0; i < message_len; i++) {
    nums[i] = (int64_t)get_number(cyphr[i]);
    print(nums[i]);
  }

  // 1. найти матрицу, обратную к ключевой
  printf("inv matr\n");
  struct square_matrix inv = invert(m);
  print_matr(&inv);
  /*
  for (size_t i = 0; i < vect_len; i++) {
    for (size_t j = 0; j < vect_len; j++) {
      printf("%f ", inv[i][j]);
    }
    printf("\n");
  }
  */

  // 2. разбить массив чисел в много маленьких
  // массив векторов шифра
  /*
  int64_t** cypher_vecs = (int64_t**)malloc(num_vect * sizeof(int64_t*));
  for (size_t i = 0; i < num_vect; i++)
    cypher_vecs[i] = (int64_t*)malloc(vect_len * sizeof(int64_t));

  for (size_t i = 0; i < num_vect; i++) {
    for (size_t j = 0; j < vect_len; j++) {
      *(*(cypher_vecs + i)+j) = nums[i * vect_len + j];
      //printf("%f ", cypher_vecs[i][j]);
    }
    //printf("\n");
  }

  // 3. умножить обратную матрицу на конечный вектор
  // массив векторов исходного сообщения
  int64_t** res = (int64_t**)malloc(num_vect * sizeof(int64_t*));
  for (size_t i = 0; i < num_vect; i++)
    res[i] = (int64_t*)malloc(vect_len * sizeof(int64_t));

  for (size_t k = 0; k < num_vect; k++) {
    for (size_t i = 0; i < vect_len; i++) {
      res[k][i] = 0;
      for (size_t j = 0; j < vect_len; j++) {
        res[k][i] += inv.arr[i][j] * cypher_vecs[k][j];
      }
      res[k][i] = res[k][i];
      //print(res[k][i]);
    }
  }
  char* decyph = (char *) malloc(message_len * sizeof(char));
  // 4. полученный вектор перевести в буквы
  for (size_t k = 0; k < num_vect; k++) {
    for (size_t i = 0; i < vect_len; i++) {
      print(res[k][i]);
    }
  }
  */
}

int main() {
  system("chcp 1251");
  char* secret = "великийаллах";

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
  char* c2 = cypher(m2, secret);
  char* c3 = cypher(m3, secret);
  char* c4 = cypher(m4, secret);

  print_string(c2);
  print_string(c3);
  print_string(c4);

  printf("дешифровка:\n");
  decypher(&m3, c3);

  getchar();
  return 0;
}
