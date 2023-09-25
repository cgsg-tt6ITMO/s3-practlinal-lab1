#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

#define message_len 12
#define abc_len 30

extern char abc[];

struct vec {
  size_t n;
  size_t* v;
};

struct square_matrix {
  size_t n;
  size_t** arr;
};

void print(size_t s);
void print_vec(struct vec* v);
void print_matr(struct square_matrix* M);

struct vec vec2(size_t v[2]);
struct vec vec3(size_t v[3]);
struct vec vec4(size_t v[4]);

struct square_matrix matr2x2(size_t arr[2][2]);
struct square_matrix matr3x3(size_t arr[3][3]);
struct square_matrix matr4x4(size_t arr[4][4]);

struct vec matr_mul_vec(struct square_matrix M, struct vec V);

struct square_matrix minor(struct square_matrix *M, size_t x, size_t y);
/*
size_t det2x2(struct square_matrix *M);
size_t det3x3(struct square_matrix *M);
size_t det4x4(struct square_matrix *M);
*/
int64_t det(struct square_matrix* M);

double** invert(struct square_matrix *M);

