//实现一个简单的shell
// #include <stdio.h>
// #include <sys/types.h>
// #include <unistd.h>
// #include <stdlib.h>
// #include <string.h>
// #include <sys/wait.h>
// #include <errno.h>

#include "../../csapp.h"

#define MAXARGS 128

void eval(char *cmdline);
int parseline(char *buf, char **argv);
int buildin_cmd(char **argv);
void unix_error(char *msg);

int main()
{
    char cmdline[MAXLINE];

    while(1)
    {
        //Read args
        printf(">");

        if(fgets(cmdline,MAXLINE,stdin)==NULL)
            printf("get input error!");

        if(feof(stdin))
            exit(0);
        
        //Evaluate
        eval(cmdline);
    }
}
//eval - Evaluate a command line
void eval(char *cmdline)
{
    char *argv[MAXARGS];
    char buf[MAXLINE];
    int bg;
    pid_t pid;

    strcpy(buf,cmdline);
    bg=parseline(buf,argv);
    if(argv[0]== NULL)
        return;
    
    if(!buildin_cmd(argv))
    {
        if((pid=fork())==0)
        {
            if(execve(argv[0],argv,__environ)<0)
            {
                printf("%s:Command not found.\n",argv[0]);
                exit(0);
            }
        }

        if(!bg)
        {
            int status;
            if(waitpid(pid,&status,0)<0)
                unix_error("waitfg: waitpid error");
        }
        else
            printf("%d %s",pid,cmdline);
    }

    return;

}

int buildin_cmd(char **argv)
{
    printf("argv[0]=%s",argv[0]);
    if(!strcmp(argv[0],"quit")) 
        exit(0);
    if(!strcmp(argv[0],"&")) 
        return 1;
    return 0;
}

int parseline(char *buf, char **argv)
{
    char *delim;
    int argc;
    int bg;

    buf[strlen(buf)-1]=' ';
    while(*buf&&(*buf==' ')) buf++;

    argc=0;
    while ((delim=strchr(buf,' ')))
    {
        argv[argc++]=buf;
        *delim='\0';
        buf=delim+1;
        while(*buf && (*buf==' ')) buf++;
    }

    argv[argc]=NULL;
    
    if(argc==0) return 1;

    if((bg=(*argv[argc-1]=='&'))!=0)
    argv[--argc]=NULL;

    return bg;
}

void unix_error(char *msg) /* Unix-style error */
{
    fprintf(stderr, "%s: %s\n", msg, strerror(errno));
    exit(0);
}