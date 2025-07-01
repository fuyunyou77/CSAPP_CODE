#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    __pid_t pid;
    int x =1;

    pid = fork();

    if(pid==0)
    {
        printf("child : %d\n",--x);
        // exit(0);
    }

    printf("parent : %d\n",++x);
    exit(0);

}

/*
output with comment exit():
parent : 2
child : 0
parent : 1

output with uncomment exit():
parent : 2
child : 0
*/