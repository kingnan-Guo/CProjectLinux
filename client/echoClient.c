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
#include <arpa/inet.h>//网络相关的
#include <sys/socket.h>
#include <netinet/in.h>

#define SERVER_PORT 8097
#define SERVER_IP "127.0.0.1"
// argc 执行命令时参数的的个数 
// *argv[] 执行命令时 所有的如参的 数组

// 使用  ./echoClient "this is " 传递参数 给 argv
int main(int argc, char const *argv[])
{
    // 准备 一个邮箱
    int sockFd;
    char * message;
    struct sockaddr_in server_addr;
    
    // 如果 执行命令的 参数 
    if (argc != 2)
    {
        fputs("usage ./eoch_client message \n ", stderr);
        exit(1);
    }
    if(argv){
        message = argv[1];
        printf("message : %s\n", message);
        sockFd = socket(AF_INET, SOCK_STREAM, 0);
        // 将 server_addr 清零
        // memset是计算机中C/C++语言初始化函数。作用是将某一块内存中的内容全部设置为指定的值， 这个函数通常为新申请的内存做初始化工作。
        memset(&server_addr, '\0', sizeof(struct sockaddr_in));
        // 协议家族
        server_addr.sin_family = AF_INET;
        // 把字符串的 ip地址 转换成网络 socket 的地址
        inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr);
        // 因为网络编成字节顺序是反的 所以需要 htons 
        // 配置端口号
        server_addr.sin_port = htons(SERVER_PORT);
        
        // 连接服务
        // (struct sockaddr * ) 强制转换数据类型
        connect(sockFd, (struct sockaddr *)&server_addr, sizeof(server_addr));
        
        // xi
        write(sockFd, message, strlen(message));
        printf(" -- server_addr.sin_port -- \n");
        int n;
        char buffer[256];
        n = read(sockFd, buffer, sizeof(buffer) - 1);
        // 定义buffer 接收读取的内容
        if(n>0){
            buffer[n] = '\0';
            printf("receive %s\n", buffer);
        } else {
            printf("error \n");
        }
        printf(" -- Finished -- \n");
        close(sockFd);
    }


    return 0;
}


