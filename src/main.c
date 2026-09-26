#include <errno.h>
#include <stdio.h>
#include <string.h>
#include "../include/virtual_machine.h"

int main() {

  /* 
  char* test = malloc(sizeof(char) * 256);
  test = strncpy(test, "ADD R1, R2, R0", 128);

  char *bruh = strtok(test, " ");

  while (bruh != NULL) {
    printf("%s\n", bruh);
    bruh = strtok(NULL, " ");
  }

  */

  instruction_t f;
  f.opcode = ADD;
  f.operands_count = 3;

  operand op1;
  op1.operand_mode = REGISTER_ADDRESS;
  op1.data.reg = 0;
  f.operands[OPERAND1] = op1;

  operand op2;
  op2.operand_mode = LITERAL;
  op2.data.literal = 3;
  f.operands[OPERAND2] = op2;

  operand op3;
  op3.operand_mode = LITERAL;
  op3.data.literal = 4;
  f.operands[OPERAND3] = op3;


  instruction_t l = declare_instructions
    (ADD, 
    3, 
    (operand){
      .operand_mode = REGISTER_ADDRESS,
      .data.reg = 2,
      },
    (operand){
      .operand_mode = LITERAL,
      .data.literal = 2
      },
    (operand){
      .operand_mode = LITERAL,
      .data.literal = 3
      }
    );

  execute(l);
  output_registers();

  // printf("%lu", sizeof(instruction_t));
  
}
