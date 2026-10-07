#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_ARGS 64

int main() {
    char line[256];
    char *args[MAX_ARGS];
    while (1) {
        printf("> ");
        fflush(stdout);
        if (!fgets(line, sizeof(line), stdin)) break;
        line[strcspn(line, "\n")] = 0;
        if (strlen(line) == 0) continue;
        if (strcmp(line, "exit") == 0) break;
        int argc = 0;
        char *token = strtok(line, " ");
        while (token != NULL && argc < MAX_ARGS - 1) {
            args[argc++] = token;
            token = strtok(NULL, " ");
        }
        args[argc] = NULL;
        int background = 0;
        if (argc > 0 && strcmp(args[argc - 1], "&") == 0) {
            background = 1;
            args[argc - 1] = NULL;
            argc--;
        }
        if (argc == 0) continue;
        pid_t pid = fork();
        if (pid < 0) {
            perror("fork");
            continue;
        }
        if (pid == 0) {
            execvp(args[0], args);
            perror("execvp");
            exit(EXIT_FAILURE);
        } else {
            if (!background) {
                wait(NULL);
            } else {
                printf("[bg] PID %d\n", pid);
            }
        }
    }
    return 0;
}
