
#include "person_class.h"
#include "person_reader.h"
#include "modify_person.h"
#include <sys/wait.h> // for wait
#include <signal.h>   // for mask
#include <unistd.h>   // for pid
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
// #include <stdbool.h> //bool 
#include <stdlib.h> // rand(), srand()
#include <time.h>   // time()

#define HARCRA_FEL SIGCHLD

#define FIRST_BUS SIGUSR1
#define SECOND_BUS SIGUSR2
#define MAX_SIZE_OF_PATIENTS 10
#define MINIMUM_SIZE_OF_PATIENTS 4

void handler(int signumber)
{
    switch (signumber)
    {
    case HARCRA_FEL:
        printf("\n FOR THE GLORY !!! \n");
        break;
    case FIRST_BUS:
        printf("\n SMS SENT !!! \n");
        break;
    default:
        printf("It was sent by something else \n");
    }
}
//vaccinating people
void vaccinate(struct patient arr[], int begin, int end);
//printingf out subarray
int print_array(struct patient arr[], int begin, int end, const char *message);
//checking whether buses already ran today
bool chek_if_already_ran_today( const char * date_file );
//update date file 
void update( const char * date_file );
int main()
{
    sigset_t mask;
    sigfillset(&mask);
    sigprocmask(SIG_SETMASK, &mask, NULL);
    signal(HARCRA_FEL, handler);
    signal(FIRST_BUS, handler);
    
    char input_file_name[] = "output.txt";
    char temporary_file_name[] = "tmp.txt";
    char swap_file_name[] = "t.txt";
    char result_file_name[] = "vaccinated.txt";
    char date[]= "date.txt";

    
   

    int pipe_front_end_child[2];
    int pipe_back_end_child[2];
    int pipe_front_end_parent[2];
    int pipe_back_end_parent[2];

    pipe(pipe_front_end_child);
    pipe(pipe_back_end_child);
    pipe(pipe_front_end_parent);
    pipe(pipe_back_end_parent);

    struct patient record_of_persons[MAX_SIZE_OF_PATIENTS];
    bool already_ran_today = chek_if_already_ran_today((char * )date);
    int size_of_patients = read_vaccinated_person_from_file(record_of_persons, input_file_name, MAX_SIZE_OF_PATIENTS);
    if (size_of_patients > MINIMUM_SIZE_OF_PATIENTS && !already_ran_today)
    {

        pid_t parent;
        parent = fork();
        if (parent)
        {

            // parent doesnt read bus one infos
            close(pipe_front_end_child[0]);
            // parent doesnt read bus one infos
            close(pipe_back_end_child[0]);
            //parent gets the infos from bus one, so it doesn't write it
            close(pipe_front_end_parent[1]);
            //parent gets the infos from bus two, so it doesn't write it
            close(pipe_back_end_parent[1]);

            if (size_of_patients > MAX_SIZE_OF_PATIENTS - 2)
            {

                sigdelset(&mask, HARCRA_FEL);
                sigsuspend(&mask);
                printf("\n Operational side | we're awating the following patients :\n");
                print_array(record_of_persons, 0, MAX_SIZE_OF_PATIENTS / 2, " - FIRST BUS");
                print_array(record_of_persons, MAX_SIZE_OF_PATIENTS / 2, size_of_patients, "- SECOND BUS");
                kill(parent, FIRST_BUS);

                int size_of_back_end_pipeline = size_of_patients - (MAX_SIZE_OF_PATIENTS / 2);
                struct patient back_end_pipeline[size_of_back_end_pipeline];
                memcpy(&back_end_pipeline, record_of_persons + (MAX_SIZE_OF_PATIENTS / 2), size_of_back_end_pipeline * (sizeof(struct patient)));

                struct patient result_front[MAX_SIZE_OF_PATIENTS / 2];
                write(pipe_front_end_child[1], &record_of_persons, MAX_SIZE_OF_PATIENTS / 2 * sizeof(struct patient));
                // receiving the first bus's results
                close(pipe_front_end_child[1]);
                read(pipe_front_end_parent[0], &result_front, MAX_SIZE_OF_PATIENTS / 2 * (sizeof(struct patient)));
                close(pipe_front_end_parent[0]);

                //sending it for second bus

                write(pipe_back_end_child[1], &back_end_pipeline, size_of_back_end_pipeline * sizeof(struct patient));
                close(pipe_back_end_child[1]);
                //receiving the second bus's results
                struct patient result_back[size_of_back_end_pipeline];
                read(pipe_back_end_parent[0], &result_back, size_of_back_end_pipeline * (sizeof(struct patient)));
                close(pipe_back_end_parent[0]);
                printf(" \n Results \nFirst Bus");
                print_array(result_front, 0, MAX_SIZE_OF_PATIENTS / 2, NULL);
                printf(" \n Second BUs");
                print_array(result_back, 0, size_of_back_end_pipeline, NULL);
                owerrite_vaccinated_person_to_file(result_front, result_back, MAX_SIZE_OF_PATIENTS / 2, size_of_patients, input_file_name, temporary_file_name, swap_file_name, result_file_name);
                printf("\n \n %s has been updated  as %s \n", input_file_name, result_file_name);
                update(date);
            }
            else
            {
                sigdelset(&mask, HARCRA_FEL);
                sigsuspend(&mask);
                printf("\n Operational side | we're awating the following patients :\n");
                print_array(record_of_persons, 0, MAX_SIZE_OF_PATIENTS / 2, " - FIRST BUS");
                kill(parent, FIRST_BUS);
                close(pipe_back_end_parent[0]);
                write(pipe_front_end_child[1], &record_of_persons, MAX_SIZE_OF_PATIENTS / 2 * sizeof(struct patient));
                close(pipe_front_end_child[1]);
                struct patient result[MAX_SIZE_OF_PATIENTS / 2];
                read(pipe_front_end_parent[0], &result, MAX_SIZE_OF_PATIENTS / 2 * (sizeof(struct patient)));
                printf(" \n Result \n Bus");
                print_array(result, 0, MAX_SIZE_OF_PATIENTS / 2, NULL);
                close(pipe_front_end_parent[0]);
                owerrite_vaccinated_person_to_file(result, NULL, MAX_SIZE_OF_PATIENTS / 2, 0, input_file_name, temporary_file_name, swap_file_name, result_file_name);
                printf("\n \n %s has been updated %s updated also", input_file_name, result_file_name);
                update(date);
            }
        }
        else
        {
            //child receives the info here, so it doesn't write it - bus 1
            close(pipe_front_end_child[1]);
            //child sends the infos with it, so it doesn't read it
            close(pipe_front_end_parent[0]);
            //child receives the info here, so it doesn't write it - bus 1
            close(pipe_back_end_child[1]);
            //child sends the infos with it, so it doesn't read it
            close(pipe_back_end_parent[0]);
            kill(getppid(), HARCRA_FEL);
            sigdelset(&mask, FIRST_BUS);
            sigsuspend(&mask);
            if (size_of_patients > MAX_SIZE_OF_PATIENTS - 2)
            {

                pid_t bus;
                bus = fork();
                if (bus)
                {
                    int size = MAX_SIZE_OF_PATIENTS / 2;
                    struct patient persons_to_vaccinate[size];
                    read(pipe_front_end_child[0], &persons_to_vaccinate, size * (sizeof(struct patient)));
                    // sleep(1);
                    printf("\n THE FIRST BUS HAS GOT THEESE : \n");
                    print_array(persons_to_vaccinate, 0, size, NULL);
                    vaccinate(persons_to_vaccinate, 0, size);
                    write(pipe_front_end_parent[1], persons_to_vaccinate, size * sizeof(struct patient));
                }
                else
                {
                    int size = size_of_patients - (MAX_SIZE_OF_PATIENTS / 2);
                    struct patient persons_to_vaccinate[size];
                    read(pipe_back_end_child[0], &persons_to_vaccinate, size * (sizeof(struct patient)));
                    //  sleep(1);
                    printf("\n THE SECOND BUS HAS GOT THEESE : \n");
                    print_array(persons_to_vaccinate, 0, size, NULL);
                    vaccinate(persons_to_vaccinate, 0, size);
                    write(pipe_back_end_parent[1], &persons_to_vaccinate, size * sizeof(struct patient));
                }
            }
            else
            {
                printf("\n WE WILL USE ONLY THE FIRST BUS \n");
                struct patient persons_to_vaccinate[MAX_SIZE_OF_PATIENTS / 2];
                read(pipe_front_end_child[0], &persons_to_vaccinate, MAX_SIZE_OF_PATIENTS / 2 * (sizeof(struct patient)));
                printf("\n THE BUS HAS GOT THEESE : \n");
                print_array(persons_to_vaccinate, 0, MAX_SIZE_OF_PATIENTS / 2, NULL);
                vaccinate(persons_to_vaccinate, 0, MAX_SIZE_OF_PATIENTS / 2);
                write(pipe_front_end_parent[1], &persons_to_vaccinate, MAX_SIZE_OF_PATIENTS / 2 * sizeof(struct patient));
            }
        }
    }
    else if(size_of_patients <= MINIMUM_SIZE_OF_PATIENTS)
    {

        printf("\n There isn't enough applicant to start \n");
    }
    else 
    {
        printf("\n Buses already ran today \n");
    }

    return 0;
}
int print_array(struct patient arr[], int begin, int end, const char *message)
{

    for (int i = begin; i < end; i++)
    {
        if (message)
            printf("\n %s %s %i %ld %s %s %s", arr[i].firstName, arr[i].lastName, arr[i].birthYear, arr[i].telephoneNumber, arr[i].extraCharge, arr[i].status, message);
        else
            printf("\n %s %s %i %ld %s %s ", arr[i].firstName, arr[i].lastName, arr[i].birthYear, arr[i].telephoneNumber, arr[i].extraCharge, arr[i].status);
    }
    printf("\n");
    return 0;
}
void vaccinate(struct patient arr[], int begin, int end)
{
    srand(time(NULL));
    int randomNumber;
    for (int i = begin; i < end; i++)
    {
        randomNumber = rand() % 10 + 1;
        if (randomNumber < 9)
        {
            memcpy(arr[i].status, VACCINATED, sizeof(VACCINATED) / sizeof(VACCINATED[0]));
        }
        else
        {
            memcpy(arr[i].status, DID_NOT_APPEAR, sizeof(DID_NOT_APPEAR) / sizeof(DID_NOT_APPEAR[0]));
        }
    }
}
bool chek_if_already_ran_today( const char * date_file )
{

    struct tm *tm;
    time_t t;
    char str_time[100];
    char str_date[100];

    t = time(NULL);
    tm = localtime(&t);

    strftime(str_time, sizeof(str_time), "%H %M %S", tm);
    strftime(str_date, sizeof(str_date), "%d %m %Y", tm);
     FILE *file = fopen(date_file, "r");
   if( file )
   {
      char *line = NULL;
            size_t len = 0;
            ssize_t read;


            while ((read = getline(&line, &len, file)) != -1)
            {
                if(strcmp(str_date,line)==0)
                    return true;
            }

    fclose(file);
   }

   return false;
}
void update( const char * date_file )
{

    struct tm *tm;
    time_t t;
    char str_time[100];
    char str_date[100];

    t = time(NULL);
    tm = localtime(&t);

    strftime(str_time, sizeof(str_time), "%H %M %S", tm);
    strftime(str_date, sizeof(str_date), "%d %m %Y", tm);
     FILE *file = fopen(date_file, "w");
   if( file )
   {
     
     fprintf(file,"%s",str_date);

   }
   fclose(file);
 
}
