#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>

int main() {
    pid_t pid1 = fork();
    if (pid1 == 0) {
        clock_t start = clock();
        printf("Child 1: PID = %d, PPID = %d\n", getpid(), getppid());
        clock_t end = clock();
        printf("Child 1 execution time: %.3f ms\n", (double)(end - start) * 1000 / CLOCKS_PER_SEC);
        return 0;
    }
    clock_t start_main = clock();
    pid_t pid2 = fork();
    if (pid2 == 0) {
        clock_t start = clock();
        printf("Child 2: PID = %d, PPID = %d\n", getpid(), getppid());
        clock_t end = clock();
        printf("Child 2 execution time: %.3f ms\n", (double)(end - start) * 1000 / CLOCKS_PER_SEC);
        return 0;
    }
    wait(NULL);
    wait(NULL);
    printf("Parent: PID = %d, PPID = %d\n", getpid(), getppid());
    clock_t end_main = clock();
    printf("Parent execution time: %.3f ms\n", (double)(end_main - start_main) * 1000 / CLOCKS_PER_SEC);
    return 0;
}
