#include <stdio.h>
#define INC_N 5
#define DEC_N 5

int main(void){
    int shared=0;

    for (int i=0; i<INC_N; i++)
        printf("%3d\n", ++shared);
    for (int i=0; i<DEC_N; i++)
        printf("%3d\n", --shared);

    return 0;
}
