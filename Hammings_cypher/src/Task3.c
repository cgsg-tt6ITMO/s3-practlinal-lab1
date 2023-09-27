#include <stdio.h>
#include <stdlib.h> // malloc
#include <time.h>

#define abc_size 32
#define code_len 5

struct map* abc;

void print_str(size_t* s, size_t n) {
  for (size_t i = 0; i < n; i++) {
    printf("%zu", *(s + i));
  }
  printf(" ");
}

struct matrix {
  size_t n, m;
  size_t** arr;
};

struct vec {
  size_t n;
  size_t* v;
};

void print_vec(struct vec* v) {
  for (size_t i = 0; i < v->n; i++) {
    printf("%zu ", *(v->v + i));
  }
  printf("\n");
}

// m 7x4, v 4
struct vec nonsquare_matr_mul_vec(struct matrix* M, struct vec* V) {
  size_t res_n = M->n;
  size_t* res = (size_t*)malloc(res_n * sizeof(size_t));

  // n = 4
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
      res[i] += (m[i][j] * v[j]);
    }
    res[i] = (res[i]) % 2;
  }
  return (struct vec) { res_n, res };
}

struct map {
  size_t* code;
  char letter;
};

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

void abc_init(void) {
  abc = (struct map*)malloc(abc_size * sizeof(struct map));
  size_t i = 0;
  abc[i++] = map("00000", 'а');
  abc[i++] = map("00001", 'б');
  abc[i++] = map("00010", 'в');
  abc[i++] = map("00011", 'г');
  abc[i++] = map("00100", 'д');
  abc[i++] = map("00101", 'е');
  abc[i++] = map("00110", 'ж');
  abc[i++] = map("00111", 'з');
  abc[i++] = map("01000", 'и');
  abc[i++] = map("01001", 'й');
  abc[i++] = map("01010", 'к');
  abc[i++] = map("01011", 'л');
  abc[i++] = map("01100", 'м');
  abc[i++] = map("01101", 'н');
  abc[i++] = map("01110", 'о');
  abc[i++] = map("01111", 'п');
  abc[i++] = map("10000", 'р');
  abc[i++] = map("10001", 'с');
  abc[i++] = map("10010", 'т');
  abc[i++] = map("10011", 'у');
  abc[i++] = map("10100", 'ф');
  abc[i++] = map("10101", 'х');
  abc[i++] = map("10110", 'ц');
  abc[i++] = map("10111", 'ч');
  abc[i++] = map("11000", 'ш');
  abc[i++] = map("11001", 'щ');
  abc[i++] = map("11010", 'ъ');
  abc[i++] = map("11011", 'ы');
  abc[i++] = map("11100", 'ь');
  abc[i++] = map("11101", 'э');
  abc[i++] = map("11110", 'ю');
  abc[i++] = map("11111", '€');
}

size_t* get_letter_code(char letter) {
  for (size_t i = 0; i < abc_size; i++) {
    if (abc[i].letter == letter) {
      return abc[i].code;
    }
  }
  printf("THERE'S NO SUCH LETTER\n");
  return NULL;
}

struct vec* vecs(size_t* s, size_t vec_size, size_t num_of_vec) {
  struct vec* vectors = (struct vec*)malloc(num_of_vec * sizeof(struct vec));
  for (size_t i = 0; i < num_of_vec; i++) {
    size_t* tmp = (size_t*)malloc(vec_size * sizeof(size_t));
    for (size_t j = 0; j < vec_size; j++) {
      tmp[j] = s[i * vec_size + j];
    }
    *(vectors + i) = (struct vec){ vec_size, tmp };
  }
  return vectors;
}

struct matrix transpose(struct matrix m) {
  size_t** res = (size_t**)malloc(m.n * sizeof(size_t*));
  for (size_t i = 0; i < m.m; i++)
    res[i] = (size_t*)malloc(m.m * sizeof(size_t));
  for (size_t i = 0; i < m.n; i++) {
    for (size_t j = 0; j < m.m; j++) {
      res[i][j] = m.arr[j][i];
    }
  }
  return (struct matrix) { m.m, m.n, res };
}

