#pragma once
#include "label_table.h"
#include "virtual_machine.h"

#include <strings.h>

#define CONDITIONS_COUNT 4

extern char string_form_of_opcodes[NUMBER_OF_OPCODES][4];
extern char string_form_of_conditions[CONDITIONS_COUNT][2];
extern void invoke_error(const char* error_message);

extern enum opcodes match_opcode(char *opcode);
extern instruction_t parse_line(char* line, struct Label_Table *label_table);
