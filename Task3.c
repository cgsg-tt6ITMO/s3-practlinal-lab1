#include <stdio.h>
#include <stdlib.h>

#define abc_size 32

struct map* abc;

void print_str(size_t* s) {
  for (size_t i = 0; i < 5; i++) {
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
  size_t n = 5;
  size_t* code = (size_t*)malloc(sizeof(size_t) * n);
  for (size_t i = 0; i < n; i++) {
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
  abc[i++] = map("00000", 'à');
  abc[i++] = map("00001", 'á');
  abc[i++] = map("00010", 'â');
  abc[i++] = map("00011", 'ã');
  abc[i++] = map("00100", 'ä');
  abc[i++] = map("00101", 'å');
  abc[i++] = map("00110", 'æ');
  abc[i++] = map("00111", 'ç');
  abc[i++] = map("01000", 'è');
  abc[i++] = map("01001", 'é');
  abc[i++] = map("01010", 'ê');
  abc[i++] = map("01011", 'ë');
  abc[i++] = map("01100", 'ì');
  abc[i++] = map("01101", 'í');
  abc[i++] = map("01110", 'î');
  abc[i++] = map("01111", 'ï');
  abc[i++] = map("10000", 'ð');
  abc[i++] = map("10001", 'ñ');
  abc[i++] = map("10010", 'ò');
  abc[i++] = map("10011", 'ó');
  abc[i++] = map("10100", 'ô');
  abc[i++] = map("10101", 'õ');
  abc[i++] = map("10110", 'ö');
  abc[i++] = map("10111", '÷');
  abc[i++] = map("11000", 'ø');
  abc[i++] = map("11001", 'ù');
  abc[i++] = map("11010", 'ú');
  abc[i++] = map("11011", 'û');
  abc[i++] = map("11100", 'ü');
  abc[i++] = map("11101", 'ý');
  abc[i++] = map("11110", 'þ');
  abc[i++] = map("11111", 'ÿ');
}

int main() {
  system("chcp 1251");
  abc_init();
  for (size_t i = 0; i < abc_size; i++) {
    print_str(abc[i].code);
    printf("%c\n", abc[i].letter);
  }

  return 0;
}
