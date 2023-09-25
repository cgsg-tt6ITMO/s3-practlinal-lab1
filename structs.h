#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define message_len 12
#define abc_len 30
// 30 ασκβ
extern char abc[];// = "ΰαβγδεζηθικλμνξοπρςστυφχψϋόύώÿ";//" ΅Ά£¤¥¦§¨ª«¬­®―ΰαγδεζηθιλμνξο";
//extern size_t abc_len = 30L;// = sizeof(abc) / sizeof(abc[0]) - 1;

struct vec {
  size_t n;
  size_t* v;
};

struct square_matrix {
  size_t n;
  size_t** arr;
};

void print_vec(struct vec* v);
void print_matr(struct square_matrix* M);

struct vec vec2(size_t v[2]);
struct vec vec3(size_t v[3]);
struct vec vec4(size_t v[4]);

struct square_matrix matr2x2(size_t arr[2][2]);
struct square_matrix matr3x3(size_t arr[3][3]);
struct square_matrix matr4x4(size_t arr[4][4]);

struct vec matr_mul_vec(struct square_matrix M, struct vec V);
