#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/epoll.h>
#include <liburing.h>

#define EPOLL_SIZE 1024
#define FILE_PATH "/home/heyuhan/leetcode/test/data/km44.txt"
#define BUFFER_SIZE 1024

int main() {
    // 创建epoll实例
    int epoll_fd = epoll_create1(0);
    if (epoll_fd == -1) {
        perror("epoll_create1");
        return -1;
    }

    // 初始化io_uring
    struct io_uring ring;
    if (io_uring_queue_init(1024, &ring, 0) != 0) {
        perror("io_uring_queue_init");
        return -1;
    }

    // 将io_uring的fd添加到epoll中
    struct epoll_event ev;
    ev.events = EPOLLIN;
    ev.data.ptr = &ring;
    if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, ring.ring_fd, &ev) != 0) {
        perror("epoll_ctl");
        return -1;
    }

    // 打开文件
    int fd = open(FILE_PATH, O_RDONLY);

    if (fd == -1) {
        perror("open");
        return -1;
    }

    // 分配缓冲区
    char buffer[BUFFER_SIZE];

    // 提交一个io_uring读取任务
    struct io_uring_sqe* sqe = io_uring_get_sqe(&ring);
    if (!sqe) {
        perror("io_uring_get_sqe");
        return -1;
    }

    io_uring_prep_read(sqe, fd, buffer, BUFFER_SIZE, 0);  // 从文件偏移0开始读取
    sqe->user_data = 456;                                 // 设置用户数据
    if (io_uring_submit(&ring) != 1) {
        perror("io_uring_submit");
        return -1;
    }

    // 使用epoll等待io_uring任务完成
    struct epoll_event events[EPOLL_SIZE];
    int nfds = epoll_wait(epoll_fd, events, EPOLL_SIZE, -1);
    if (nfds == -1) {
        perror("epoll_wait");
        return -1;
    }

    for (int i = 0; i < nfds; i++) {
        struct io_uring* ring = (struct io_uring*)events[i].data.ptr;
        struct io_uring_cqe* cqe;

        // 获取完成的任务
        while (io_uring_peek_cqe(ring, &cqe) == 0) {
            if (cqe->res < 0) {
                perror("io_uring read");
            } else {
                printf("Read %d bytes with user_data: %llu\n", cqe->res,
                       cqe->user_data);
                // 打印读取的内容
                buffer[cqe->res] = '\0';  // 确保字符串结束
                printf("Content: %s\n", buffer);
            }
            io_uring_cqe_seen(ring, cqe);  // 标记任务已处理
        }
    }

    // 清理资源
    close(fd);
    io_uring_queue_exit(&ring);
    close(epoll_fd);
    return 0;
}