#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>  

void* thread1() {  //função a ser executada quando a thread 1 for criada
	printf("A"); 
	}

void* thread2() {  //função a ser executada quando a thread 2 for criada
	printf("B"); 
	}

void* thread3() {  //função a ser executada quando a thread 3 for criada
	printf("C\n"); 
	}
 
int main() { 
	pthread_t t1; //criando t1 do tipo thread
	pthread_create(&t1,NULL,&thread1,NULL);
	/*criando thread 1, o primeiro parâmetro aponta para t1, o segundo refere-se a customizações
	que podem ser feitas com as threads, nesse caso será NULL utilizando o que vem por padrão,
	o terceiro parâmetro aponta para a função que irá ser executada,no caso, thread1 
	e o último é o argumento usado na função como não utilizamos (o () do thread 1 está vazio) então será NULL */
	
	pthread_join(t1,NULL);  /* espera a thread 1 terminar, 
	o primeiro parâmetro é de identificação da thread, no caso, t1
	o segundo argumento se não for NULL conterá valor de retorno da thread*/
	
	pthread_t t2; //criando t2 do tipo thread
	pthread_create(&t2,NULL,&thread2,NULL);//criando thread 2
	pthread_join(t2,NULL);  // espera a thread 2 terminar 
	
	pthread_t t3;//criando t3 do tipo thread
	pthread_create(&t3,NULL,&thread3,NULL);//criando thread 3    
        pthread_join(t3,NULL);  // espera a thread 3 terminar
        
	return 0; 
}