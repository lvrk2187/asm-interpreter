#include <stdio.h>
#include <string.h>
#include "../include/virtual_machine.h"

int main() {

  char* test = malloc(sizeof(char) * 256);
  test = strncpy(test, "ADD R1, R2, R0", 128);

  char *bruh = strtok(test, " ");

  while (bruh != NULL) {
    printf("%s\n", bruh);
    bruh = strtok(NULL, " ");
  }


  // printf("%lu", sizeof(instruction_t));
  
}
