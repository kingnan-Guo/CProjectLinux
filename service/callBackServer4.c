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

#define SERVER_PORT 8097

int main()
{
    printf("listing %u \n", SERVER_PORT);
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
        // printf("监听中 %u \n", SERVER_PORT);
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
        //     ,
        //     ntohs(client.sin_port)
        // );
        printf("clint ip is %s\t", inet_ntop(AF_INET, &client.sin_addr.s_addr, client_ip, sizeof(client_ip)));
        printf("port: %d \n", ntohs(client.sin_port));


        // 读取客户端发送的 数据
        // 定义buffer 接收读取的内容
        char buffer[256];
        // 定义len来接收客户端数据发送的长度
        int len;
        // 使用 read

        len = read(client_sock, buffer, sizeof(buffer) - 1);

        
        buffer[len] = '\0';
        
        printf("reciver[%d] : %s\n", len, buffer);
        // 发送数据给客户端
        // 使用 write
        // len = write(client_sock, "buffer\n", len);
        // len = write(client_sock, buffer, len);
        // printf("write finished len %d \n", len);

        // 转换成大写
        int i;
        for ( i = 0; i < len; i++)
        {
            // 此处分两种方式 
            // 第一种方式使用  asci 码的形式
            // if(buffer[i] >= 'a' && buffer[i] <= 'z'){
            //     buffer[i] = buffer[i] - 32;
            // }
            // 第二种方式使用 引入的 库 ctype 中的  大小写转换 函数 toupper 
             buffer[i] = toupper(buffer[i]);
        }
        len = write(client_sock, buffer, len);
        printf("write finished len %d \n", len);
        close(client_sock);
    }
    


    return 0;
}

