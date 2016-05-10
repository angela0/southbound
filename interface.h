/*************************************************************************
	> File Name: interface.h
	> Author: Angela
	> Mail: zuchuang1@gmail.com
	> Created Time: Fri 06 May 2016 03:41:33 PM CST
 ************************************************************************/

#ifndef _INTERFACE_H
#define _INTERFACE_H

#include <ev.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <stdio.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>

typedef struct sockaddr SA;

int init_interface();
void start(int);
void accept_cb(struct ev_loop *loop, struct ev_io *watcher, int revents);
void read_cb(struct ev_loop *loop, struct ev_io *watcher, int revents);

int read_ip_and_port(char *, struct sockaddr_in*);

#endif
