#include <stdio.h>
#include <stdlib.h>

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
  abc[i++] = map("11111", 'я');
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
  char* word = "тома";
  size_t* nums = (size_t*)malloc(sizeof(size_t) * message_len * code_len);

  for (size_t i = 0; i < message_len; i++) {
    size_t* tmp = get_letter_code(word[i]);
    for (size_t j = 0; j < code_len; j++) {
      nums[code_len * i + j] = tmp[j];
    }
  }

  size_t* result = (size_t*)malloc(25 * sizeof(size_t));
  // индексы
  size_t p1 = 1, p2 = 2, p3 = 4, p4 = 8, p5 = 16;
  p1--;
  p2--;
  p3--;
  p4--;
  p5--;
  size_t s1, s2, s3, s4, s5;
  size_t cnt = 0;
  for (size_t i = 0; i < 25; i++) {
    if (i != p1 && i != p2 && i != p3 && i != p4 && i != p5) {
      result[i] = nums[cnt++];
    }
  }

  // посчитать p

  s1 = (nums[0] + nums[1] + nums[3] + nums[4] + nums[6] + nums[8] +
    nums[10] + nums[11] + nums[13] + nums[15] + nums[17] + nums[19]) % 2;
  s2 = (nums[0] + nums[2] + nums[3] + nums[5] + nums[6] + nums[9] +
    nums[10] + nums[12] + nums[13] + nums[16] + nums[17]) % 2;
  s3 = (nums[1] + nums[2] + nums[3] + nums[7] + nums[8] + nums[9] +
    nums[10] + nums[14] + nums[15] + nums[16] + nums[17]) % 2;
  s4 = (nums[4] + nums[5] + nums[6] + nums[7] + nums[8] + nums[9] +
    nums[10] + nums[18] + nums[19]) % 2;
  s5 = (nums[11] + nums[12] + nums[13] + nums[14] + nums[15] + nums[16] + 
    nums[17] + nums[18] + nums[19]) % 2;
 
  return 0;
}
