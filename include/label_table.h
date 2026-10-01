#pragma once
#include "virtual_machine.h"

struct Label {
  char *label_name;
  size_t location;
};

struct Label_Table {
  short label_count;
  struct Label* labels;
};

extern struct Label_Table* create_label_table();
extern void insert_into_label_table(struct Label label, struct Label_Table *label_table);
extern bool contains_label(char *label_name, struct Label_Table *label_table);
extern size_t find_instruction_location(char* label_name, struct Label_Table *label_table);
extern void destroy_table(struct Label_Table* label_table);
extern void print_table(struct Label_Table label_table);

