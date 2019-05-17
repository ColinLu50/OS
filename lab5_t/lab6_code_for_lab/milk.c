/*dad_mem_mutex.c*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <time.h> 
#include <sys/stat.h>
#include <pthread.h>

int interested[2] = {0, 0};
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int res;

void *mom(){
    int fd;
    printf("Mom comes home.\n");
    sleep(rand()%2+1);
    //sinterested[0] = 1;
    //while(interested[1] == 1);
    sem_wait(&mutex); 
    printf("Mom checks the fridge.\n");
    fd=open("fridge", O_CREAT|O_RDWR|O_APPEND, 0777);
    
    if(lseek(fd,0,SEEK_END)==0){
        printf("Mom goes to buy milk...\n");
        sleep(rand()%2+1);
        printf("Mon comes back.\n");
        if(lseek(fd,0,SEEK_END)>0)
            printf("What a waste of food! The fridge can not hold so much milk!\n");
        else{
            write(fd,"milk",4);
            printf("Mom puts milk in fridge and leaves.\n");
        }
        
    }else{
        printf("Mom knows dad has gone to buy the milk, so she closes the fridge and commits suicide.\n");
        
    }
    close(fd);
    sem_post(&mutex); 
    //interested[0] = 0;
}

void *dad(){
    int fd;
    printf("Dad comes home.\n");
    sleep(rand()%2+1);
    sem_wait(&mutex); 
    //interested[1] = 1;
    //while(interested[0] == 1);
    //pthread_mutex_lock(&mutex);
    printf("Dad checks the fridge.\n");
    fd=open("fridge", O_CREAT|O_RDWR|O_APPEND, 0777);
    if(lseek(fd,0,SEEK_END)==0 && pthread_mutex_trylock(&mutex) == 0){
        printf("Dad goes to buy milk...\n");
        sleep(rand()%2+1);
        printf("Dad comes back.\n");
        if(lseek(fd,0,SEEK_END)>0)
            printf("What a waste of food! The fridge can not hold so much milk!\n");
        else{
            write(fd,"milk",4);
            printf("Dad puts milk in fridge and leaves.\n");
        }
        
    } else{
        printf("Dad knows mom has gone to buy the milk, so he closes the fridge and commits suicide.\n");
        
    }
    close(fd);
    sem_post(&mutex); 
    //interested[1] = 0;
}

int main(int argc, char * argv[]) {


    srand(time(0));
    pthread_t p1, p2;
    int fd = open("fridge", O_CREAT|O_RDWR|O_TRUNC , 0777);  //empty the fridge
    close(fd);
    // Create two threads (both run func)  
    pthread_create(&p1, NULL, mom, NULL); 
    pthread_create(&p2, NULL, dad, NULL); 
  
    // Wait for the threads to end. 
    pthread_join(p1, NULL); 
    pthread_join(p2, NULL); 
}
