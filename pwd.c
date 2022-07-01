#include <errno.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>

void pwd(char* path, size_t size)
{
    char *pathPointer = getcwd(path, size);

    if (!pathPointer) {
        perror("getcwd() failed");
    }
}