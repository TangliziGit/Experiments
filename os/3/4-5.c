#include <stdio.h>
#include <stdlib.h>
int fork(void);
void sleep(int);
void wait(int);

int main(void){
    int p1,p2,i;
    p1 = fork();
    if (p1 == 0){
         for ( i = 0; i < 10; i++ )
            printf ( "parent%d\n", i );

        // 一直阻塞当前进程运行，直到有当前进程的子进程结束，wait方法会返回
        wait ( 0 );   /* 保证在子进程终止前，父进程不会终止*/
        exit ( 0 );
    }else{
        p2 = fork ( );
        if (p2 == 0){
            for ( i = 0; i < 10; i++ )
                printf ( "son %d\n", i );
            wait ( 0 );     /* 保证在子进程终止前，父进程不会终止*/
            exit ( 0 );   /*向父进程信号0且该进程推出*/
        }else{
            for ( i = 0; i < 10; i++)
                printf ("grandchild %d\n", i );
            exit ( 0 );
        }
    }

    return 0;
}
