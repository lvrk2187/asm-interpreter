#include "../include/interpreter.h"
#include <stdio.h>
#include <stdlib.h>
#include <fnmatch.h>
#include <string.h>

//remember for to increment program counter in main loop

char string_form_of_conditions[CONDITIONS_COUNT][2] = {"EQ", "NE", "GT", "LT"};

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
  
  if (first_word[0] == 'B' && strlen(first_word) > 1) {
    if (strlen(first_word) != 3)  invoke_error("INVALID CONDITION IN BRANCH");
    else {
        instruction_struct.opcode = B;

        /* each condition is /= 2 due to how the actual enum within the virtual machine is defined*/
        for (int i = 0, each_condition = 8; i < CONDITIONS_COUNT; i++, each_condition /= 2) {
          if (strncmp(first_word + 1, string_form_of_conditions[i], 2)) {
            instruction_struct.operands[0].data.condition = each_condition;
            instruction_struct.operands[0].operand_mode = CONDITION;
            instruction_struct.operands_count += 1;
            break;
          }
        }

    }
  } else {
    instruction_struct.opcode = opcode_buffer;
  }


  //parse args
  while (first_word != NULL) {
    //heavy part where you go through each of operands 
    char* current_operand = strtok(NULL,",");

    

    operand_count++;
  }
  
  
  return instruction_struct;
  
}
