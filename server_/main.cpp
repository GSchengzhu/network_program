#include "connection.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/poll.h>
#include <atomic>
#include <signal.h>
#include <sys/epoll.h>
#include <unordered_map>
#include <unistd.h>
#include "thread_pool.h"

sig_atomic_t g_flag = 0;
std::unordered_map<int,Connection> g_connections;

void signalHandle(int no)
{
    g_flag = 0; 
}

void dealRead(int epoll_fd,Connection& connection)
{
    connection.read();
    epoll_event ev;
    ev.data.fd = connection.getFD();
    if(connection.process())
    {
        ev.events = EPOLLOUT;
    }else
    {
        ev.events = EPOLLIN;
    }
    epoll_ctl(epoll_fd,EPOLL_CTL_MOD,connection.getFD(),&ev);
}

void dealWrite(int epoll_fd,Connection& connection)
{
    size_t writed = connection.write();
    if(writed == 0)
    {
        epoll_event ev;
        ev.data.fd = connection.getFD();
        if(connection.process())
        {
            ev.events = EPOLLOUT;
        }else
        {
            ev.events = EPOLLIN;
        }
        epoll_ctl(epoll_fd,EPOLL_CTL_MOD,connection.getFD(),&ev);
    }else if(writed < 0 && errno == EAGAIN)
    {
        epoll_event ev;
        ev.data.fd = connection.getFD();
        ev.events = EPOLLOUT;
        epoll_ctl(epoll_fd,EPOLL_CTL_MOD,connection.getFD(),&ev);
    }
}

int main()
{
    int serverfd = socket(AF_INET,SOCK_STREAM,0);
    if(serverfd < 0)
    {
        perror("socket error:");
        return -1;
    }
    
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(9999);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    if(bind(serverfd,(struct sockaddr*)&server_addr,sizeof(server_addr)) < 0)
    {
        perror("bind error:");
        return -1;
    }

    listen(serverfd,10);

    signal(SIGUSR1,signalHandle);
    g_flag = 1;

    int epoll_fd = epoll_create1(0);
    if(epoll_fd < 0)
    {
        perror("epoll_create1 error:");
        return -1;
    }

    struct epoll_event ev;
    ev.events = EPOLLIN;
    ev.data.fd = serverfd;
    if(epoll_ctl(epoll_fd,EPOLL_CTL_ADD,serverfd,&ev) < 0)
    {
        perror("epoll_ctl error:");
        return -1;
    }

    while(g_flag)
    {
        epoll_event events[1024];
        int nfds = epoll_wait(epoll_fd,events,1024,-1);
        if(nfds < 0)
        {
            perror("epoll_wait error:");
            return -1;
        }

        for(int i = 0; i < nfds; i++)
        {
            if(events[i].data.fd == serverfd)
            {
                sockaddr client;
                socklen_t client_size;
                int client_fd = accept(serverfd,&client,&client_size);
                if(client_fd > 0)
                {
                    g_connections.emplace(client_fd,Connection(client_fd));
                }
            }else if(events[i].events == EPOLLIN)
            {
                //g_connections
                Connection client =  g_connections.at(events[i].data.fd);
                ThreadPool::getInstace()->addWork(std::bind(&dealRead,epoll_fd,client));
            }else if(events[i].events == EPOLLOUT)
            {
                Connection client =  g_connections.at(events[i].data.fd);
                ThreadPool::getInstace()->addWork(std::bind(&dealWrite,epoll_fd,client));
                //write data
            }
        }
    }

    close(serverfd);

}