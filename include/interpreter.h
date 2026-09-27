#pragma once
#include "virtual_machine.h"

#include <strings.h>

extern void invoke_error(const char* error_message);

extern enum opcodes match_opcode(char *opcode);
extern instruction_t parse_line(char* line);
