#include "../include/interpreter.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <fnmatch.h>
#include <string.h>

//remember for to increment program counter in main loop

char string_form_of_opcodes[NUMBER_OF_OPCODES][5] = {"LDR", "STR", "ADD", "SUB", "MOV", "CMP", "B", "BEQ", "BNE", "BGT", "BLT", "AND", "ORR", "EOR", "MVN", "LSL", "LSR", "HALT", "OUT"};
char string_form_of_conditions[CONDITIONS_COUNT][2] = {"EQ", "NE", "GT", "LT"};

void invoke_error(const char* error_message) {
  fprintf(stderr, "ERROR: %s, LINE: %d\n", error_message, pc);
  exit(EXIT_FAILURE);
}

//textual find
enum opcodes match_opcode(char *opcode) {
  for (int i = 0; i < NUMBER_OF_OPCODES; i++) {
    if (!strcmp(string_form_of_opcodes[i], opcode)) {
      return (enum opcodes) (i + 1); //this works as the first enum is defined 0b1
    }
  }

  return -1;
}

long parse_number(char* number) { //parse number has a slides it forward by one
  char *remainder; 
  long returning_number = strtol(number + 1, &remainder, 10);

  if (strlen(remainder) > 0) invoke_error("INVALID ADDRESSING");
  return returning_number;
}

bool expression_is_numeric(char* expr) {
  for (int i = 0; i < strlen(expr); i++) {
    if (!isnumber(expr[i])) return false;
  }

  return true;
}

bool expression_is_alphabetic(char *expr) {
    for (int i = 0; i < strlen(expr); i++) {
      if (!isalpha(expr[i])) return false;
    }

    return true;
}

bool expression_is_space_or_null(char *expr) {

  if (expr == NULL) return true;
  
  for (int i = 0; i < strlen(expr); i++) {
    if (!isspace(expr[i])) return false;
  }

  return true;
}

char* remove_spaces(char *expr) {
  
  char* buffer = malloc(sizeof(char) * (strlen(expr) + 1));

  for (int i = 0, j = 0; i < strlen(expr); i++) {
    if (isspace(expr[i]) == 0) {
      buffer[j] = expr[i];
      j++;
    }
  }
  
  return buffer;
}

 void retrieve_labels_from_src(char* src_file_txt, struct Label_Table* table) {
  FILE *src_pointer = fopen(src_file_txt, "r");

    char* current_line = NULL;
    size_t line_number = 0;
    size_t current_line_buffer_length = 0;
    ssize_t current_line_length = 0;
    

  while ((current_line_length = getline(&current_line, &current_line_buffer_length, src_pointer)) != -1) {
    if (expression_is_space_or_null(current_line)) continue;
    
    if (current_line_length < 2) invoke_error("INVALID LENGTH");
    
    current_line[current_line_length - 1] = '\0';
    char* remove_spaces_from_label = remove_spaces(current_line);

    if (remove_spaces_from_label[strlen(remove_spaces_from_label) - 1] != ':') {
      line_number++;
      continue;
    }
    
    remove_spaces_from_label[strlen(remove_spaces_from_label) - 1] = '\0';
    insert_into_label_table((struct Label) {.label_name = remove_spaces_from_label, .location = line_number}, table);
    line_number++;
  }

  
  fclose(src_pointer);
 }

instruction_t parse_line(char* line, struct Label_Table *label_table) {

  instruction_t instruction_struct = {0};
  instruction_struct.operands_count = 0;
  short operand_count = 0;
  size_t pc_track = 0;

  if (expression_is_space_or_null(line)) {instruction_struct.opcode = EMP; return instruction_struct;}
  
  char* first_word = strtok(line, " ");
  
  char* first_word_with_no_spaces = remove_spaces(first_word);
  enum opcodes opcode_buffer = match_opcode(first_word_with_no_spaces);

  if (strlen(first_word_with_no_spaces) < 1) {   
    invoke_error("FAILED OPCODE PARSING");
  } else if (first_word[strlen(first_word_with_no_spaces) - 1] == ':') {
    //it is a label then...
    first_word_with_no_spaces[strlen(first_word_with_no_spaces) - 1] = '\0';
    opcode_buffer = EMP;    
  } else if (opcode_buffer == -1 && first_word_with_no_spaces[0] != 'B') {
      invoke_error("CANNOT FIND OPCODE");
  }

  instruction_struct.opcode = opcode_buffer;
  
  char* current_operand_with_spaces = strtok(NULL,",");

  //parse args
  while (current_operand_with_spaces != NULL) {
    char* current_operand = remove_spaces(current_operand_with_spaces);
    
    if (strlen(current_operand) < 1) invoke_error("FAILED PARSING OPERAND");

    if (contains_label(current_operand, label_table)) {
      instruction_struct.operands[operand_count].operand_mode = LABEL;
      instruction_struct.operands[operand_count].data.instruction_location = find_instruction_location(current_operand, label_table);
    } else if (current_operand[0] == 'R') { 

      long register_number = parse_number(current_operand);
      
      if (register_number < 0 || register_number > 12) invoke_error("INVALID REGISTER");

      instruction_struct.operands[operand_count].operand_mode = REGISTER_ADDRESS;
      instruction_struct.operands[operand_count].data.reg = (enum regs) register_number;
      
    } else if (current_operand[0] == '#') {

      long literal_number = parse_number(current_operand);

      if (literal_number < 0 || literal_number > SIZE_OF_MEMORY) invoke_error("INVALID MEMORY ADDRESS");
        
      instruction_struct.operands[operand_count].operand_mode = LITERAL;
      instruction_struct.operands[operand_count].data.literal =  literal_number;  
    } else if (expression_is_numeric(current_operand)) {
      //implement 
      long memory_location = atoi(current_operand);

      instruction_struct.operands[operand_count].operand_mode = MEMORY_ADDRESS;
      instruction_struct.operands[operand_count].data.memory_location = memory_location;
      
    } else {
      invoke_error("CANNOT PARSE OPERAND");
    }
    operand_count++;
    free(current_operand);
    current_operand_with_spaces = strtok(NULL,",");
  } 

  instruction_struct.operands_count = operand_count;

  if (instruction_struct.opcode != EMP) free(first_word_with_no_spaces);

  /*
  if (instruction_struct.opcode != EMP) {
    pc_track++;
  }
  */
  return instruction_struct;
  
}

//MOV R1, #3
//BEQ plus3
