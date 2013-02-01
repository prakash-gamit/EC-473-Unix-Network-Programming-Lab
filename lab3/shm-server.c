/*
 * shm-server - server program to demonstrate shared memory.
 */
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>

#define SHMSZ     27

main()
{
    int shmid;
    key_t key;
    int *shm, *s;

    /*
     * We need to get the segment named
     * "5678", created by the client.
     */
    key = 5678;

    /*
     * Locate the segment.
     */
    if ((shmid = shmget(key, SHMSZ, 0666)) < 0) {
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
     * Now read what the client put in the memory.
     */
    for (s = shm+1; *s != -1; s++)
        printf("%d ", *s);
    putchar('\n');
    
    printf("sorting\n");
    /*
     * sort 
    */
     int *t, *smallest, temp;
     for(t = shm + 1; *t != -1; t++){
          smallest = t;
          for(s = (t + 1); *s != -1; s++){
               if(*s < *smallest)
                    smallest = s;
          }
          temp = *t;
          *t = *smallest;
          *smallest = temp;
     }

    /*
     * Finally, change the first character of the 
     * segment to -1, indicating we have read 
     * the segment.
     */
    *shm = -1;

    exit(0);
}
