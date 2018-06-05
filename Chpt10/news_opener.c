#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include "common.h"




int main(int argc, char *argv[])
{
    char *phrase = argv[1];
    char *vars[] = {"RSS_FEED=http://www.cnn.com/rss/celebs.xml", NULL};
    int fd[2];
    if (-1 == pipe(fd)) {
        error("Can't create the pipe");
    };
    pid_t pid = fork();
    if (-1 == pid) {
        error("Can't fork process");
    };
     if(!pid) {
        // child
        close(fd[0]);   // close read
        dup2(fd[1], 1); // connect write to standard out
        system("ls -l");
        /*
        if(execle("ls", "ls", " -l", NULL, vars) == -1) {
            error("Can't run ls");
        }
        */
        
    } else {
        // parent
        dup2(fd[0], 0); // read to standard in
        close(fd[1]);   // close write
        char line[255];
        while (fgets(line, 255, stdin)) {
            printf("%s", line);
        }
    }
    return 0;

}