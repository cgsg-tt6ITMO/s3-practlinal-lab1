#include "headers/hill.h"

struct square_matrix matr_gen() {
  struct square_matrix
    m = matr2x2((size_t[2][2]) {
      {17, 3},
      { 2, 1 }});
  return m;
}

int main() {
  char* s1 = "������������",
    *s2 = "������������";
  struct square_matrix m = matr_gen();
  char* c1 = cypher(&m, s1),
    *c2 = cypher(&m, s2);

  // 1. ������� �� ������� ����������� � �������������
  // 2. ��������� � ����� ������� c1, s1
  // 3. ������� �� �� ������� ����� 2
  // 4. �� ����� ���������� ����� 4 ����� �������� �������
  // 5. ����������� ������ ��������� (����� ������ �������� �������)
}