size_t* typo(size_t* message) {
  srand(clock());
  size_t message_len = 35;
  size_t i1 = rand() % message_len;
  printf("typo index: %zu\n", i1);
  message[i1] = (message[i1] + 1) % 2;
  return message;
}

size_t* encoding(char* word) {
  size_t mes_len = 4;
  // массив из чисел
  size_t* nums = (size_t*)malloc(sizeof(size_t) * mes_len * code_len);
  for (size_t i = 0; i < mes_len; i++) {
    size_t* tmp = get_letter_code(word[i]);
    for (size_t j = 0; j < code_len; j++) {
      nums[code_len * i + j] = tmp[j];
    }
  }
  // разбиваем на вектора длины 4
  struct vec* orig_vecs = vecs(nums, 4, 5);
  size_t matr_G[7][4] = {
    {1, 1, 0, 1},
    {1, 0, 1, 1},
    {1, 0, 0, 0},
    {0, 1, 1, 1},
    {0, 1, 0, 0},
    {0, 0, 1, 0},
    {0, 0, 0, 1}
  };
  size_t** G = (size_t**)malloc(7 * sizeof(size_t*));
  for (size_t i = 0; i < 7; i++)
    G[i] = (size_t*)malloc(4 * sizeof(size_t));
  for (size_t i = 0; i < 7; i++) {
    for (size_t j = 0; j < 4; j++) {
      G[i][j] = matr_G[i][j];
    }
  }
  struct matrix key = (struct matrix){ 7, 4, G };
  // умножаем матрицу на вектора и получаем вектора длины 7
  struct vec* multiplied = (struct vec*)malloc(5 * sizeof(struct vec));
  for (size_t i = 0; i < 5; i++) {
    *(multiplied + i) = nonsquare_matr_mul_vec(&key, orig_vecs + i);
  }
  printf("vec:\n");
  for (size_t i = 0; i < 5; i++) {
    print_vec(&orig_vecs[i]);
    print_vec(&multiplied[i]);
  }
  printf("\n");
  // склеить в один массив
  size_t* encoded = (size_t*)malloc(35 * sizeof(size_t));
  for (size_t i = 0; i < 5; i++) {
    for (size_t j = 0; j < 7; j++) {
      encoded[i * 7 + j] = (multiplied[i]).v[j];
    }
  }
  return encoded;
}

int main() {
  system("chcp 1251");
  abc_init();
  char* word = "тома";
  size_t* encoded = encoding(word);

  print_str(encoded, 35);
  printf("\n");
  encoded = /*typo(typo(typo(*/typo(encoded)/*)))*/;

  print_str(encoded, 35);
  printf("\n");
  // проверка кодов
  size_t matr_H[3][7] = {
    {1, 0, 1, 0, 1, 0, 1},
    {0, 1, 1, 0, 0, 1, 1},
    {0, 0, 0, 1, 1, 1, 1}
  };
  size_t** h = (size_t**)malloc(3 * sizeof(size_t*));
  for (size_t i = 0; i < 3; i++)
    h[i] = (size_t*)malloc(7 * sizeof(size_t));
  for (size_t i = 0; i < 3; i++) {
    for (size_t j = 0; j < 7; j++) {
      h[i][j] = matr_H[i][j];
    }
  }
  struct matrix H = (struct matrix){ 3, 7, h };

  size_t num_of_vec = 5 , vec_size = 7;
  // если умножить проверочную матрицу на векторы, должны в идеале получитьс€ все нули
  struct vec* decipher = (struct vec*)malloc(num_of_vec * sizeof(struct vec));
  // надо сначала разбить encoded на векторы длины 7
  struct vec* vectors = (struct vec*)malloc(num_of_vec * sizeof(struct vec));
  for (size_t i = 0; i < num_of_vec; i++) {
    size_t* tmp = (size_t*)malloc(vec_size * sizeof(size_t));
    for (size_t j = 0; j < vec_size; j++) {
      tmp[j] = encoded[i * vec_size + j];
    }
    *(vectors + i) = (struct vec){ vec_size, tmp };
  }
  
  for (size_t i = 0; i < 5; i++) {
    *(decipher + i) = nonsquare_matr_mul_vec(&H, vectors + i);
  }
  
  
  for (size_t i = 0; i < 5; i++) {
    print_vec(&decipher[i]);
  }
  
  return 0;
}
