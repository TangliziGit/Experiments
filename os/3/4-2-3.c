#include <stdio.h>
#define INC_N 20
#define DEC_N 30
int shared=0;

int main(void){
    int pid=fork();

    if (pid>0){
        for (int i=0; i<INC_N; i++)
            shared++;
        printf("parent: %3d\n", shared);
    }else if (pid==0){
        for (int i=0; i<DEC_N; i++)
            shared--;
        printf("child: %3d\n", shared);
    }

    return 0;
}
