#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

struct matr {
  size_t n, m;
  double** arr;
};

void print(double a);
void print_arr(double* a, size_t n);
void print_matr(struct matr M);


