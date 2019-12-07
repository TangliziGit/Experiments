#include <stdio.h>
#include <pthread.h>
#define N 5

void func(int* shared){
    for (int i=0; i<N; i++)
        printf("sub thread: %3d\n", ++(*shared));
    pthread_exit((void*)0);
}

int main(void){
    int shared=0;
    pthread_t thread_id;
    int err=pthread_create(&thread_id, NULL, (void *)func, (void**)(&shared));

    if (err != 0){
        fprintf(stderr, "Con not create a thread.\n");
        return 1;
    }

    pthread_join(thread_id, NULL);
    for (int i=0; i<N; i++)
        printf("parent: %3d\n", --shared);

    return 0;
}
