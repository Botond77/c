#ifndef PERSON_READER_H
#define PERSON_READER_H
#include "person_class.h"
#include "stdio.h"
#include <stdbool.h>


bool check_if_valid_person(int tag, const char * first_name,
                            const char * last_name , const char * birth_year,
                             const char * telephone_number , const char* extra_charge);
struct person * read_person_from_file(const char *filename);
bool name_validate(const char * name);
bool birth_year_validate(const char * birth_year);
bool telephone_number_validate(const char * telephone_number);
bool extra_charge_validate(const char* extra_charge  );
void get_person_list(struct person* root);
void write_list_into_file(const char * filename, struct person * root);
#endif

