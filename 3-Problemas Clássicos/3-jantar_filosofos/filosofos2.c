/*
Codigo em C criado por ANUSHKA DESHPANDE
para o problema cl�ssico "O Jantar dos filosofos"
*/
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>

sem_t sala;
sem_t garfo[5];
/*Aqui, o sem�foro sala � um sem�foro de contagem, pois h� uma sala de jantar que pode acomodar 4 fil�sofos. 
ou seja, considere que h� 4 cadeiras na sala e esse � o recurso. 
Portanto, h� v�rias inst�ncias do recurso na sala. Portanto, sala � um sem�foro de contagem. */

void * filosofo(void *);
void comer(int);
int main()
{
	int i,a[5];
	pthread_t tid[5];
	/*Essas threads referem-se a 5 fil�sofos sentados ao redor da mesa. Os temos como threads porque queremos que 
	sejam executados simultaneamente, isto �, que v�rios fil�sofos comam ao mesmo tempo.*/
	
	sem_init(&sala,0,4);
	//A fun��o sem_init () � usada para inicializar o sem�foro. 
	
	/*O primeiro par�metro � o ponteiro para o sem�foro declarado.

     O segundo par�metro � pshared. Se for zero, o sem�foro � compartilhado entre os encadeamentos; 
	 caso contr�rio, � compartilhado entre os processos. Em nosso caso, � zero, o que significa que � compartilhado entre threads.

     O terceiro valor do par�metro � o valor com o qual o sem�foro � inicializado. 
	 Aqui, o sem�foro sala  � inicializada como 4, o que significa que variar� entre 0�3 e ter� 4 valores.*/
     
	for(i=0;i<5;i++)
		sem_init(&garfo[i],0,1);
	/* como existem 5 garfos, criamos 5 sem�foros bin�rios referentes aos cinco garfos de4 0 a 4. */	
	for(i=0;i<5;i++){
		a[i]=i;
		pthread_create(&tid[i],NULL,filosofo,(void *)&a[i]);
	} 
	for(i=0;i<5;i++)
		pthread_join(tid[i],NULL);
}   /* poder� haver a situa��o em que todos os 5 threads come�am a ser executados, ou seja, todos os 5 fil�sofos entram na sala e causam deadlock. 
      Portanto, estamos permitindo que 4 fil�sofos entrem na sala primeiro para que pelo menos um deles possa terminar de comer. */

void * filosofo(void * num)
//Estamos chamando a fun��o a partir de pthread_create (linha 42) e passando a ela o endere�o de uma vari�vel inteira que se refere ao n�mero do fil�sofo. 
{
	int filo=*(int *)num;

	sem_wait(&sala);
	//Em seguida, chamamos a fun��o sem_wait que primeiro verifica se o recurso est� dispon�vel e, 
	//se estiver dispon�vel, o recurso � alocado para o fil�sofo, ou seja, o sem�foro est� bloqueado. 
	
	printf("\n O filosofo %d esta na sala",filo);
	sem_wait(&garfo[filo]);
	sem_wait(&garfo[(filo+1)%5]);
	//aplicamos sem_wait em garfo, que s�o sem�foros bin�rios. 
	
	comer(filo);
	sleep(2);
	printf("\n O filosofo %d terminou de comer",filo);

	sem_post(&garfo[(filo+1)%5]);
	sem_post(&garfo[filo]);
	sem_post(&sala);
	/*
	estamos bloqueando os garfos � esquerda e � direita do fil�sofo. por exemplo, para o fil�sofo 0, estamos bloqueando os garfos 0 e 4.
	assim, permitindo que os fil�sofos comam.
	finalmente, sao liberados os sem�foros chamando a fun��o sem_post() para que as outras threads colocadas na fila possam usar os recursos. 
	*/
}

void comer(int filo)
{
	printf("\n O filosofo %d esta comendo",filo);
}
