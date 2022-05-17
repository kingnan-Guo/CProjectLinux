/**
 * @file callBackService.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-05-15
 * 
 * @copyright Copyright (c) 2022
 * 
 */


#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>

#include <string.h>
#include <ctype.h> //C类型定义的
#include <arpa/inet.h>//网络相关的

#define SEVICE_PORT 8090

int main()
{
    // 准备信箱
    int sock;
    //  创建一个信箱
    // AF_INET   网络通信家族 TCIP 
    // SOCK_STREAM  使用 sock协议
    sock = socket(AF_INET, SOCK_STREAM, 0);
    printf("sock = %u", sock);

    return 0;
}

