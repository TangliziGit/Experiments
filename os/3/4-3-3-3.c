#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define N 5
int shared_pass;

int main(int is_parent){
    int *shared_add=NULL;
    int shared=0;
    pthread_t thread_id;

    if (is_parent){
        pthread_create(&thread_id, NULL, (void *)main, 0);
        pthread_join(thread_id, (void**)&shared_add);
    }

    printf("is_parent:%d\n", is_parent);

    for (int i=0; i<N; i++){
        if (is_parent)
            printf("parent: %3d\n", ++shared);
        else
            printf("thread: %3d\n", --shared);
    }

    if (!is_parent){
        shared_pass=shared;
        pthread_exit((void*)&shared);
    }else{
        printf("shared in parent:\n\taddress:%p val:%d\n", &shared, shared);
        printf("shared in sub thread:\n\taddress:%p val:%d (shared_pass %d)\n",
                shared_add, *shared_add, shared_pass);
    }

    return 0;
}
