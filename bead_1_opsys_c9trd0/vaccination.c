#include <stdio.h>
#include "person_class.h"
#include "person_reader.h"
#include <stdlib.h>
#include "modify_person.h"

void main_menu(char *menu_choice, size_t menu_choice_size)
{
 
   printf("\n Vacination !\n\nPlease select from the list below(1-5)\n\n1. Set a new patient \n2. Modifying a patient's data (DELETE / UPDATE ) \n3. Save current list \n4. Print current list \n5. Exit \n \n  Choice :");
   read_stdin(menu_choice, menu_choice_size);
}
//Driver code
int main()
{

   char input_file[] = "input.txt";
   char menu_choice[2];
   size_t menu_choice_size = 2;
   struct person *root = read_person_from_file(input_file);
   while (1)
   {
      main_menu(menu_choice, menu_choice_size);
      //New person
      if (atoi(menu_choice) == 1)
      {
         system("clear");
         mod_insert_a_new_person(&root);
         printf("\n Patient sucessfully inserted : \n\n" );
         printf("\n\n Please PRESS ENTER to step back to the main menu \n");
         flush_stdin();
        
      }
      //Modify person
      if (atoi(menu_choice) == 2)
      {
         //printf("\n MAIN %d ", root );
         modify_a_person(&root);
      }
      if (atoi(menu_choice) == 3)
      {
         system("clear");
         write_list_into_file("output.txt",root);
         
         printf("\n\n Please PRESS ENTER to step back to the main menu \n");
          flush_stdin();

      }
      //List
      if (atoi(menu_choice) == 4)
      {
         get_list_of_current_persons(root);
      }
      //exit
      if (atoi(menu_choice) == 5)
      {
         list_remove_all(root);
         break;
      }
      else
      {
         system("clear");
         printf("\n Please select only value listed below \n");
      }
   }

   return 0;
}
