#include "headers/structs.h"

struct map* abc;

// ������� ������ ��� ����-�������� ��� ����� � � ��������� ����
void abc_init(void) {
  abc = (struct map*)malloc(abc_size * sizeof(struct map));
  size_t i = 0;
  abc[i++] = map("00000", '�');
  abc[i++] = map("00001", '�');
  abc[i++] = map("00010", '�');
  abc[i++] = map("00011", '�');
  abc[i++] = map("00100", '�');
  abc[i++] = map("00101", '�');
  abc[i++] = map("00110", '�');
  abc[i++] = map("00111", '�');
  abc[i++] = map("01000", '�');
  abc[i++] = map("01001", '�');
  abc[i++] = map("01010", '�');
  abc[i++] = map("01011", '�');
  abc[i++] = map("01100", '�');
  abc[i++] = map("01101", '�');
  abc[i++] = map("01110", '�');
  abc[i++] = map("01111", '�');
  abc[i++] = map("10000", '�');
  abc[i++] = map("10001", '�');
  abc[i++] = map("10010", '�');
  abc[i++] = map("10011", '�');
  abc[i++] = map("10100", '�');
  abc[i++] = map("10101", '�');
  abc[i++] = map("10110", '�');
  abc[i++] = map("10111", '�');
  abc[i++] = map("11000", '�');
  abc[i++] = map("11001", '�');
  abc[i++] = map("11010", '�');
  abc[i++] = map("11011", '�');
  abc[i++] = map("11100", '�');
  abc[i++] = map("11101", '�');
  abc[i++] = map("11110", '�');
  abc[i++] = map("11111", '�');
}

// �������� �������� ��� �� 5 �������� ��� �����
size_t* get_letter_code(char letter) {
  for (size_t i = 0; i < abc_size; i++) {
    if (abc[i].letter == letter) {
      return abc[i].code;
    }
  }
  printf("THERE'S NO SUCH LETTER\n");
  return NULL;
}

// �������� ����� �� ������� 5 �������� ��������
char get_letter(size_t* code) {
  for (size_t i = 0; i < abc_size; i++) {
    if (equals(code, abc[i].code))
      return abc[i].letter;
  }
  printf("����� ����� ���\n");
  return 0;
}

// ������� ��� ����������� ������� ������� ��������
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

// �� ��������� ������� �������� �������� ���������� ��� �� ������ � 1 ���������
size_t* typo(size_t* message) {
  size_t message_len = 35;
  size_t i1 = rand() % message_len;
  printf("typo index: %zu\n", i1);
  message[i1] = (message[i1] + 1) % 2;
  return message;
}

// �������� ����� �� ������ ����, ���������� ������ �� 35 �������� ��������
size_t* encoding(char* word) {
  size_t mes_len = 4;
  // ������ �� ����� �� ����
  size_t* nums = (size_t*)malloc(sizeof(size_t) * mes_len * code_len);
  for (size_t i = 0; i < mes_len; i++) {
    size_t* tmp = get_letter_code(word[i]);
    for (size_t j = 0; j < code_len; j++) {
      nums[code_len * i + j] = tmp[j];
    }
  }
  // ��������� �� ������� ����� 4
  struct vec* orig_vecs = vecs(nums, 4, 5);
  // ����� ������� G
  size_t matr_G[7][4] = {
    {1, 1, 0, 1},
    {1, 0, 1, 1},
    {1, 0, 0, 0},
    {0, 1, 1, 1},
    {0, 1, 0, 0},
    {0, 0, 1, 0},
    {0, 0, 0, 1}
  };
  // �������� ������, ���������� ������ � ������� ���������, ������������ ������
  size_t** G = (size_t**)malloc(7 * sizeof(size_t*));
  for (size_t i = 0; i < 7; i++)
    G[i] = (size_t*)malloc(4 * sizeof(size_t));
  for (size_t i = 0; i < 7; i++) {
    for (size_t j = 0; j < 4; j++) {
      G[i][j] = matr_G[i][j];
    }
  }
  // ����������� ������� ��������� � ���������
  struct matrix key = (struct matrix){ 7, 4, G };
  // �������� ������� �� ������� ����� 4 � �������� ������� ����� 7
  struct vec* multiplied = (struct vec*)malloc(5 * sizeof(struct vec));
  for (size_t i = 0; i < 5; i++) {
    *(multiplied + i) = nonsquare_matr_mul_vec(&key, orig_vecs + i);
  }
  // �������� �������� � �������������� �������
  printf("vec:\n");
  for (size_t i = 0; i < 5; i++) {
    print_vec(&orig_vecs[i]);
    print_vec(&multiplied[i]);
  }
  printf("\n");
  // ��������� ������� � ���� ������ �� 35 �������� ��������
  size_t* encoded = (size_t*)malloc(35 * sizeof(size_t));
  for (size_t i = 0; i < 5; i++) {
    for (size_t j = 0; j < 7; j++) {
      encoded[i * 7 + j] = (multiplied[i]).v[j];
    }
  }
  return encoded;
}

