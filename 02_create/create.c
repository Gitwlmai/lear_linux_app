#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
/*
*./create 1.txt
*argc = 2
*argv[0] = ./create
*argv[1] = 1.txt
*/


int main(int argc, char **argv)
{
    int fd = 0;
    if(argc != 2)
    {
        printf("usage : %s <file> \n", argv[0]);
        return -1;
    }

    fd = open(argv[1], O_RDWR | O_CREAT | O_TRUNC, 0444);
    if(fd < 0)
    {
        printf("open %s failed \n", argv[1]);
        printf("errno is %d \n", errno);
        printf("strerror is %s \n", strerror(errno));
        perror("open");
        return -1;
    }

    printf("fd = %d \n", fd);

    close(fd);

    return 0;
}