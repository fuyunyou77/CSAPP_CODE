#include </home/fu/csapp_code/book_code/csapp.h>

void unix_error(char *msg)
{
    fprintf(stderr,"%s: %s\n",msg,strerror(errno));
    exit(1);
}

int main(int argc,char* argv[])
{
    struct  in_addr ip_addr;
    uint32_t addr;
    char buf[MAXBUF];

    sscanf(argv[1],"%x",&addr);
    ip_addr.s_addr=htonl(addr);

    if (!inet_ntop(AF_INET,&ip_addr,buf,INET_ADDRSTRLEN))
    {
        unix_error("inet_ntop");
    }

    printf("%s\n",buf);

    return 0;
}