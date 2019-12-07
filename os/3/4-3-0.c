#include <stdio.h>
#include <pthread.h>
#define INC_N 20
#define DEC_N 20

void func(void* args){
    int res=0;
    printf("func\n");
    pthread_exit((void*)&res);
}

int main(void){
    int *res;
    pthread_t thread_id;
    pthread_create(&thread_id, NULL, (void *)func, NULL);
    pthread_join(thread_id, (void**)&res);

    printf("thread_id %d\n", thread_id);
    printf("result %d\n", *res);

    // for (int i=0; i<INC_N; i++)
    //     print("parent: %3d\n", i);

    return 0;
}
