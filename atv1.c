#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int count=0;
int n;
pthread_mutex_t mutex;
pthread_cond_t cond;


void* tarefa (void* argv){
    pthread_mutex_lock(&mutex);
    count = count+1;
    int id = *(int*)argv;

    if(count < n){
        while(count < n){
            pthread_cond_wait(&cond, &mutex);
        }
    } else {
        pthread_cond_broadcast(&cond);
    }
    pthread_mutex_unlock(&mutex);

    for(int i = 0; i <= 99; i++){
        printf("Thread %d: %d\n", id+1, i);
        if(i == 99){
            printf("\nThread %d terminou!\n\n", id+1);
        }
    }
    return NULL;
}

int main (){
    pthread_cond_init(&cond, NULL);
    printf("Digite quantas threads você quer utlizar?\n");    
    scanf("%d", &n);
    int ids[n];

    pthread_t *threads = malloc(n * sizeof(pthread_t));
    pthread_mutex_init(&mutex, NULL);
    
    for(int i=0; i<n; i++){
        ids[i] = i;
        pthread_create(&threads[i], NULL, tarefa, &ids[i]);
    }
    for(int i=0; i<n; i++){
        pthread_join(threads[i], NULL);
    }

    free(threads);
}