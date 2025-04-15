#include "common.h"

#include <fstream>
#include <iostream>
#include <stdexcept>
#include <cstring>
#include <string_view>
#include <fcntl.h>
#include <fmt/base.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/epoll.h>

#define MAX_EVENTS 10
#define BUFFER_SIZE 1024

// 封装错误检查逻辑的函数
void check_error(int result, const char* message) {
    if (result == -1) {
        throw std::runtime_error(std::string(message) + ": " + strerror(errno));
    }
}

void handle_new_connection(int epoll_fd, int listen_fd) {
    struct sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);

    // 检查accept是否成功
    int client_fd =
        accept(listen_fd, (struct sockaddr*)&client_addr, &client_len);
    check_error(client_fd, "accept failed");

    // 设置客户端连接为非阻塞模式
    int flags = fcntl(client_fd, F_GETFL, 0);
    check_error(flags, "fcntl F_GETFL failed");

    flags |= O_NONBLOCK;
    check_error(fcntl(client_fd, F_SETFL, flags), "fcntl F_SETFL failed");

    // 将客户端连接添加到epoll监听
    struct epoll_event event;
    event.data.fd = client_fd;
    event.events = EPOLLIN | EPOLLET;  // 边缘触发

    check_error(epoll_ctl(epoll_fd, EPOLL_CTL_ADD, client_fd, &event),
                "epoll_ctl add client failed");
}

void handle_client_data(int epoll_fd, int client_fd) {
    char buffer[BUFFER_SIZE];
    ssize_t bytes_read = read(client_fd, buffer, sizeof(buffer) - 1);

    // 检查read是否成功
    check_error(bytes_read, "read failed");

    if (bytes_read == 0) {
        // 客户端关闭连接
        close(client_fd);
        check_error(epoll_ctl(epoll_fd, EPOLL_CTL_DEL, client_fd, nullptr),
                    "epoll_ctl del client failed");
        return;
    }

    if (std::string_view{buffer, static_cast<size_t>(bytes_read)} == "quit\n") {
        check_error(epoll_ctl(epoll_fd, EPOLL_CTL_DEL, client_fd, nullptr),
                    "epoll_ctl del client failed");
        close(client_fd);
        fmt::println("client send quit");
        return;
    }

    buffer[bytes_read] = '\0';
    std::cout << "Received from client: " << buffer << std::endl;

    // 将数据回发给客户端
    check_error(write(client_fd, buffer, bytes_read), "write failed");
}

MYTEST(1) {
    try {
        int listen_fd = socket(AF_INET, SOCK_STREAM, 0);
        check_error(listen_fd, "socket failed");

        struct sockaddr_in server_addr;
        server_addr.sin_family = AF_INET;
        server_addr.sin_addr.s_addr = INADDR_ANY;
        server_addr.sin_port = htons(8080);

        check_error(bind(listen_fd, (struct sockaddr*)&server_addr,
                         sizeof(server_addr)),
                    "bind failed");
        check_error(listen(listen_fd, 10), "listen failed");

        // 创建epoll实例
        int epoll_fd = epoll_create1(0);
        check_error(epoll_fd, "epoll_create1 failed");

        // 将监听套接字添加到epoll
        struct epoll_event event;
        event.data.fd = listen_fd;
        event.events = EPOLLIN | EPOLLET;  // 边缘触发

        check_error(epoll_ctl(epoll_fd, EPOLL_CTL_ADD, listen_fd, &event),
                    "epoll_ctl add listen failed");

        std::cout << "Echo server running on port 8080..." << std::endl;

        struct epoll_event events[MAX_EVENTS];
        while (true) {
            int nfds = epoll_wait(epoll_fd, events, MAX_EVENTS, -1);
            check_error(nfds, "epoll_wait failed");

            for (int n = 0; n < nfds; ++n) {
                if (events[n].data.fd == listen_fd) {
                    handle_new_connection(epoll_fd, listen_fd);
                } else if (events[n].events & EPOLLIN) {
                    handle_client_data(epoll_fd, events[n].data.fd);
                }
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
}
