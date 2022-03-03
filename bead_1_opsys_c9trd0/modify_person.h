#ifndef MODIFY_PERSON_H
#define MODIFY_PERSON_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "person_reader.h"
#include "person_class.h"

void flush_stdin();
void read_stdin(char *to, const size_t array_size);
void  mod_insert_a_new_person(struct person **root);
void update_a_person(struct person **root, struct person **temp);
void modify_a_person_helper(struct person **root, struct person **temp);
void modify_a_person(struct person **root);
void get_list_of_current_persons( struct person *root);
#endif