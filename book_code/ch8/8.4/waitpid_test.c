#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    if (fork()==0)
    {
        printf("a\n");//fflush(stdout);
    }
    else
    {
        printf("b\n");//fflush(stdout);
        waitpid(-1,NULL,0);
    }
    printf("c\n");fflush(stdout);
    exit(0);

}