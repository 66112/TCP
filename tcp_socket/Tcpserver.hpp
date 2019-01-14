#pragma once
#include <iostream>
#include <string>
#include <string.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>
class Sock
{
public:
    Sock():_fd(-1)
    {}
    bool Socket()   //创建套接字
    {
        _fd = socket(AF_INET,SOCK_STREAM,0);
        if(_fd < 0){
            std::cerr << "socket error!" << std::endl;
            return false;
        }
        return true;
    }
    bool Bind(const std::string& ip,const uint16_t port)  //绑定
    {
        struct sockaddr_in local;
        bzero(&local,sizeof(local));
        local.sin_family = AF_INET;
        local.sin_port = htons(port);  //转成网络端口
        local.sin_addr.s_addr = inet_addr(ip.c_str()); //转成网络字节序
        int ret = bind(_fd,(struct sockaddr*)&local,sizeof(local)); //绑定本地的ip和port
        if(ret < 0){
            std::cerr << "bind error!" << std::endl;
            return false;
        }
        return true;
    }
    bool Listen(int num)    //监听
    {
        int ret = listen(_fd,num);  //声明_fd处于监听状态，最多允许有num个客户处于连接等待状态
        if(ret < 0){
            std::cerr << "listen error!" << std::endl;
            return false;
        }
        return true;
    }
    int Accept()   //接受客户端连接
    {
        sockaddr_in peer;
        socklen_t len = sizeof(peer);
        int new_sock = accept(_fd,(struct sockaddr*)&peer,&len);  //传出客户端的信息
        if(new_sock < 0){
            std::cerr << "accept error!" << std::endl;
            return -1;
        }
        std::cout << "New Client Connect" << std::endl;
        return new_sock;
    }
    bool Close() const //关闭
    {
        close(_fd);
        return true;
    }
    ~Sock()
    {}
private:
    int _fd;
};
class Server
{
public:
    Server(const std::string& ip,const uint16_t& port)
        :_ip(ip),_port(port)
    {}
    bool ServerInit(int num)
    {
        Listen_sock.Socket();
        Listen_sock.Bind(_ip,_port);
        Listen_sock.Listen(num);
        return true;
    }
    bool ServerStart()
    {
        int new_sock = Listen_sock.Accept();
        char buf[1024];
        for( ; ; ){
            ssize_t sz = read(new_sock,buf,sizeof(buf)-1);
            if(sz > 0){
                buf[sz] = 0;
                std::cout << "client# " << buf << std::endl;
                std::string answer = buf;
                answer += "_123";
                write(new_sock,answer.c_str(),answer.size());
            }
            else if(sz == 0){
                std::cout << "client quit!" << std::endl;
                break;
            } 
            else{
                std::cout << "read error!" << std::endl;
                continue;
            }
        }
        Listen_sock.Close();
        return true;
    }
    ~Server()
    {}
private: 
    Sock Listen_sock;
    std::string _ip;
    uint16_t _port;
};
