#ifndef PERSON_CLASS_H
#define PERSON_CLASS_H
#define NAME_SIZE 20
#define YEAR_SIZE 4
#define TELEPHONE_SIZE 11
#define EXTRA_CHARGE_SIZE 4
#define MINIMAL_NAME_SIZE 4
#include <stdio.h>
#include "string.h"
#include <stdlib.h>
#include <ctype.h>

struct person
{
     char *firstName;
     char *lastName;
     int birthYear;
     long telephoneNumber;
     char *extraCharge;

     struct person *next;
};

void list_remove_all(struct person *n);
struct person *list_add(struct person **p, const char *firstName, const char *lastName,
                        const char *birthYear, const char *extraCharge, const char *telephoneNumber);
void list_remove(struct person **p);
struct person **list_search(struct person **n, const char *firstName, 
                              const char *lastName, int birthYear);
void list_print(struct person *n);
int get_list_size(struct person *n);
void modify_person( struct person * p ,char *firstName,  char *lastName,
                         char *birthYear, char *extraCharge,  char *telephoneNumber);
void insert_a_new_person(struct person *p);

#endif
