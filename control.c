#include semaphore.h

int sem_id, shm_id, fd;
union semun s;


//char flag
//int v, r;
//char input[3];
//struct

//DONE???
int creates(){
    sem_id = semget(SEMKEY, 1, IPC_CREAT | IPC_EXCL | 0644); //create semaphore
    if (sem_id < 0){
        printf("error creating semaphore: %d: %s\n", errno, strerror(errno));
        return -1;
    }
    printf("Semaphore created!\n");
    semctl(sem_id, 0, SETVAL, su);

    shm_id = shmget(SHKEY, sizeof(char *), IPC_CREAT | 0644); //create shared memory
    if (shm_id < 0){
        printf("error creating shared memory: %d: %s\n", errno, strerror(errno));
        return -1;
    }
    printf("Shared memory created!\n");

    fd = open("telephone.txt", O_CREAT | O_TRUNC | O_RDWR, 0644); //create telephone file
    if (fd < 0){
        printf("error creating telephone file: %d: %s\n", errno, strerror(errno));
        return -1;
    }
    printf("Telephone file created!\n");
    close(fd);

    return 0;
}

//NOT DONE
int removes(){
    sem_id = semget(SEMKEY, 1, 0);
    printf("trying to get in\n");
    if (sem_id < 0){
        printf("error accessing semaphore: %d: %s\n", errno, strerror(errno));
        return -1;
    }
    semop(sem_id, )

}

//OBVIOUSLY NOT DONE
int views(){
    fd = open("telephone.txt", O_RDONLY);
    if (fd < 0){
        printf("error creating telephone file: %d: %s\n", errno, strerror(errno));
        return -1;
    }
    char buff[SIZE];
    int rd = read(fd, buff, SIZE);


}


int main(){
//Take a command line argument to determine if it is creating or removing the resources or viewing the story.


}
