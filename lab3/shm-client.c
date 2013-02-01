#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SHMSZ     27

main()
{
    int shmid;
    key_t key;
    int *shm, *s;

    /*
     * We'll name our shared memory segment
     * "5678".
     */
    key = 5678;

    /*
     * Create the segment.
     */
    if ((shmid = shmget(key, SHMSZ, IPC_CREAT | 0666)) < 0) {
        perror("shmget");
        exit(1);
    }

    /*
     * Now we attach the segment to our data space.
     */
    if ((shm = shmat(shmid, NULL, 0)) == (int *) -1) {
        perror("shmat");
        exit(1);
    }

    /*
     * Now put some things into the memory for the
     * other process to read.
     */
     *shm = 0;
    s = shm+1;

     int c;
    for (c = 10; c >= 1; c--)
        *s++ = rand() % 100;
    *s = -1;
    
    while (*shm != -1)
        sleep(1);
        
    /*
     * Now read what the server put in the memory.
     */
     printf("sorted output:\n");
    for (s = shm+1; *s != -1; s++)
        printf("%d ", *s);
    putchar('\n');

    exit(0);
}
