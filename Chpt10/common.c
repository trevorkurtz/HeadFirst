#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include "common.h"

void error(char *msg)
{
    fprintf(stderr, "%s: %s\n", msg, strerror(errno));
    exit(1);
}