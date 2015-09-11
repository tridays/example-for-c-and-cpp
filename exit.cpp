#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    pid_t result = fork();
    if (result < 0)
        perror("fork");

    if (result == 0) {
        printf("This is _exit test\n");
        printf("This is the content in the child's buffer");
        _exit(0);
    } else {
        printf("This is exit test\n");
        printf("This is the content in the parent's buffer");
        exit(0);
    }
    return 0;
}

/* This is _exit test
 * This is exit test
 * This is the content in the parent's buffer
 * 即 exit 将输出 I/O 缓冲区
 */