#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
/*
*./read 1.txt 
*argc = 2
*argv[0] = ./read
*argv[1] = 1.txt
*/

int main(int argc, char **argv)
{
    int fd = 0;
    int size = 0;
    int i = 0;
    char buf[1024];
    if(argc != 2)
    {
        printf("usage : %s <file> \n", argv[0]);
        return -1;
    }

    fd = open(argv[1], O_RDONLY);
    if(fd < 0)
    {
        printf("open %s failed \n", argv[1]);
        printf("errno is %d \n", errno);
        printf("strerror is %s \n", strerror(errno));
        perror("open");
        return -1;
    }

    printf("fd = %d \n", fd);

    while(1)
    {
        size = read(fd, buf, sizeof(buf) - 1);
        if(size < 0)
        {
            perror("read");
            close(fd);
            return -1;
        }
        else if(size == 0)
        {
            break;
        }
        else
        {
            buf[size] = '\0';
            printf("%s \n", buf);
        }
    }

    close(fd);

    return 0;
}