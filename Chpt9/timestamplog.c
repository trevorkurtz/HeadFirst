#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char* now()
{
    time_t t;
    time(&t);
    return asctime(localtime(&t));
}

void remove_newline(char* input)
{
    int lastchar = strlen(input)-1;
    printf("lastchar: '%d' and character: '%c'\n", lastchar, input[lastchar]);
    
    if(input[lastchar] == '\n')
    {
        input[lastchar] = ' ';
    }
}

/* Master Control Program utility.
   Records guard patrol check-ins. */

int main()
{
    char comment[80];
    char cmd[120];
    fgets(comment, 80, stdin);
    remove_newline(comment);
  
    sprintf(cmd, "echo '%s %s' >> reports.log", comment, now());
    printf("comment: %s\n", comment);
    printf("cmd: %s \n", cmd);
    system(cmd);
    return 0;
}