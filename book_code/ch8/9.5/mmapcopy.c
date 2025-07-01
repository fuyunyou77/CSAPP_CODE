#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

//练习题9.5
int main(int argc,char* argv[])
{
    struct stat stat;
    char* buf;

    if(argc!=2)
    {
        printf("Usage: %s <input_filename>\n",argv[0]);
        return 0;
    }

    int fd=open(argv[1],O_RDONLY);
    fstat(fd,&stat);    
    
    buf=mmap(NULL,stat.st_size,PROT_READ,MAP_SHARED,fd,0);

    write(1,buf,stat.st_size);
    return 0;
}