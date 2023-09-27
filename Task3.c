#include <stdio.h>
#include <stdlib.h>

#define abc_size 32
#define code_len 5

struct map* abc;

void print_str(size_t* s) {
  for (size_t i = 0; i < 20; i++) {
    printf("%zu", *(s + i));
  }
  printf(" ");
}

struct matrix {
  size_t n, m;
  size_t** arr;
};

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

size_t* get_letter_code(char letter) {
  for (size_t i = 0; i < abc_size; i++)  {
    if (abc[i].letter == letter) {
      return abc[i].code;
    }
  }
  printf("THERE'S NO SUCH LETTER\n");
  return NULL;
}

int main() {
  system("chcp 1251");
  abc_init();
  size_t message_len = 4;
  char* word = "����";
  size_t* nums = (size_t*)malloc(sizeof(size_t) * message_len * code_len);

  for (size_t i = 0; i < message_len; i++) {
    size_t* tmp = get_letter_code(word[i]);
    for (size_t j = 0; j < code_len; j++) {
      *(nums + code_len * i + j) = tmp[j];
    }
  }
  print_str(nums);
  return 0;
}
