#include <errno.h>
#include <string.h>
#include "../include/virtual_machine.h"
#include "../include/interpreter.h"

int main() {

  /* 
  char* test = malloc(sizeof(char) * 256);
  test = strncpy(test, "ADD R1, R2, R0", 128);

  char *bruh = strtok(test, " ");

  while (bruh != NULL) {
    printf("%s\n", bruh);
    bruh = strtok(NULL, " ");
  }

  

  instruction_t k = declare_instructions
    (ADD, 
    3, 
    (operand){
      .operand_mode = REGISTER_ADDRESS,
      .data.reg = 2,
      },
    (operand){
      .operand_mode = LITERAL,
      .data.literal = 2
      },
    (operand){
      .operand_mode = LITERAL,
      .data.literal = 3
      }
  );

  instruction_t l = declare_instructions
    (ADD, 
    3, 
    (operand){
      .operand_mode = REGISTER_ADDRESS,
      .data.reg = 2,
      },
    (operand){
      .operand_mode = REGISTER_ADDRESS,
      .data.literal = 2
      },
    (operand){
      .operand_mode = LITERAL,
      .data.literal = 3
      }
  );
  execute(k);
  execute(l);
  output_registers();
  */
  


  // printf("%lu", sizeof(instruction_t));
  char apple[] = "BOY:";
  struct Label_Table* table = create_label_table();
  

  instruction_t a = parse_line(apple, table);
  execute(a);

  output_registers();
  

  
  
}
