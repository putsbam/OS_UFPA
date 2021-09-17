/*
Código adaptado de Carlos Maziero e Codophobia
http://wiki.inf.ufpr.br/maziero/doku.php?id=socm:start
https://github.com/codophobia/producer-consumer-problem-solution-in-c/blob/master/producer-consumer.c
*/

#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>

/*
Esse programa fornece uma possível solução para o problema do produtor-consumidor usando Mutex e Semáforos
Para demonstrar a solução, foram usados 5 produtores e 5 consumidores.
*/

#define MaxItems 5      // Máximo de itens que um consumidor pode consumir, ou que um produtor pode produzir
#define BufferSize 5    // Tamanho do buffer

sem_t vagas;            // Semáforo usado para suspender produção quando não há vagas
sem_t itens;            // Semáforo usado para impedir consumo quando não há itens

// Contadores para o número de itens e vagas no Buffer
int num_vagas = BufferSize;
int num_itens = 0;

int in = 0;     // Posição do Buffer onde um item será inserido
int out = 0;    // Posição do Buffer de onde um item será removido

int buffer[BufferSize];
pthread_mutex_t mutex;  // Controla a entrada ao buffer


void *producer(void *pno)
{   
    int item;
    for(int i = 0; i < MaxItems; i++) {
        item = rand();                  // Produz um item aleatório
        sem_wait(&vagas);               // Decrementa semáforo das vagas
        pthread_mutex_lock(&mutex);     // Pede acesso ao buffer
        num_vagas--;
        num_itens++;
        buffer[in] = item;
        printf("Produtor %d: inseriu um item (Buffer: %d itens, %d vagas)\n", *(int *)pno, num_vagas, num_itens);
        in = (in+1)%BufferSize;
        pthread_mutex_unlock(&mutex);   // Libera o buffer
        sem_post(&itens);               // Incrementa semáforo dos itens
    }
}
void *consumer(void *cno)
{   
    int item;
    for(int i = 0; i < MaxItems; i++) {
        sem_wait(&itens);               // Decrementa semáforo dos itens
        pthread_mutex_lock(&mutex);     // Pede acesso ao buffer
        num_vagas++;
        num_itens--;
        item = buffer[out];             // Recebe um item
        printf("Consumidor %d: removeu um item (Buffer: %d itens, %d vagas)\n", *(int *)cno, num_vagas, num_itens);
        out = (out+1)%BufferSize;
        pthread_mutex_unlock(&mutex);   // Libera o buffer
        sem_post(&vagas);               // Incrementa semáforo das vagas
    }
}

int main()
{   

    pthread_t pro[5],con[5];
    pthread_mutex_init(&mutex, NULL);
    sem_init(&vagas,0,BufferSize);
    sem_init(&itens,0,0);

    int a[5] = {1,2,3,4,5};             // Usado apenas para numerar threads

    // Criação das threads produtoras
    for(int i = 0; i < 5; i++)
        if(pthread_create(&pro[i], NULL, producer, (void *)&a[i])) {
            perror("pthread_create");
            exit(1);
        }

    // Criação das threads consumidoras
    for(int i = 0; i < 5; i++)
        if(pthread_create(&con[i], NULL, consumer, (void *)&a[i])) {
            perror("pthread_create");
            exit(1);
        }
    
    // Espera as threads concluírem
    for(int i = 0; i < 5; i++)
        pthread_join(pro[i], NULL);
    for(int i = 0; i < 5; i++)
        pthread_join(con[i], NULL);

    // Encerra as threads
    pthread_mutex_destroy(&mutex);
    sem_destroy(&vagas);
    sem_destroy(&itens);

    return 0;
    
}
