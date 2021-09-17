/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/
// programa C para encontrar o número máximo de threads dentro
// um processo 

#include<stdio.h>
#include<pthread.h>

void *thread (void *vargp){     }
  
int main()
{
    int err = 0, count = 0;
    pthread_t tid;
    //thread id
      
    while (err == 0)
    {
        err = pthread_create (&tid, NULL, thread, NULL);
        count++;
    }
    // em caso de sucesso, pthread_create retorna 0 e
     // em erro, ele retorna o número do erro
     // Então, o loop while é iterado até que o valor de retorno seja 0 
     
    printf("O numero maximo de threads dentro do processo e : %d\n", count);
    
    return 0;
}