//
// Created by 徐普 on 15/9/10.
//

#include "pipe.h"

int main() {

    // init pipe
    int fd_pipe[2];
    if (pipe(fd_pipe) < 0) {
        perror("pipe()");
        return -1;
    }

    // init buffer
    int buffer_size = 128;
    char buffer[buffer_size];
    memset(buffer, 0, buffer_size);

    // fork
    pid_t pid = fork();
    if (pid == 0) {

    }

}