#include <unistd.h>
#include "common.h"

int main()
{
    int fd[2];
    if (-1 == pipe(fd)) {
        error("Can't create the pipe");
    }
    pid_t pid = fork();
    if (-1 == pid) {
        error("Can't fork process");
    }

    if(!pid) {
        // child
        close(fd[0]);   // close read
        dup2(fd[1], 1); // connect write to standard out
    } else {
        // parent
        dup2(fd[0], 0); // read to standard in
        close(fd[1]);   // close write
    }
}