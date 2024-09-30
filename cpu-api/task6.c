#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();

    if (pid == 0) { // Child process
        return 42; // Exit with status 42
    } else { // Parent process
        int status;
        waitpid(pid, &status, 0); // Wait for the specific child to exit
        if (WIFEXITED(status)) {
            printf("Child exited with status %d\n", WEXITSTATUS(status));
        }
    }

    return 0;
}
