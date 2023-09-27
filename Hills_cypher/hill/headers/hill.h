#pragma once

#include "structs.h"

char get_letter(size_t s);
size_t get_number(char letter);

char* nums_to_string(struct vec* vectors, size_t vec_size, size_t num_of_vec);
struct vec* vectors(char* s, size_t vec_size, size_t num_of_vec);

char* cypher(struct square_matrix* m, char* s);
char* decypher(struct square_matrix* m, char* cyphr);
