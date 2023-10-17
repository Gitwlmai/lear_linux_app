#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>


int main(int argc, char **argv)
{
    int fd = 0;
    int write_size = 0;
    int i = 0;
    if(argc != 2)
    {
        printf("usage : %s <file>\n", argv[0]);
        return -1;
    }

    fd = open(argv[1], O_RDWR | O_CREAT, 0666);
    if(fd < 0)
    {
        printf("open %s failed \n", argv[1]);
        printf("errno is %d \n", errno);
        printf("strerror is %s \n", strerror(errno));
        perror("open");
        return -1;
    }

    printf("fd = %d \n", fd);
    printf("lseek offset %d\n", lseek(fd, 5, SEEK_SET));
    write(fd, "zzz", 3);
    
    close(fd);

    return 0;
}