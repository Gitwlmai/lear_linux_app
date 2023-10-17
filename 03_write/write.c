#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
/*
*./write str1 str2 ....
*argc = 3
*argv[0] = ./write
*argv[1] = str1
*argv[2] = str2
*/


int main(int argc, char **argv)
{
    int fd = 0;
    int write_size = 0;
    int i = 0;
    if(argc < 3)
    {
        printf("usage : %s <file> <str1> <str2>\n", argv[0]);
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

    for(i = 2; i < argc; i++)
    {
        write_size = write(fd, argv[i], strlen(argv[i]));
        if(write_size != strlen(argv[i]))
        {
            perror("write");
            return -1;
        }
        write(fd, "\r\n", 2);
    }

    close(fd);

    return 0;
}