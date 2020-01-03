#include "semaphore.h"

int sem_id, shm_id, fd;
struct sembuf sb;
/*

Will attempt to access the resources using the semaphore
Once in, it should display the last line added to the file (use shared memory to contain the size of the last line).
Prompt the use for the next line.
Once a new line is read, write that to the file, update the shared memory and then release the semaphore

*/

int main(){
    sem_id = semget(SEMKEY, 1, 0);
    sb.sem_num = 1;
    sb.sem_op = -1;
    printf("trying to get in\n");
    if (sem_id < 0){
        printf("error accessing semaphore: %s\n", strerror(errno));
        return -1;
    }
    //something goes here apparently
    //
    //
    shm_id = shmget(SHMKEY, 1, 0);
    if (shm_id < 0){
        printf("error accessing shared memory: %s\n", strerror(errno));
        return -1;
    }

    fd = open("telephone.txt", O_WRONLY, O_APPEND);
    if (fd < 0){
        printf("error accessing telephone file: %s\n", strerror(errno));
        return -1;
    }

    //read last line from shared memeory
    char *lastLine = shmat(shm_id, 0, 0);
    printf("last line: %s\n\n", lastLine);

    //prompt user for the next line
    //read that line and write it to the file
    char nextLine[SIZE];
    printf("Your next line:\n");
    fgets(nextLine, SIZE, stdin);
    write(fd, nextLine, strlen(nextLine));
    close(fd);

    strcpy(&lastLine, nextLine); //update shared memory
    shmdt(lastLine);
    sb.sem_op = 1;
    semop(sem_id, &sb, 1);
    return 0;

}
