#include <stdio.h>
#include <unistd.h>

int my_fgetc(int fd) {
//    int fd = fileno(stream); // Get file descriptor from the FILE pointer

    if (fd == -1) {
        return EOF; // Return EOF on error
    }

    char c;
    ssize_t bytesRead = read(fd, &c, 1); // Read a single character

    if (bytesRead == -1 || bytesRead == 0) {
        return EOF; // Return EOF on error or end-of-file
    }

    return (int)c; // Return the character read as an integer
}

