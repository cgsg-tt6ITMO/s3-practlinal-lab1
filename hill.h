#pragma once

#include "structs.h"

char get_letter(size_t s);
size_t get_number(char letter);

char* cypher(struct square_matrix m, char* s);
char* decypher(struct square_matrix* m, char* cyphr);
