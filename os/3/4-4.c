#include <stdio.h>
int fork(void);
void sleep(int);

int main(void){
    int p1, p2;
    p1=fork();

    if (p1 == 0){                     /*子进程创建成功*/
        sleep(1);            /*延长子进程运行时间*/
        putchar('b');
    }else{
        p2 = fork();
        if (p2 == 0){          /*子进程创建成功*/
            sleep(1);           /*延长子进程运行时间*/
            putchar('c');
        }else{
            sleep(1);           /*延长进程运行时间*/
            putchar('a');        /*父进程执行*/
        }
    }

    return 0;
}
