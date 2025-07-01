#include <stdio.h>

int main(int argc, char *argv[], char *envp[])
{

    printf("arg:\n");
    for(int i=0;i<=argc&&argv[i]!=NULL;i++)
    {
        printf("arg[%d]:%s\n",i,argv[i]);
    }

    printf("env:\n");
    int j=0;
    while(envp[j]!=NULL)
    {
        printf("envp[%d]:%s\n",j,envp[j]);
        j++;
    }
        
    return 0;
}