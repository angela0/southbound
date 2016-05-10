/*************************************************************************
	> File Name: processdata.h
	> Author: Angela
	> Mail: zuchuang1@gmail.com
	> Created Time: Fri 06 May 2016 03:44:01 PM CST
 ************************************************************************/

#ifndef _PROCESSDATA_H
#define _PROCESSDATA_H

#include <ctype.h>
#include <inttypes.h>

#include "rapidjson/document.h"

struct pathinfo
{
    uint32_t pid;
    uint32_t local_ip;
    uint16_t local_port;
    uint32_t remote_ip;
    uint16_t remote_port;
    uint8_t direction;
};


struct pathinfo *parsedata(struct pathinfo *path, const char *info);

#endif
