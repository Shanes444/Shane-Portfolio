#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    char* argv[] = {"ls", NULL}; 
    pid_t cid;

    cid = fork();

    if (cid < 0)
    {
        printf("A fork error has occurred.\n");
        exit(-1);
    }
    else
        if (cid == 0)
        {
            printf("I am the child, about to call ps using execlp.\n");
            if(execvp("/bin/ls", argv) == -1){
                printf("The call to execlp() was not successful.\n");
            }
            exit(127);
        }
        else{
            if(wait(0) == -1){
                printf("A wait error has occurred\n");
            }
            else{
                printf("I am the parent. The child just ended. I will now exit.\n");
            }
            exit(0);
        }
    return(0);
}