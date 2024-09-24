#include <stdio.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();

    if (pid == 0) { // Child process
        execl("/bin/ls", "ls", NULL);
        // If exec fails
        perror("execl failed");
    }

    return 0;
}

