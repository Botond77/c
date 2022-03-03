#include "modify_person.h"

void flush_stdin()
{
    while ((getchar()) != '\n');
}
void read_stdin(char *to, const size_t array_size)
{
    char c;
    for (int i = 0; i < array_size; ++i)
    {
        c = getchar();
        if (i == array_size - 1 && (c != '\n' && c != EOF))
        {
            printf("Too long!\n");
            memset(to, 0, array_size);
            flush_stdin();
            break;
        }
        if (c == ' ' && i == 0)
        {
            printf("Can not start with space!\n");
            flush_stdin();
            break;
        }
        if (c == '\n' || c == EOF)
        {
            to[i] = '\0';
            break;
        }
        to[i] = c;
    }
}
void mod_insert_a_new_person(struct person **root)
{
    
    printf("\n ---------------Inserting a new patient , please type the patient in the following format ---------------\n \n'Firstname Lastname, Birthyear, Telephone, Extra Charge '\n\n ");
    printf("\n Example :'Bac Ilus, 1988, 36704567899, nem'\n\n  Candidate : ");
    char *line;

    size_t line_buff = 0;
    getline(&line, &line_buff, stdin);
    const char *firstName[20];
    char lastName[20];
    char com[2];
    char birthYear[5];
    const char *extraCharge[5];
    char telephoneNumber[13];
    //Spliting line
    int tag = sscanf(line, "%s %[^',']  %s %[^','] %s %[^',']%s%s", (char *)firstName, lastName,
                     com, birthYear, com, telephoneNumber, com, (char *)extraCharge);
    if (check_if_valid_person(tag, lastName, (char *)firstName, birthYear, telephoneNumber, (char *)extraCharge))
    {
        //Adding it into a list
        printf("\n ---------------Patient added to the list sucessfully  ---------------\n");
     
         list_add(root, (char *)firstName, lastName, birthYear, (char *)extraCharge, telephoneNumber);

    }
    else {
        system("clear");
        printf("\n \n \n Ooops ! Something happened, make sure you type the patient correctly!\n");

        mod_insert_a_new_person(root);
        }
    
}
void update_a_person(struct person **root, struct person **temp)
{
    system("clear");
    printf("\n ---------------Updating the patient, please type the patient in the following format---------------\n \n'Firstname Lastname, Birthyear, Telephone, Extra Charge '\n\n  Candidate : ");
    char *line;

    size_t line_buff = 0;
    getline(&line, &line_buff, stdin);
    const char *firstName[20];
    char lastName[20];
    char com[2];
    char birthYear[5];
    const char *extraCharge[5];
    char telephoneNumber[13];
    int tag = sscanf(line, "%s %[^',']  %s %[^','] %s %[^',']%s%s", (char *)firstName, lastName,
                     com, birthYear, com, telephoneNumber, com, (char *)extraCharge);
    if (check_if_valid_person(tag, lastName, (char *)firstName, birthYear, telephoneNumber, (char *)extraCharge))
    {
        //Adding it into a list
        modify_person(*temp,(char*)firstName,lastName,birthYear,(char*)extraCharge,telephoneNumber);
        printf("\n ---------------Person added to the list sucessfully  ---------------");
       
        //list_print(root);
       
    }
    else
    {
        printf("\n \n \n Ooops ! Something happened, make sure you type the patient correctly!\n");

        update_a_person(root,temp);
    }
    
}
void modify_a_person_helper(struct person **root, struct person **temp)
{
    system("clear");
    printf("\n Please select one : \n1. DELETE\n2. UPDATE\n  Choice: ");
    char menu_choice[2];
    size_t menu_choice_size = 2;
    read_stdin(menu_choice, menu_choice_size);
    if (atoi(menu_choice) == 1)
    {
        list_remove(list_search(root, (*temp)->firstName,(*temp)->lastName, (*temp)->birthYear));
        printf("\n\n Please PRESS ENTER to step back to the main menu \n");
        flush_stdin();
    }
    if (atoi(menu_choice) == 2)
    {
        update_a_person(root,temp);
        printf("\n\n Please PRESS ENTER to step back to the main menu \n");
        flush_stdin();
    }
}

void modify_a_person(struct person **root)
{
    system("clear");
    printf("\n\n Please enter some attributions of the patient you want to modify \n\n Correct syntax : 'First Name Last Name, Birth Year '\n");
    printf("\n Example :'Bac Ilus, 1988'\n\n  Candidate :");
    char *line;
    size_t line_buff = 0;
    getline(&line, &line_buff, stdin);
    const char *firstName[20];
    char lastName[20];
    char birthYear[5];
    char com[2];
    int tag = sscanf(line, "%s %[^',']%s %s", (char *)firstName, lastName, com, birthYear);
    //validation
    if (tag != 4 || !name_validate((char *)firstName) || !name_validate(lastName) || !birth_year_validate(birthYear))
    {
        printf("\n \n \n Ooops! Something happened, make sure you are typing the patient correctly!\n");
        printf("\n Example :'Bac Ilus, 1988'\n\n ");
        modify_a_person(root);
    }
    else
    {
   
        struct person **temp = list_search(root, (char*)firstName, lastName, atoi(birthYear));
        if (temp)
        {
            printf("\n       Found person with the following data : '%s %s %d %ld %s ' \n",
                   (*temp)->firstName, (*temp)->lastName,
                   (*temp)->birthYear, (*temp)->telephoneNumber, (*temp)->extraCharge);
            //checking whether delete or update is the option
            modify_a_person_helper(root, temp);
            
        }
        else
        {
           
            printf(" \n There is no patient with the given parameters! ");
             printf("\n\n Please PRESS ENTER to step back to the main menu \n");
              flush_stdin();
        }
    }
}
void get_list_of_current_persons( struct person *root)
{
    system("clear");
    list_print(root);
    printf("\nPlease PRESS ENTER to step back to the main menu \n");
    flush_stdin();
}
