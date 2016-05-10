/*************************************************************************
	> File Name: interface.c
	> Author: Angela
	> Mail: zuchuang1@gmail.com
	> Created Time: Fri 06 May 2016 03:41:00 PM CST
 ************************************************************************/

#include <unistd.h>
#include "interface.h"

#define BUFSIZE 1024


struct ev_loop *loop;

struct bufs {
    uint32_t jsonlen;
    uint32_t getlen;
    uint8_t *buf;
    ev_io *watcher;
};

struct bufs *fdbuf[1024];

int init_interface()
{
    FILE *fp = fopen("controlers.ini", "r");
    if (fp == NULL)
    {
        perror("fopen error");
        return 1;
    }

    int sockfd;

    char ippport[BUFSIZE];

    struct sockaddr_in serveraddr;
    socklen_t len = sizeof(serveraddr);

    loop = EV_DEFAULT;

    while (fgets(ippport, BUFSIZE, fp))
    {
        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        if (sockfd < 0)
        {
            perror("socket error:");
            return 1;
        }

        bzero(&serveraddr, len);
        read_ip_and_port(ippport, &serveraddr);
        serveraddr.sin_family = AF_INET;

        if (connect(sockfd, (SA *)&serveraddr, len) < 0)
        {
            printf("%s", ippport);
            perror("connect error:");
            continue;
        }

        fdbuf[sockfd]->buf = (uint8_t *)malloc(BUFSIZE);
        if (fdbuf[sockfd] == NULL)
        {
            printf("malloc failed\n");
            continue;
        }
        fdbuf[sockfd]->getlen = 0;
        fdbuf[sockfd]->jsonlen = 0;
        bzero(fdbuf[sockfd]->buf, BUFSIZE);

        fdbuf[sockfd]->watcher = (ev_io *)malloc(sizeof(ev_io));

        if (fdbuf[sockfd]->watcher == NULL)
        {
            printf("can't alloc for watcher\n");
            continue;
        }

        ev_io_init(fdbuf[sockfd]->watcher, read_cb, sockfd, EV_READ);
        ev_io_start(loop, fdbuf[sockfd]->watcher);
    }
    return 0;
}


void start()
{
    ev_run(loop, 0);
}

void accept_cb(struct ev_loop *loop, struct ev_io *watcher, int revents)
{
    struct sockaddr_in clientaddr;
    socklen_t len;
    int clientfd;

    clientfd = accept(watcher->fd, (SA *)&clientaddr, &len);
    if (clientfd < 0)
    {
        perror("accept error:");
        return;
    }

    ev_io *client_read_watch = (ev_io *)malloc(sizeof(ev_io));

    ev_io_init(client_read_watch, read_cb, clientfd, EV_READ);
    ev_io_start(loop, client_read_watch);

    fdbuf[clientfd] = (struct bufs*)malloc(sizeof(struct bufs));
    if (fdbuf[clientfd] == NULL)
    {
        perror("malloc error:");
        return;
    }
    fdbuf[clientfd]->buf = (uint8_t *)malloc(BUFSIZE);
    fdbuf[clientfd]->getlen = 0;
    fdbuf[clientfd]->jsonlen = 0;

}

void read_cb(struct ev_loop *loop, struct ev_io *watcher, int revents)
{
    if (EV_ERROR & revents)
    {
        printf("error event in error");
        return;
    }
    int fd = watcher->fd;
    uint8_t *buf = fdbuf[fd]->buf;

    uint8_t tmpbuf[BUFSIZE];

    ssize_t getn;
    if (getn < 0)
    {
        perror("recv error:");
        return;
    }
    else if (getn == 0)
    {
        ev_io_stop(loop, watcher);
        free(fdbuf[watcher->fd]->buf);
        close(watcher->fd);
        free(fdbuf[watcher->fd]->watcher);
        free(fdbuf[watcher->fd]);
        fdbuf[watcher->fd] = NULL;

        return;
    }
    else
    {
        if (fdbuf[fd]->jsonlen == 0)
        {
            getn  = recv(watcher->fd, tmpbuf, 8, 0);
            fdbuf[fd]->jsonlen = *(uint32_t *)(tmpbuf+4);
            buf = (uint8_t *)realloc(buf, fdbuf[watcher->fd]->jsonlen);
        }
        else
        {
            int needn;
            if ((needn = fdbuf[fd]->jsonlen - fdbuf[fd]->getlen) < BUFSIZE)
                getn = recv(watcher->fd, tmpbuf, needn, 0);
            else
                getn = recv(watcher->fd, tmpbuf, BUFSIZE, 0);

            bcopy(tmpbuf, fdbuf[fd]->buf+fdbuf[fd]->getlen, getn);
        }

        if (fdbuf[fd]->jsonlen == fdbuf[fd]->getlen)
        {
            //process full json data
            printf("recive over\n");

            //clear buf
            fdbuf[fd]->jsonlen = 0;
            fdbuf[fd]->getlen = 0;
        }
    }

}

/*
 * name: read_ip_and_port
 * function: fill "a.b.c.d:port" into sockaddr_in
 * return-value: 1 for failed, and 0 for sucess
 */
 
int read_ip_and_port(char *ippport, struct sockaddr_in* serveraddr)
{
    char *p = strchr(ippport, ':');
    if (p == NULL)
    {
        printf("strchr error!\n");
        return 1;
    }

    *p = '\0';
    if (inet_pton(AF_INET, ippport, &(serveraddr->sin_addr)) <= 0) 
    {
        perror("inet_pton error:");
        return 1;
    }

    *p = ':';
    serveraddr->sin_port = htons(atoi(p+1));

    return 0;
}
