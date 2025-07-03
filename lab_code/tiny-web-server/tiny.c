#include "csapp.h"

void doit(int fd);

int main(int argc,char **argv)
{

    int listen_fd,connfd;
    char hostname[MAXLINE],port[MAXLINE];
    socklen_t clientlen;
    struct sockaddr_storage clientaddr;
    

    if(argc!=2)
    {
        fprintf(stderr,"Usage: %s <port>\n",argv[0]);
        exit(1);
    }

    listen_fd=Open_listenfd(argv[1]);
    while (1)
    {
        clientlen=sizeof(clientaddr);
        //accept connection from client
        connfd=Accept(listen_fd,(SA *)&clientaddr,&clientlen);
        Getnameinfo((SA *)&clientaddr,clientlen,hostname,MAXLINE,port,MAXLINE,0);

        printf("Accept connection from %s:%s",hostname,port);

        doit(connfd);
        Close(connfd);

    }
    
}

void doit(int fd)
{
    int is_static;
    struct stat sbuf;
    char buf[MAXLINE],method[MAXLINE],uri[MAXLINE],version[MAXLINE];
    char filename[MAXLINE],cgiargs[MAXLINE];
    rio_t rio;

    /*read request line and headers*/
    Rio_readinitb(&rio,fd);
    Rio_readlineb(&rio,buf,MAXLINE);
    printf("Request headers:\n");
    printf("%s",buf);
    sscanf(buf,"%s %s %s",method,uri,version);
    if(strcasecmp(method,"GET"))
    {
        clienterror(fd,method,"501","Not implemented","Tiny does no implement this method");
        return;
    }

    read_requesthdrs(&rio);

    /*Parse URI from GET request*/
    is_static=parse_uri(uri,filename,cgiargs);

    if(stat(filename,&sbuf)<0)
    {
        clienterror(fd,filename,"404","Not found","Tiny couldn't find this file");
        return;
    }

    /*Serve static content*/
    if(is_static)
    {

    }
    else/*Serve dynamic content*/
    {

    }

}