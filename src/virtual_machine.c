#include "../include/virtual_machine.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int memory[1 << 9];
int registers[1 << 4];

int retrieve_value(instruction_t instruction, enum operand_index index) {

 operand current_operand = instruction.operands[index];
  
  switch (current_operand.operand_mode) {
    case LITERAL:
      return current_operand.data.literal;
    case MEMORY_ADDRESS:
      return memory[current_operand.data.memory_location];
    case REGISTER_ADDRESS:
      return registers[current_operand.data.reg];
    case LABEL:
      return current_operand.data.label;
    case CONDITION:
      return current_operand.data.condition;
    default:
      break;
  }

  assert(1); //switch should just catch everything, it should never span to this point in the code
  return 0;
} 

int retrieve_address(instruction_t instruction, enum operand_index index) {

  operand current_operand = instruction.operands[index];
  
  switch (current_operand.operand_mode) {
    case MEMORY_ADDRESS:
      return current_operand.data.memory_location;
    case REGISTER_ADDRESS:
      return current_operand.data.reg;
    default:
      break;
  }

  assert(1);
  return 0;
}

void execute(instruction_t instruction) {

  switch (instruction.opcode) {
    case LDR : 

      if (instruction.operands_count != 2) exit(EXIT_FAILURE);
      
      registers[retrieve_address(instruction, OPERAND1)] =
      retrieve_value(instruction, OPERAND2);
      
      break;
      
    case STR:

      if (instruction.operands_count != 2) exit(EXIT_FAILURE);
      
      memory[retrieve_address(instruction, OPERAND2)] = 
      retrieve_value(instruction, OPERAND1);
      
      break;
      
    case ADD: 

      if (instruction.operands_count != 3) exit(EXIT_FAILURE);
      
      registers[retrieve_address(instruction, OPERAND1)] = 
        retrieve_value(instruction, OPERAND2) + 
        retrieve_value(instruction, OPERAND3);

      break;
    
    case SUB :

      if (instruction.operands_count != 3) exit(EXIT_FAILURE);
      
      registers[retrieve_address(instruction, OPERAND1)] = 
        retrieve_value(instruction, OPERAND2) + 
        retrieve_value(instruction, OPERAND3);

     break;

    case MOV : break;
    case CMP : break;
    case B   : break;
    case AND : break;
    case ORR : break;
    case EOR : break;
    case MVN : break;
    case LSL : break;
    case LSR : break;
    case HALT: break;
    case OUT : 
      printf("%d", retrieve_value(instruction, OPERAND1));
      break;
  }

  
}

instruction_t declare_instructions(enum opcodes opcode, size_t operands_count, operand op1, operand op2, operand op3) {
  instruction_t buffer;
  buffer.opcode = opcode;
  buffer.operands_count = operands_count;

  buffer.operands[OPERAND1] = op1;
  buffer.operands[OPERAND2] = op2;
  buffer.operands[OPERAND3] = op3;

  return buffer;
}


void output_registers() {
  for (int i = 0; i < 16; i++) {
    printf("R%d: %d\n", i, registers[i]);
  }
}
