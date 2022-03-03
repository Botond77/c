#include "person_reader.h"
#include <stdbool.h>
#include <ctype.h>
#include <stdio.h>
#include "string.h"
#include <stdlib.h>
bool check_if_valid_person(int tag, const char *first_name,
                           const char *last_name, const char *birth_year,
                           const char *telephone_number, const char *extra_charge)
{
    return (tag == 8 &&
            name_validate((char *)last_name) &&
            name_validate((char *)first_name) &&
            telephone_number_validate(telephone_number) &&
            extra_charge_validate((char *)extra_charge) &&
            birth_year_validate(birth_year));
}
struct person *read_person_from_file(const char *filename)
{
    struct person *root = NULL;
    if (filename)
    {

        FILE *file = fopen(filename, "r");
        if (file)
        {
            char *line = NULL;
            size_t len = 0;
            ssize_t read;

            int line_pos = 1;

            while ((read = getline(&line, &len, file)) != -1)
            {

                const char *firstName[20];
                char lastName[20];
                char com[2];
                char birthYear[5];
                const char *extraCharge[5];
                char telephoneNumber[13];
                //Spliting line
                int tag = sscanf(line, "%s %[^',']  %s %[^','] %s %[^',']%s%s", (char *)firstName, lastName,
                                 com, birthYear, com, telephoneNumber, com, (char *)extraCharge);
                //Validating parameters such as that: telephone number, birthday format, etc.
                if (check_if_valid_person(tag, lastName, (char *)firstName, birthYear, telephoneNumber, (char *)extraCharge))
                {
                    //Adding it into a list
                    list_add(&root, (char *)firstName, lastName, birthYear, (char *)extraCharge, telephoneNumber);
                }
                else
                    printf("\nWARINGING : There was an input error reading file at line: [%d] %s ", line_pos, line);
            }

            free(line);
            printf("\n\n*****************************\n Data sucessfully saved\n*****************************\n\n");
        }
        else
            printf("File not found");
    }
    else
        printf("File not found");

    return root;
}
bool name_validate(const char *name)
{

    if (name)
    {
        char c = name[0];
        int i = 0;
        while (c != '\0')
        {
            c = name[i];

            if (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) && (i < NAME_SIZE - 1 && c != '\0'))
            {
                printf("\n Error : the last name/ first name can not contain digits or speaces -> '%s'", name);
                return false;
            }
            if (i >= NAME_SIZE)
            {
                printf("\n Error : the name is long  -> '%s'", name);
                return false;
            }
            i++;
        }
        size_t s = strlen(name);

        if (i + 1 < s || i < 3)
        {
            printf("\n Error : the name is to short ->'%s'", name);
            return false;
        }
    }
    else
        return false;

    return true;
}

bool birth_year_validate(const char *birth_year)
{
    if (birth_year)
    {
        int year = atoi(birth_year);
        if (year > 2020 || year < 1910)
            return false;
        int i = 0;
        while (i < YEAR_SIZE && i != '\0')
        {
            if (!isdigit(birth_year[i]))
            {
                printf("\n Error : the birth year can not contain characters . %s ", birth_year);
                return false;
            }
            i++;
        }
    }
    else
    {
        printf("\n Error : birth year does not exists. ");
        return false;
    }

    return true;
};
bool telephone_number_validate(const char *telephone_number)
{

    if (telephone_number)
    {
        long number = atoll(telephone_number);
        if (number < 36000000000 || number >= 40000000000)
            return false;
        for (int i = 0; i < TELEPHONE_SIZE; i++)
        {
            char c = telephone_number[i];
            if (c < '0' || c > '9')
            {
                printf("\n Error : the telephone number can not contain characters . %s ", telephone_number);
                return false;
            }
        }
    }
    else
    {
        printf("\n Error : the telephone number does not exists . ");
        return false;
    }
    return true;
}
bool extra_charge_validate(const char *extra_charge)
{
    if (extra_charge)
    {
        char buffer_1[] = "IGEN";
        char buffer_2[] = "NEM";

        int switch_buffer_1 = 0;
        int switch_buffer_2 = 0;
        bool equals_to_buffer_1 = true;
        bool equals_to_buffer_2 = true;

        int i = 0;
        while (i < EXTRA_CHARGE_SIZE && extra_charge[i] != '\0')
        {
            if (toupper(extra_charge[i]) != buffer_1[i] && switch_buffer_1 == 0)
            {
                equals_to_buffer_1 = false;
                switch_buffer_1++;
            }
            if (toupper(extra_charge[i]) != buffer_2[i] && switch_buffer_2 == 0)
            {
                equals_to_buffer_2 = false;
                switch_buffer_2++;
            }
            if (toupper(extra_charge[i]) != buffer_2[i] && toupper(extra_charge[i]) != buffer_1[i])
            {
                printf("\n Error : the extracharge '%s' does not match [%s] or [%s]", extra_charge, buffer_1, buffer_2);
                return false;
            }
            i++;
        }
        if (i < strlen(extra_charge))
        {
            printf("\n Error : the extracharge '%s' does not match [%s] or [%s]", extra_charge, buffer_1, buffer_2);
            return false;
        }
        return equals_to_buffer_1 || equals_to_buffer_2;
    }
    else
    {
        return false;
    }
}
void write_list_into_file(const char *filename, struct person *root)
{

    if (filename)
    {

        FILE *file = fopen(filename, "w");
        if (file)
        {

            if (!root)
                printf("write_list_into file  : list is empty\n");
            while (root)
            {
                fprintf(file, "%s %s, %i, %ld, %s \n", root->firstName, root->lastName,
                        root->birthYear, root->telephoneNumber, root->extraCharge);
                root = root->next;
            }
            fclose(file);
        }
        printf("\n Sucessfully saved \n");
    }
    else 
    {
        printf("\n Failed to save list");
    }
}
