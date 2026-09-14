#include "../include/virtual_machine.h"
#include <assert.h>


void execute(instruction_t instruction) {

  switch (instruction.opcode) {
    case LDR : 
      assert(instruction.operand1_mode != REGISTER_ADDRESS || instruction.operand2_mode != MEMORY_ADDRESS);
      instruction.operand1.reg = memory[instruction.operand2.memory_location];
      break;
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
