#include "../../csapp.h"

unsigned int snooze(unsigned int secs)
{
    unsigned int left_secs=sleep(secs);
    printf("Slept for %d of %d secs\n",secs-left_secs,secs);
    return left_secs;
}

void sigint_handler(int sig)
{
    return;
}

int main(int argc,char *argv[])
{

    if(signal(SIGINT,sigint_handler)==SIG_ERR)
    {
        printf("signal error\n");
    }
        // unix_error("signal error\n");
        // 不知道为什么这里的unix_error函数不可用
    
    snooze(atoi(argv[1]));

    exit(0);
}