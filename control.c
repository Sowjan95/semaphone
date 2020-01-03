#include "semaphore.h"

int sem_id, shm_id, fd;
union semun s;
struct sembuf sb; //sem_num, sem_op, sem_flg


int create(){
    sem_id = semget(SEMKEY, 1, IPC_CREAT | IPC_EXCL | 0644); //create semaphore
    if (sem_id < 0){
        printf("error creating semaphore: %s\n", strerror(errno));
        return -1;
    }
    printf("Semaphore created!\n");
    semctl(sem_id, 0, SETVAL, s);

    shm_id = shmget(SHMKEY, sizeof(char *), IPC_CREAT | 0644); //create shared memory
    if (shm_id < 0){
        printf("error creating shared memory: %s\n", strerror(errno));
        return -1;
    }
    printf("Shared memory created!\n");

    fd = open("telephone.txt", O_CREAT | O_TRUNC | O_RDWR, 0644); //create telephone file
    if (fd < 0){
        printf("error creating telephone file: %s\n", strerror(errno));
        return -1;
    }
    printf("Telephone file created!\n");
    close(fd);

    return 0;
}

int view(){
    fd = open("telephone.txt", O_RDONLY);
    if (fd < 0){
        printf("error accessing telephone file: %s\n", strerror(errno));
        return -1;
    }
    printf("The story so far:\n");
    char buff[SIZE];
    while (read(fd, buff, SIZE))
        printf("%s\n", buff);
    close(fd);
    return 0;
}


int removes(){
    sem_id = semget(SEMKEY, 1, 0); //access semaphore
    if (sem_id < 0){
        printf("error accessing semaphore: %s\n", strerror(errno));
        return -1;
    }
    printf("trying to get in\n");
    semop(sem_id, &sb, 1);

    shm_id = shmget(SHMKEY, 1, 0); //access shared memory
    if (shm_id < 0){
        printf("error accessing shared memory: %s\n", strerror(errno));
        return -1;
    }

    view(); //display story

    shmctl(shm_id, IPC_RMID, 0);
    printf("successful removed shared memory\n");

    remove("telephone.txt");
    printf("successfully removed telephone file\n");

    semctl(sem_id, IPC_RMID, 0);
    printf("successfully removed semaphore\n");

    return 0;
}

int main(int agrc, char *argv[]){
    s.val = 1;
    sb.sem_num = 0;
    sb.sem_op = -1;
    if (strcmp(argv[1], "-c") == 0) create();
    else if (strcmp(argv[1], "-v") == 0) view();
    else if (strcmp(argv[1], "-r") == 0) removes();
    else printf("Flag not recognized. Valid flags: [-c | -r | -v]");
    return 0;
//Take a command line argument to determine if it is creating
//or removing the resources or viewing the story.
}
