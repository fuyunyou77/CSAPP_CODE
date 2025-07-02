#include </home/fu/csapp_code/book_code/csapp.h>

void unix_error(char *msg)
{
    fprintf(stderr,"%s: %s\n",msg,strerror(errno));
    exit(1);
}

int main(int argc,char **argv)
{
    struct in_addr ip_addr;
    uint32_t addr;
    char buf[INET_ADDRSTRLEN];

    sscanf(argv[1],"%s",buf);

    if(!inet_pton(AF_INET,buf,&addr))
        unix_error("inet_pton");
    
    ip_addr.s_addr = ntohl(addr);

    printf("0x%x\n",ip_addr.s_addr);

    return 0;
}