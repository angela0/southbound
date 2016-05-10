/*************************************************************************
	> File Name: processdata.c
	> Author: Angela
	> Mail: zuchuang1@gmail.com
	> Created Time: Fri 06 May 2016 03:43:34 PM CST
 ************************************************************************/

#include "processdata.h"

using namespace rapidjson;

struct pathinfo *parsedata(struct pathinfo *path, const char *info)
{
    Document document;

    document.Parse(info);

    /*
    for (Value::ConstMemberIterator itr = document.MemberBegin(); itr != document.MemberEnd(); itr++)
    {

    }
     */

    path->pid = document["path_id"].GetUint();
    path->local_ip = document["local_ip"].GetUint();
    path->local_port = document["local_port"].GetUint();
    path->remote_ip = document["remote_ip"].GetUint();
    path->remote_port = document["remote_ip"].GetUint();
    path->direction = document["direction"].GetString()[0];

    return path;
}

char *makejson(char *s)
{
    return s;
}

