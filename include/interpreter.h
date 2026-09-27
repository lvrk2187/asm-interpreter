#pragma once
#include "virtual_machine.h"

struct Label_Table {
  char *label_name;
  size_t location;
};

extern enum opcodes match_opcode(char *opcode);
extern instruction_t parse_line(char* line);
