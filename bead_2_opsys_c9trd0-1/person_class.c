#include "person_class.h"

struct person *list_add(struct person **p, const char *firstName, const char *lastName,
                        const char *birthYear, const char *extraCharge, const char *telephoneNumber)
{
    //Allocating memory 
     struct person *n = malloc(sizeof(struct person));
     n->next = *p;
     *p = n;

     n->firstName = (char *)malloc(sizeof(firstName));
     strcpy(n->firstName, (char *)firstName);

     n->lastName = (char *)malloc(sizeof(lastName));
     strcpy(n->lastName, (char *)lastName);
     int x = atoi(birthYear);
     n->birthYear = x;
     long x2 = atoll(telephoneNumber);
     n->telephoneNumber = x2;

     n->extraCharge = (char *)malloc(sizeof(extraCharge));
     strcpy(n->extraCharge, (char *)extraCharge);

     n->status=(char*)malloc(sizeof(WAIT_STATUS));
     strcpy(n->status, (char *)WAIT_STATUS);
     return n;
}
//It removes a specific person
void list_remove(struct person **p)
{
    
     if (p)
     {
          struct person *n = *p;
          *p = (*p)->next;
          free(n);
        
        printf("\n Person deleted sucessfully\n");
     }
   
}
void list_remove_all(struct person *p)
{
    
  
     while (p)
     {
          struct person *n = p;
          p = p->next;
          free(n);
         
     }
}
// Finding the person that matches criteria below
struct person **list_search(struct person **n, const char *firstName, 
                              const char *lastName, int birthYear)
{
     //printf("\n--- %s %s",firstName,lastName);
     if (!n)
          return NULL;
     while (*n)
     {
          if ((*n)->birthYear == birthYear 
          && strcmp((*n)->firstName,firstName)==0 && strcmp((*n)->lastName,lastName)==0)
          {
               return n;
          }
          n = &(*n)->next;
     }
     return NULL;
}

void list_print(struct person *n)
{
     if (!n)
          printf("list is empty\n");
     while (n!= NULL)
     {
          printf("\n %s %s %i %ld %s %s",n->firstName,n->lastName, n->birthYear
                    ,n->telephoneNumber,n->extraCharge,n->status);
          n = n->next;
         
     }
    printf("\n");
}
int get_list_size(struct person *n)
{
    if (!n)
          return 0;
    int list_size=0;
     while (n)
     {
          n = n->next;
          list_size++;
     }
     return list_size;
}
// It modifies a specific person to the new parameters below
void modify_person( struct person * p ,char *firstName,  char *lastName,
                         char *birthYear, char *extraCharge,  char *telephoneNumber)
{
    strcpy(p->firstName,firstName);
    strcpy(p->lastName, lastName);
    strcpy(p->extraCharge, extraCharge);
  
    p->birthYear=atoi(birthYear);
    p->telephoneNumber= atoll(telephoneNumber);

   // printf("************************\n\n Data succesfully changed to: \n\n %s %s %i %ld %s \n\n************************",
    //p->firstName, p->lastName,p->birthYear,p->telephoneNumber,p->extraCharge);
    //printf("\n");

}
