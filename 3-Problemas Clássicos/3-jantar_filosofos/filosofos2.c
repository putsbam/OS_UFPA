/*
Codigo em C criado por ANUSHKA DESHPANDE
para o problema clássico "O Jantar dos filosofos"
*/
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>

sem_t sala;
sem_t garfo[5];
/*Aqui, o semáforo sala é um semáforo de contagem, pois há uma sala de jantar que pode acomodar 4 filósofos. 
ou seja, considere que há 4 cadeiras na sala e esse é o recurso. 
Portanto, há várias instâncias do recurso na sala. Portanto, sala é um semáforo de contagem. */

void * filosofo(void *);
void comer(int);
int main()
{
	int i,a[5];
	pthread_t tid[5];
	/*Essas threads referem-se a 5 filósofos sentados ao redor da mesa. Os temos como threads porque queremos que 
	sejam executados simultaneamente, isto é, que vários filósofos comam ao mesmo tempo.*/
	
	sem_init(&sala,0,4);
	//A função sem_init () é usada para inicializar o semáforo. 
	
	/*O primeiro parâmetro é o ponteiro para o semáforo declarado.

     O segundo parâmetro é pshared. Se for zero, o semáforo é compartilhado entre os encadeamentos; 
	 caso contrário, é compartilhado entre os processos. Em nosso caso, é zero, o que significa que é compartilhado entre threads.

     O terceiro valor do parâmetro é o valor com o qual o semáforo é inicializado. 
	 Aqui, o semáforo sala  é inicializada como 4, o que significa que variará entre 0–3 e terá 4 valores.*/
     
	for(i=0;i<5;i++)
		sem_init(&garfo[i],0,1);
	/* como existem 5 garfos, criamos 5 semáforos binários referentes aos cinco garfos de4 0 a 4. */	
	for(i=0;i<5;i++){
		a[i]=i;
		pthread_create(&tid[i],NULL,filosofo,(void *)&a[i]);
	} 
	for(i=0;i<5;i++)
		pthread_join(tid[i],NULL);
}   /* poderá haver a situação em que todos os 5 threads começam a ser executados, ou seja, todos os 5 filósofos entram na sala e causam deadlock. 
      Portanto, estamos permitindo que 4 filósofos entrem na sala primeiro para que pelo menos um deles possa terminar de comer. */

void * filosofo(void * num)
//Estamos chamando a função a partir de pthread_create (linha 42) e passando a ela o endereço de uma variável inteira que se refere ao número do filósofo. 
{
	int filo=*(int *)num;

	sem_wait(&sala);
	//Em seguida, chamamos a função sem_wait que primeiro verifica se o recurso está disponível e, 
	//se estiver disponível, o recurso é alocado para o filósofo, ou seja, o semáforo está bloqueado. 
	
	printf("\n O filosofo %d esta na sala",filo);
	sem_wait(&garfo[filo]);
	sem_wait(&garfo[(filo+1)%5]);
	//aplicamos sem_wait em garfo, que são semáforos binários. 
	
	comer(filo);
	sleep(2);
	printf("\n O filosofo %d terminou de comer",filo);

	sem_post(&garfo[(filo+1)%5]);
	sem_post(&garfo[filo]);
	sem_post(&sala);
	/*
	estamos bloqueando os garfos à esquerda e à direita do filósofo. por exemplo, para o filósofo 0, estamos bloqueando os garfos 0 e 4.
	assim, permitindo que os filósofos comam.
	finalmente, sao liberados os semáforos chamando a função sem_post() para que as outras threads colocadas na fila possam usar os recursos. 
	*/
}

void comer(int filo)
{
	printf("\n O filosofo %d esta comendo",filo);
}
