#include "../include/virtual_machine.h"
#include "../include/interpreter.h"
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

instruction_t program[1 << 10];
bool executing = true;

int memory[SIZE_OF_MEMORY];
int registers[1 << 4];
int pc = 0;

void validate_operands(instruction_t instruction, short expected_operand_count) {
  if (instruction.operands_count != expected_operand_count) invoke_error("INVALID OPERANDS");
}

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
      return current_operand.data.instruction_location;
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

  exit(EXIT_FAILURE);
  return 0;
}

void execute(instruction_t instruction) {

  switch (instruction.opcode) {
    case LDR : 

      validate_operands(instruction, 0x2);
      
      registers[retrieve_address(instruction, OPERAND1)] =
        retrieve_value(instruction, OPERAND2);
      
      break;
      
    case STR:

      validate_operands(instruction, 0x2);
      
      memory[retrieve_address(instruction, OPERAND2)] = 
        retrieve_value(instruction, OPERAND1);
      
      break;
    
    case ADD: 

      validate_operands(instruction, 0x3);
      
      registers[retrieve_address(instruction, OPERAND1)] = 
        retrieve_value(instruction, OPERAND2) + 
        retrieve_value(instruction, OPERAND3);

      break;
    
    case SUB :

      if (instruction.operands_count != 0x3) exit(EXIT_FAILURE);
      
      registers[retrieve_address(instruction, OPERAND1)] = 
        retrieve_value(instruction, OPERAND2) - 
        retrieve_value(instruction, OPERAND3);

     break;

    case MOV: 

      validate_operands(instruction, 0x2);

      registers[retrieve_address(instruction, OPERAND1)] = 
        retrieve_value(instruction, OPERAND2);

      break;
      
    case CMP: 
    
      validate_operands(instruction, 0x2);

      registers[R_CMP] &= 0x0;

      if (retrieve_value(instruction, OPERAND1) == retrieve_value(instruction, OPERAND2)) {
        registers[R_CMP] |= EQ; 
      } else {
        registers[R_CMP] |= NE;
      
        if (retrieve_value(instruction, OPERAND1) > retrieve_value(instruction, OPERAND2)) registers[R_CMP] |= GT; 
        else if (retrieve_value(instruction, OPERAND1) < retrieve_value(instruction, OPERAND2)) registers[R_CMP] |= LT; 
      }
      
      break;

    case B:
      pc = retrieve_value(instruction, OPERAND1);
      break;
      
    case BEQ: 
      
      if ((registers[R_CMP] & EQ) == EQ) {
        pc = retrieve_value(instruction, OPERAND1);
      }
      
      break;
      
    case BNE:

      if ((registers[R_CMP] & NE) == NE) {
        pc = retrieve_value(instruction, OPERAND1);
      }

      break;
      
    case BGT:
      
      if ((registers[R_CMP] & GT) == GT) {
        pc = retrieve_value(instruction, OPERAND1);
      }

      break;

    case BLT:
      
      if ((registers[R_CMP] & LT) == LT) {
        pc = retrieve_value(instruction, OPERAND1);
      }

      break;
            
    case AND: 
      validate_operands(instruction, 0x3);

      registers[retrieve_address(instruction, OPERAND1)] = 
        retrieve_value(instruction, OPERAND2) & 
        retrieve_value(instruction, OPERAND3);
        
    break;
    
    case ORR: 
      validate_operands(instruction, 0x3);

      registers[retrieve_address(instruction, OPERAND1)] = 
        retrieve_value(instruction, OPERAND2) |
        retrieve_value(instruction, OPERAND3);
        
      break;
    
    case EOR: 
      validate_operands(instruction, 0x3);

      registers[retrieve_address(instruction, OPERAND1)] = 
        retrieve_value(instruction, OPERAND2) ^ 
        retrieve_value(instruction, OPERAND3);
        
      break;
      
    case MVN : break; //nah
    case LSL:
      validate_operands(instruction, 0x3);

      registers[retrieve_address(instruction, OPERAND1)] = 
        retrieve_value(instruction, OPERAND2) << 
        retrieve_value(instruction, OPERAND3);
        
      break;

    case LSR:
      validate_operands(instruction, 0x3);

      registers[retrieve_address(instruction, OPERAND1)] = 
        retrieve_value(instruction, OPERAND2) >>
        retrieve_value(instruction, OPERAND3);
        
      break;
      
    case HALT: 
    
        executing = false;
        
        break;
    case OUT : 
      printf("%d\n", retrieve_value(instruction, OPERAND1));
      break;
      
    case EMP:
      break;
  }  
}

void run_program() {
  while (executing) {
    execute(program[pc]);
    pc++;
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
  for (enum regs CURRENT_REG = R0; CURRENT_REG < 16; CURRENT_REG++) {
    
    if (CURRENT_REG <= 12) printf("R%d: %d\n", CURRENT_REG, registers[CURRENT_REG]);
    else if (CURRENT_REG == R_CMP) printf("R_CMP: %d\n", registers[CURRENT_REG]);
    else if (CURRENT_REG == R_FLAGS) printf("R_FLAGS: %d\n", registers[CURRENT_REG]);


  }
}

void output_memory() {
  
}
