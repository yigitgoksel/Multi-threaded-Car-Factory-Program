#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>

int typeA_input,typeB_input,typeC_input,typeD_input,noOfDays;
int noOfChassis, noOfPainting, noOfTires, noOfSeats, noOfEngines, noOfCarTops;

void chassis(){
    printf("Chassis is done.");
}

void tires(){
    printf("Tires is done. ");
}

void seats(){
    printf("Seats is done.");
}
void engine(){
    printf("Engine is done.");
}
void top(){
    printf("Top cover is done.");
}
void painting(){
    printf("Painting is done.");
}
sem_t sem_chassis;
sem_t sem_noOf_chassis;



sem_t sem_tires;
sem_t sem_noOf_tires;


sem_t sem_seats;
sem_t sem_noOf_seats;


sem_t sem_engine;
sem_t sem_noOf_engine;


sem_t sem_top;
sem_t sem_noOf_top;


sem_t sem_noOf_painting;




void * typeA_work(){
    sem_wait(&sem_noOf_tires);
    sem_wait(&sem_chassis);
    tires();
    sem_post(&sem_tires);
    sem_post(&sem_chassis);

    sem_wait(&sem_noOf_painting);
    sem_wait(&sem_top);
    painting();
}

void * typeB_work(){
    sem_wait(&sem_noOf_chassis);
    chassis();
    sem_post(&sem_chassis);

}

void * typeC_work(){
    sem_wait(&sem_noOf_seats);
    sem_wait(&sem_chassis);
    seats();
    sem_post(&sem_seats);
    sem_post(&sem_chassis);
}

void * typeD_work(){
    sem_wait(&sem_noOf_engine);
    sem_wait(&sem_chassis);
    engine();
    sem_post(&sem_engine);
    sem_post(&sem_chassis);

    sem_wait(&sem_noOf_top);
    sem_wait(&sem_tires);
    sem_wait(&sem_seats);
    sem_wait(&sem_engine);
    top();
    sem_post(&sem_top);


}

int main(void)
{





    char data[2][100];
    FILE *file;
    file = fopen("input.txt", "r");

    if (file == NULL)
    {
        printf("Error opening file.\n");
        return 1;
    }
    int line = 0;

    while (!feof(file) && !ferror(file))
        if (fgets(data[line], 100, file) != NULL)
            line++;

    fclose(file);

/*
    char *p = strtok (data[0], " ");

        typeA_input = p;
        p = strtok (NULL, " ");
        typeB_input= p;
        p = strtok (NULL, " ");
        typeC_input= p;
        p = strtok (NULL, " ");
        typeD_input= p;

            printf(typeB_input);

  */

    sscanf(data[0], "%d %d %d %d %d", &typeA_input, &typeB_input, &typeC_input, &typeD_input, &noOfDays);
    sscanf(data[1], "%d %d %d %d %d %d", &noOfChassis, &noOfPainting, &noOfTires, &noOfSeats, &noOfEngines, &noOfCarTops);

    pthread_t threadA[typeA_input];
    pthread_t threadB[typeB_input];
    pthread_t threadC[typeC_input];
    pthread_t threadD[typeD_input];
    int i,status;

    sem_init(&sem_chassis, 0, 0);
    sem_init(&sem_noOf_chassis, 0, 0);
    sem_init(&sem_tires, 0, 0);
    sem_init(&sem_noOf_tires, 0, noOfTires);
    sem_init(&sem_seats, 0, 0);
    sem_init(&sem_noOf_seats, 0, noOfSeats);
    sem_init(&sem_engine, 0, 0);
    sem_init(&sem_noOf_chassis, 0, noOfEngines);
    sem_init(&sem_top, 0, 0);
    sem_init(&sem_noOf_top, 0, noOfCarTops);
    sem_init(&sem_noOf_painting, 0, noOfPainting);


    for(i=0;i<typeA_input;i++){
        status=pthread_create(&threadA[i],NULL,typeA_work,NULL);
        if (status != 0)
        {
            fprintf(stderr, "Failed to create thread %d: %s\n", i , strerror(status));
            return 0;
        }
    }
    for(i=0;i<typeB_input;i++){
        status=pthread_create(&threadB[i],NULL,typeB_work,NULL);
        if (status != 0)
        {
            fprintf(stderr, "Failed to create thread %d: %s\n", i , strerror(status));
            return 0;
        }
    }

    for(i=0;i<typeC_input;i++){
        status=pthread_create(&threadC[i],NULL,typeC_work,NULL);
        if (status != 0)
        {
            fprintf(stderr, "Failed to create thread %d: %s\n", i , strerror(status));
            return 0;
        }
    }
    for(i=0;i<typeD_input;i++){
        status=pthread_create(&threadD[i],NULL,typeD_work,NULL);
        if (status != 0)
        {
            fprintf(stderr, "Failed to create thread %d: %s\n", i , strerror(status));
            return 0;
        }
    }




    return 0;
}