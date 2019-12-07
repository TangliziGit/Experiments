#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
void wait(int);
int pid1, pid2;

int main(void){
    int fd[2];
    int lock[2];
    char outpipe[100],inpipe[100];
    pipe(fd);                                       /*创建一个管道*/
    pipe(lock);                                     /*创建一个管道，作用是进程间同步，pid1首先运行*/
    while ((pid1 = fork()) == -1);
    if (pid1 == 0){
        lockf(fd[1], 1, 0);
        sprintf(outpipe, "child 1 process is sending message!");/*把串放入数组outpipe中*/
        write(fd[1], outpipe, 50);                  /*向管道写长为50字节的串*/
        sleep(5);                                   /*自我阻塞5秒*/
        lockf(fd[1], 0, 0);

        // 此处首先写入一个数据，作用是触发pid2的read操作
        outpipe[0]=1;
        write(lock[1], outpipe, 1);

        exit(0);
    }else{
        while ((pid2 = fork()) == -1);
        if (pid2 == 0){

            // 此处作用是等待pid1的write操作
            read(lock[0], NULL, 1);

            lockf(fd[1], 1, 0);                     /*互斥*/
            sprintf(outpipe, "child 2 process is sending message!");
            write(fd[1], outpipe, 50);
            sleep(5);
            lockf(fd[1], 0, 0);
            exit(0);
        }else{
            wait(0);                                /*同步*/
            read(fd[0], inpipe, 50);                /*从管道中读长为50字节的串*/
            printf("%s\n", inpipe);
            wait(0);
            read(fd[0], inpipe, 50);
            printf("%s\n", inpipe);
            exit(0);
        }
    }
}
