#include "../include/virtual_machine.h"
#include "../include/interpreter.h"

int main(int argc, char** argv) {
  
  char file_name[] = "testing_files/fact.aasm";

  FILE* src_file = fopen(file_name, "r");

  struct Label_Table* table = create_label_table();

  
  size_t current_line_number = 0;

  char* current_line = NULL;
  size_t current_line_buffer_length = 0;
  ssize_t current_line_length = 0;

  retrieve_labels_from_src(file_name, table);


  while ((current_line_length = getline(&current_line, &current_line_buffer_length, src_file)) != -1) {
    current_line[current_line_length - 1] = '\0';
    program[current_line_number] = parse_line(current_line, table); 
    current_line_number++;

  }
  

  free(current_line);
  
  // printf("%lu", sizeof(instruction_t));
  run_program();
  
  //output_registers();
  

  destroy_table(table);
  
}
