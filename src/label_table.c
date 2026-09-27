#include "../include/label_table.h"
#include "../include/interpreter.h"

struct Label_Table* create_label_table() {
  struct Label_Table* table;
  table = malloc(sizeof(struct Label_Table));

  table->labels = malloc(sizeof(struct Label) * MAX_NUMBER_OF_LABELS);
  table->label_count = 0;

  return table;
}

void insert_into_label_table(char* label_name, size_t location, struct Label_Table *label_table) {
    if (label_table->label_count == MAX_NUMBER_OF_LABELS) invoke_error("TOO MANY LABELS");

    label_table->labels[label_table->label_count] = (struct Label) {.label_name = label_name, .location = location};  
    label_table->label_count++;
}

bool contains_label(char* label_name, struct Label_Table *label_table) {
  for (int i = 0; i < label_table->label_count; i++) {
    if (strcmp(label_name, label_table->labels[i].label_name)) return true; 
  }

  return false;
}

size_t find_instruction_location(char* label_name, struct Label_Table *label_table) {
  for (int i = 0; i < label_table->label_count; i++) {
    if (strcmp(label_name, label_table->labels[i].label_name)) return label_table->labels[i].location; 
  }

  return -1;
}

void destroy_table(struct Label_Table* label_table) {
  free(label_table->labels);
  free(label_table);
}

