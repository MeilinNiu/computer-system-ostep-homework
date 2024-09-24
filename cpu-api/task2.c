#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd = open("testfile.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    pid_t pid = fork();
    if (pid == 0) { // Child process
        write(fd, "Child writing.\n", 16);
    } else { // Parent process
        write(fd, "Parent writing.\n", 17);
    }

    close(fd);
    return 0;
}

