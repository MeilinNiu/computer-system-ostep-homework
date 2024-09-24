#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    int pipefd[2];
    pipe(pipefd);

    pid_t pid1 = fork();
    if (pid1 == 0) { // First child
        close(pipefd[0]); // Close read end
        dup2(pipefd[1], STDOUT_FILENO); // Redirect stdout to pipe
        printf("Output from first child.\n");
        close(pipefd[1]); // Close write end
        return 0;
    }

    pid_t pid2 = fork();
    if (pid2 == 0) { // Second child
        close(pipefd[1]); // Close write end
        char buffer[100];
        read(pipefd[0], buffer, sizeof(buffer)); // Read from pipe
        printf("Second child received: %s", buffer);
        close(pipefd[0]); // Close read end
        return 0;
    }

    close(pipefd[0]);
    close(pipefd[1]);
    return 0;
}

