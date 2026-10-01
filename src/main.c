#include <errno.h>
#include <string.h>
#include "../include/virtual_machine.h"
#include "../include/interpreter.h"

int main() {

  /* 



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
  struct Label_Table* table = create_label_table();
  char instructions[6][64] = {"MOV R0, #5", "AND R1, R0, #1", "HALT"};
  
  for (int i = 0; i < 3; i++) {
    program[i] = parse_line(instructions[i], table);
  }

  run_program();
  
  output_registers();
  

  destroy_table(table);
  
}