// 35 �������� �������� ���������� � ����� ����� 4
char* decode(size_t* encoded) {
  struct vec* v = check_parity_bits(encoded);
  // �������� ��� �� ����������� ����
  size_t multiplied[5][4];
  for (size_t i = 0; i < 5; i++) {
    multiplied[i][0] = v[i].v[2];
    multiplied[i][1] = v[i].v[4];
    multiplied[i][2] = v[i].v[5];
    multiplied[i][3] = v[i].v[6];
  }
  // ��������� 5 �������� ����� 4
  size_t* encoded = (size_t*)malloc(20 * sizeof(size_t));
  for (size_t i = 0; i < 5; i++) {
    for (size_t j = 0; j < 4; j++) {
      encoded[i * 4 + j] = multiplied[i][j];
    }
  }
  for (size_t i = 0; i < 4; i++) {
    for (size_t j = 0; j < 5; j++) {
      encoded[i * 5 + j];
    }
  }
  // ������� �� 4 �����
  char* res = (char*)malloc(4 * sizeof(char));
  for (size_t i = 0; i < 4; i++) {
    size_t* tmp = (size_t*)malloc(5 * sizeof(size_t));
    for (size_t j = 0; j < 5; j++) {
      tmp[j] = encoded[i * 5 + j];
    }
    res[i] = get_letter(tmp);
  }
  return res;
}

// ��������� ���������� �������� ���, ���������� ����� ������, � �����
size_t number(size_t* binary) {
  if (binary[0] == 0 && binary[1] == 0 && binary[2] == 0)
    return 0;
  if (binary[0] == 1 && binary[1] == 1 && binary[2] == 1)
    return 7;
  if (binary[0] == 0 && binary[1] == 1 && binary[2] == 1)
    return 6;
  if (binary[0] == 1 && binary[1] == 0 && binary[2] == 1)
    return 5;
  if (binary[0] == 0 && binary[1] == 0 && binary[2] == 1)
    return 4;
  if (binary[0] == 1 && binary[1] == 1 && binary[2] == 0)
    return 3;
  if (binary[0] == 0 && binary[1] == 1 && binary[2] == 0)
    return 2;
  if (binary[0] == 1 && binary[1] == 0 && binary[2] == 0)
    return 1;
}

// ���������, ���� �� ��������. ���������� ������� ��� ��������
struct vec* check_parity_bits(size_t* encoded) {
  // �������, ������������, �� ����� ���� �������� ����� ��� ��������
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

  size_t num_of_vec = 5, vec_size = 7;
  // ���� �������� ����������� ������� �� �������, ������ � ������ ���������� ��� ����
  struct vec* decipher = (struct vec*)malloc(num_of_vec * sizeof(struct vec));
  // ���� ������� ������� encoded �� ������� ����� 7
  struct vec* vectors = (struct vec*)malloc(num_of_vec * sizeof(struct vec));
  for (size_t i = 0; i < num_of_vec; i++) {
    size_t* tmp = (size_t*)malloc(vec_size * sizeof(size_t));
    for (size_t j = 0; j < vec_size; j++) {
      tmp[j] = encoded[i * vec_size + j];
    }
    *(vectors + i) = (struct vec){ vec_size, tmp };
  }
  // �������� ������� �� ����������� �������, ������� ������ �������� ������
  // (� �������� ������� ���������� 3 �������� �������)
  for (size_t i = 0; i < 5; i++) {
    *(decipher + i) = nonsquare_matr_mul_vec(&H, vectors + i);
  }
  for (size_t i = 0; i < 5; i++) {
    size_t typo = number(decipher[i].v);
    print_vec(&decipher[i]);
    // ���� ���� ������, ���������� 1 � ���� �� ������ 2 (1->0, 0->1)
    if (typo != 0) {
      vectors[i].v[typo - 1] += 1;
      vectors[i].v[typo - 1] %= 2;
    }
  }
  return vectors;
}

int main() {
  system("chcp 1251");
  srand(clock());
  abc_init();
  char* word = "����";
  // �������� �����
  size_t* encoded = encoding(word);
  print_str(encoded, 35);
  printf("\n");
  // ��������� 3 ��������
  encoded = typo(typo(typo(encoded)));
  print_str(encoded, 35);
  printf("\n");
  // �������� ��������� �������������
  print_string(decode(encoded));

  return 0;
}
