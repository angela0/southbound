/*************************************************************************
	> File Name: main.c
	> Author: Angela
	> Mail: zuchuang1@gmail.com
	> Created Time: Fri 06 May 2016 03:40:01 PM CST
 ************************************************************************/

#include <stdio.h>
#include <string.h>
#include "processdata.h"
#include "interface.h"

int main(int argc, char *argv[])
{
    /*
    char s[1000];
    FILE *fp = fopen("/home/angela/Workspace/southbound/test.json", "r");
    if (fp == NULL)
    {
        perror("fopen error");
        exit(1);
    }
    fread(s, 1, 999, fp);
    printf("%s\n", s);
    //strcpy(s, "{\"direction\": \"a\", \"remote\": 0, \"local_port\": 1234, \"remote_port\": 4321, \"local_ip\": 0, \"path_id\": 1}");
    struct pathinfo path;

    parsedata(&path, s);


    printf("%u %u %u %u %u %c\n", path.pid, path.local_ip, path.local_port, path.remote_ip,path.remote_port, path.direction);
     */

    init_interface();

    return 0;
}
