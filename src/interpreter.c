#include "../include/interpreter.h"
#include <stdio.h>
#include <stdlib.h>
#include <fnmatch.h>
#include <string.h>

//remember for to increment program counter in main loop

char string_form_of_opcodes[NUMBER_OF_OPCODES][4] = { "LDR", "STR", "ADD", "SUB", "MOV", "CMP", "BEQ", "BNE", "BGT", "BLT", "AND", "ORR", "EOR", "MVN", "LSL", "LSR", "HALT", "OUT" };
char string_form_of_conditions[CONDITIONS_COUNT][2] = {"EQ", "NE", "GT", "LT"};

void invoke_error(const char* error_message) {
  fprintf(stderr, "ERROR: %s, LINE: %d", error_message, pc);
  exit(EXIT_FAILURE);
}

//textual find
enum opcodes match_opcode(char *opcode) {
  for (int i = 0; i < NUMBER_OF_OPCODES; i++) {
    if (strcmp(string_form_of_opcodes[i], opcode)) {
      return (enum opcodes) (i + 1); //this works as the first enum is defined 0b1
    }
  }

  return -1;
}

instruction_t parse_line(char* line, struct Label_Table *label_table) {

  instruction_t instruction_struct;
  short operand_count = 0;
  
  char* first_word = strtok(line, " ");
  enum opcodes opcode_buffer = match_opcode(first_word);

  if (strlen(first_word) < 1) {   
    invoke_error("FAILED OPCODE PARSING");
  } else if (first_word[strlen(first_word) - 1] == ':') {
    //it is a label then...
    first_word[strlen(first_word) - 1] = '\0';
    
    if (!contains_label(first_word, label_table)) {
      insert_into_label_table((struct Label) {.label_name = first_word, .location = pc}, label_table);
    }
    
  } else if (opcode_buffer == -1 && first_word[0] != 'B') {
      invoke_error("CANNOT FIND OPCODE");
  }

  instruction_struct.opcode = opcode_buffer;
  


  //parse args
  while (first_word != NULL) {
    
    /*
    heavy part where you go through each of operands, there should be a check for operand_count
    as for the instruction B <condition> the first operand has already
    */
    char* current_operand = strtok(NULL,",");

    

    operand_count++;
  }
  
  
  return instruction_struct;
  
}
