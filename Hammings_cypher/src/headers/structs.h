#pragma once

#include <stdio.h>
#include <stdlib.h> // malloc
#include <time.h>

#define abc_size 32
#define code_len 5

struct matrix {
  size_t n, m;
  size_t** arr;
};

struct vec {
  size_t n;
  size_t* v;
};

struct map {
  size_t* code;
  char letter;
};

void print_str(size_t* s, size_t n);
void print_string(char* s);
void print_vec(struct vec* v);

size_t equals(size_t* a, size_t* b);
struct map map(char* c, char letter);

struct vec nonsquare_matr_mul_vec(struct matrix* M, struct vec* V);
struct matrix transpose(struct matrix m);

