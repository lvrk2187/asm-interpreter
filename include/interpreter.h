#pragma once
#include "label_table.h"
#include "virtual_machine.h"

#include <stdio.h>
#include <strings.h>

#define CONDITIONS_COUNT 4

extern char* remove_spaces(char *expr);

extern char string_form_of_opcodes[NUMBER_OF_OPCODES][5];
extern char string_form_of_conditions[CONDITIONS_COUNT][2];
extern void invoke_error(const char* error_message);

extern void retrieve_labels_from_src(char* src_file, struct Label_Table* table);

extern enum opcodes match_opcode(char *opcode);
extern instruction_t parse_line(char* line, struct Label_Table *label_table);

