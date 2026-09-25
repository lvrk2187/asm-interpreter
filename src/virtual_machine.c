#include "../include/virtual_machine.h"
#include <assert.h>

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

void execute(instruction_t instruction) {

  switch (instruction.opcode) {
    case LDR : break;
      
    case STR : break;
    case ADD : break;
    case SUB : break;
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
    case OUT : break;
  }

  
}
