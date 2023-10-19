#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
/*
*./example score.csv result.csv
*argc = 3
*argv[0] = ./example
*argv[1] = score.csv
*argv[2] = result.csv
*/

//打开处理文件和结果文件
//逐行读取处理文件的数据
//逐行处理数据
//将处理后的数据写入结果文件

//问：怎么判断读完1行数据？
//答：回车换行

//返回值
//大于0表示读到了多少个字节数据
//等于0表示读到了回车换行
//小于0表示发生了错误或者读到了尾部并且没有读到数据
int read_line(int fd, char *buf)
{
    char c;
    int len;
    int i = 0;
    int error = 0;
    while(1)
    {
        len = read(fd, &c, 1);
        if(len < 0)
        {
            //发生了错误
            perror("read");
            error = 1;
            break;
        }
        else if(len == 0)
        {
            //读到文件末尾
            printf("read end of file \n");
            error = 1;
            break;
        }
        else
        {
            //读到数据
            if((c != '\n') && (c != '\r'))
            {
                buf[i] = c;
                i++;
            }
            else
            {
                break;
            }
        }
    }

    buf[i] = '\0';

    if(error && i == 0)
    {
        return -1;
    }
    else
    {
        return i;
    }
}

void proc_data(char *data_buf, char *result_buf)
{
    //,语文,数学,英语,总分,评价
    // 张三,90,91,92,,
    // 李四,80,81,82,,
    // 王五,70,71,72,,
    char name[64];
    int score[3];
    char *level_str[3] = {"A", "B", "C"};
    int level = 0;
    int sum = 0;
    if(data_buf[0] == ',')
    {
        strcpy(result_buf, data_buf);
    }
    else
    {
        sscanf(data_buf, "%[^,],%d,%d,%d", name, &score[0], &score[1], &score[2]);
        sum = score[0] + score[1] + score[2];
        if(sum >= 270)
        {
            level = 0;
        }
        else if(sum >= 240)
        {
            level = 1;
        }
        else
        {
            level = 2;
        }
        sprintf(result_buf, "%s,%d,%d,%d,%d,%s", name, score[0], score[1], score[2], sum, level_str[level]);
    }
}

int main(int argc, char **argv)
{
    int fd_data = 0;
    int fd_result = 0;
    int write_size = 0;
    char buf[1024];
    char result_buf[1024];
    int len = 0;
    if(argc != 3)
    {
        printf("usage : %s <file1> <file2> \n", argv[0]);
        return -1;
    }

    fd_data = open(argv[1], O_RDONLY);
    if(fd_data < 0)
    {
        perror("open data file");
        return -1;
    }

    fd_result = open(argv[2], O_RDWR | O_CREAT | O_TRUNC, 0666);
    if(fd_result < 0)
    {
        perror("open result file");
        return -1;
    }

    printf("fd_data = %d \n", fd_data);
    printf("fd_result = %d \n", fd_result);

    while(1)
    {
        len = read_line(fd_data, buf);
        if(len < 0)
        {
            break;
        }
        else if(len > 0)
        {
            proc_data(buf, result_buf);
            write(fd_result, result_buf, strlen(result_buf));
            write(fd_result, "\r\n", 2);
        }
    }

    close(fd_data);
    close(fd_result);
    return 0;
}