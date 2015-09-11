#include <unistd.h>
#include <cstdio>
#include <cstdlib>
#include <sys/wait.h>

using namespace std;

int main() {
    pid_t child_pid = fork();
    int count = 1;
    if (child_pid < 0) {
        perror("fork()");
    } else if (child_pid == 0) {
        printf("[PID: %d] child  (parent_pid: %d, child_pid: %d).\n", getpid(), getppid(), child_pid);
        count++;
    } else {
        // 如果父进程先于子进程退出 getppid() == 1
        // 当然在这里因为下文中的 waitpid() 所以不会发生这种情况
        printf("[PID: %d] parent (parent_pid: %d, child_pid: %d).\n", getpid(), getppid(), child_pid);
        count++;
    }
    printf("count: %d\n", count); // 证明两进程的变量（数据空间）在 fork() 后是独立的

    //

    if (child_pid == 0) {
        _exit(255);
    } else {
        int child_ret_status = 0;
        waitpid(child_pid, &child_ret_status, 0);
        // wait(&pid_ret);

        int child_ret = 0;
        if (WIFEXITED(child_ret_status)) {
            // 正常退出，返回 exit 的低 8 位
            printf("child exited.\n");
            child_ret = WEXITSTATUS(child_ret_status);
        } else if (WIFSIGNALED(child_ret_status)) {
            // 异常退出
            printf("child signaled.\n");
            child_ret = WTERMSIG(child_ret_status);
        } else if (WIFSTOPPED(child_ret_status)) {
            printf("child stopped.\n");
            child_ret = WSTOPSIG(child_ret_status);
        }
        if (child_ret == -1) {
            perror("waitpid()");
        } else {
            printf("child %d return %d\n", child_pid, child_ret);
        }
    }

    return 0;
}