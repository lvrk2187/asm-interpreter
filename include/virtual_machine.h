#pragma once

#include <stdio.h>
#include <stdlib.h>

#define MAX_NUMBER_OF_OPERANDS 3

enum regs {R0 = 0, R1, R2, R3, R4, R5, R6, R7, R8, R9, R10, R11, R12, R_CMP, R_FLAGS};
enum conditions {EQ = 8, NE = 4, GT = 2, LT = 1};
enum modes {LITERAL = 0, MEMORY_ADDRESS, REGISTER_ADDRESS, LABEL, CONDITION, EMPTY};
enum operand_index {OPERAND1, OPERAND2, OPERAND3};

/*
the concept is EQ is just 8, but for NE, it can either be GT OR LT

EQ = 0b1000
NE {
  GT = 0b0110
  LT = 0b0101
}
*/

enum opcodes {
  LDR = 0b0001, //2 operands
  STR, //2
  ADD, //3
  SUB, //3
  MOV, //2
  CMP, //2
  B, // 2 or 1 
  AND, //3
  ORR, //3
  EOR, //3
  MVN, //2
  LSL, //3
  LSR, //3
  HALT, //0
  OUT //1
};

typedef struct {
  enum modes operand_mode;

  union {
    size_t literal;
    size_t label;
    size_t memory_location;
    enum conditions condition;
    enum regs reg;    
  } data;

} operand;

typedef struct {

  enum opcodes opcode;
  short operands_count;
  operand operands[MAX_NUMBER_OF_OPERANDS];
  
} instruction_t;

extern instruction_t program[];
extern int memory[1 << 9];
extern int registers[1 << 4];

extern void execute(instruction_t instruction);

extern instruction_t declare_instructions(
  enum opcodes opcode, 
  size_t operands_count,
  operand op1, operand op2, operand op3);

extern void memory_out();
extern void output_registers();

