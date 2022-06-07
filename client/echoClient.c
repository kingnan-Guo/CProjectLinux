/**
 * @file echoClient.cpp
 * @author your name (you@domain.com)
 * @brief 客户端的 实现
 * @version 0.1
 * @date 2022-06-08
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <stdio.h>

// #include <sys/types.h>

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
// #include <ctype.h> //C类型定义的
// #include <arpa/inet.h>//网络相关的
#include <sys/socket.h>
#include <netinet/in.h>

#define SERVER_PORT 8097

// argc 执行命令时参数的的个数 
// *argv[] 执行命令时 所有的如参的 数组
int main(int argc, char const *argv[])
{
    // 准备 一个邮箱
    int sockFd;
    char * message;
    // 如果 执行命令的 参数 
    if (argc != 2)
    {
        fputs("usage ./eoch_client message \n ", stderr);
        exit(1);
    }

    message = argv[1];
    printf("message : %s\n", message);

    

    return 0;
}


