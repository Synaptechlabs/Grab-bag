#include <stdio.h>
#include <string.h>

struct studentT {
  char name[64];
  int age;
  float gpa;
  int grad_yr;
};

int checkID(struct studentT s1, int min_age);

int main() {

  int can_vote;
  struct studentT student;
  strcpy(student.name, "Ruth");
  student.age = 17;
  student.gpa = 3.5;
  student.grad_yr = 2021;

  if (can_vote) {
    printf("%s is %d years old and can vote. \n", student.name, student.age);
  } else {
    printf("%s is %d years old and cannot vote. \n", student.name, student.age);
  }
  return 0;
}
