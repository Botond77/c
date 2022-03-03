#ifndef PERSON_READER_H
#define PERSON_READER_H
#include "person_class.h"
#include "stdio.h"
#include <stdbool.h>
struct patient
{
     char firstName[21];
     char lastName[21];
     int birthYear;
     long telephoneNumber;
     char extraCharge[5];
     char status[30];
};
//validate a person with the given parameters- BEAD1
bool check_if_valid_person(int tag, const char *first_name,
                           const char *last_name, const char *birth_year,
                           const char *telephone_number, const char *extra_charge);
struct person *read_person_from_file(const char *filename);
// reading persons in, we do not validate here - BEAD2
int read_vaccinated_person_from_file(struct patient  record_of_persons[],const char *filename, int max_size);
// updating vaccinated persons and input persons - BEAD2
int owerrite_vaccinated_person_to_file(struct patient result_front[], struct patient result_end[], int size_front, 
int size_end, const char *input_file_name, char * temporary_fille_name , char * swap_file_name , char * result_file_name);

//finding wheter a patient already exixst in theese arrays - BEAD1
bool find_in_patient_arr(struct patient result_front[],struct patient result_end[], int size_front , int size_end, const char * first_name, const char * last_name , int birth_year);
//- BEAD1
bool name_validate(const char *name);
//- BEAD1
bool birth_year_validate(const char *birth_year);
//- BEAD1
bool telephone_number_validate(const char *telephone_number);
//- BEAD1
bool extra_charge_validate(const char *extra_charge);
//- BEAD1
void get_person_list(struct person *root);
//- BEAD1
void write_list_into_file(const char *filename, struct person *root);
#endif
