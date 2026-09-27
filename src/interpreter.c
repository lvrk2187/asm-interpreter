#include "../include/interpreter.h"
#include <stdio.h>
#include <stdlib.h>
#include <fnmatch.h>
#include <string.h>

void invoke_error(const char* error_message) {
  fprintf(stderr, "ERROR: %s, LINE: %d", error_message, pc);
  exit(EXIT_FAILURE);
}

//textual find
enum opcodes match_opcode(char *opcode) {

  if      (strcmp("LDR", opcode)) return LDR;
  else if (strcmp("STR", opcode))  return STR;
  else if (strcmp("ADD", opcode))  return ADD;
  else if (strcmp("SUB", opcode))  return SUB;
  else if (strcmp("MOV", opcode))  return MOV;
  else if (strcmp("CMP", opcode))  return CMP;
  else if (fnmatch("B??", opcode, 0) == 0)  return B; //special case
  else if (strcmp("AND", opcode))  return AND;
  else if (strcmp("ORR", opcode))  return ORR;
  else if (strcmp("EOR", opcode))  return EOR;
  else if (strcmp("MVN", opcode))  return MVN;
  else if (strcmp("LSL", opcode))  return LSL;
  else if (strcmp("LSR", opcode))  return LSR;
  else if (strcmp("HALT", opcode)) return HALT;
  else if (strcmp("OUT", opcode))  return OUT;
  else return -1;
}

instruction_t parse_line(char* line) {

  instruction_t instruction_struct;
  short operand_count = 0;
  
  char* opcode = strtok(line, " ");
  enum opcodes opcode_buffer = match_opcode(opcode);

  if (strlen(opcode) < 1 || opcode_buffer == -1 && opcode[strlen(opcode) - 1] != ':') {   
    invoke_error("FAILED OPCODE PARSING");
  } else if (opcode[strlen(opcode) - 1] == ':') {
    
  }

  if (opcode[0] == 'B') {
    if (strlen(opcode) != 3)  invoke_error("INVALID CONDITION IN BRANCH");
  }
  //deal with the BEQ, BNE...


  instruction_struct.opcode = opcode_buffer;

  //parse args
  while (opcode != NULL) {
    char* current_operand = strtok(NULL,",");
    
  }

  
  

  return instruction_struct;
  
}
