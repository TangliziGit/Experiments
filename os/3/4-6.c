#include <stdio.h>
#include <stdlib.h>
int fork(void);
void sleep(int);
void wait(int);
void lockf(int, int, int);

int main(void){
    int p1, p2, i;
    p1 = fork();
    if (p1 == 0){
        lockf ( 1, 1, 0 );
        for ( i = 0; i < 10; i++ )
           printf ( "parent %d\n", i );
        lockf ( 1, 0, 0 );
        wait ( 0 );    /* 保证在子进程终止前，父进程不会终止*/
        exit ( 0 );
    }else{
        p2 = fork();
        if ( p2 == 0 ){
            lockf ( 1, 1, 0 );
            for ( i = 0; i < 10; i++ )
                printf ( "son %d\n", i );
            lockf ( 1, 0, 0 );
            wait ( 0 );    /* 保证在子进程终止前，父进程不会终止*/
            exit ( 0 );
        }else{
            lockf ( 1, 1, 0 );
            for ( i = 0; i < 10; i++ )
                printf ( "daughter %d\n", i );
            lockf ( 1, 0, 0 );
            exit ( 0 );
        }
    }

    return 0;
}
