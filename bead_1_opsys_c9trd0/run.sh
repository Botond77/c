#!/bin/bash 
gcc -Wall vaccination.c person_reader.h person_reader.c person_class.h person_class.c modify_person.h modify_person.c -o program && ./program
