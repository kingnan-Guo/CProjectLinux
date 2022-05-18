/**
 * @file callBackServer.cpp
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

#define SERVER_PORT 666

int main()
{
    // 准备信箱
    int sock; // 代表信箱
    // 地址使用服务器的地址
    struct sockaddr_in server_addr;
    //  创建一个信箱
    // AF_INET   网络通信家族 TCIP 
    // SOCK_STREAM  使用 sock协议
    sock = socket(AF_INET, SOCK_STREAM, 0);
    // printf("sock = %u", sock);

    // 把地址端口号写在标签上面
    // 清空标签写上地址 端口号
    bzero(&server_addr, sizeof(server_addr));
    // 写地址前 要指定 协议家族 IPV4
    server_addr.sin_family = AF_INET;
    // 绑定本机的所有 IP 地址
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    // htons 主机(字节序) to 网络
    // 因为网络编成字节顺序是反的 所以需要 htons 
    // 配置端口号
    server_addr.sin_port = htons(SERVER_PORT);


    // 标签准备好要贴到 收信的信箱上去
    // (struct sockaddr * ) 强制转换数据类型
    bind(sock, (struct sockaddr * )&server_addr, sizeof(server_addr));

    // 128 表示 同时来的信件 接收多少个
    listen(sock, 128);

    // 等待
    printf("waiting pc content\n");

    int done = 1;
    while (done)
    {
        // printf("while");
        struct sockaddr_in client;
        // printf("client = %d", client);
        // 定义客户端 sock
        int client_sock;
        char client_ip[64];
        // 
        socklen_t client_addr_len;
        client_addr_len = sizeof(client);
        // printf("client_addr_len = %d", client_addr_len);
        // 从 sock 中接收
        client_sock = accept(sock, (struct sockaddr * )&client, &client_addr_len);
        // printf("client_sock = %d", client_sock);
        // printf("clint ip is %S\t prot: %d \n", 
        //     inet_ntop(AF_INET, &client.sin_addr.s_addr, client_ip, sizeof(client_ip)),
        //     ntohs(client.sin_port)
        // );
        printf("port: %d \n", ntohs(client.sin_port));
    }
    


    return 0;
}

