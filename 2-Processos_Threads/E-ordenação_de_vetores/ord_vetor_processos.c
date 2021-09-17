#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int *num, n, i, j, temp;
    pid_t pid, p;

    pid = getpid(); 
   /*Executando o processo pai*/
   printf("Coloque o tamanho do vetor: ");
   scanf("%d",&n);                                        //lê o tamanho do vetor.
   num = (int*)malloc(sizeof(int)*n);                     /*Aloca 'n' números inteiros, 'num' pode agora   
                                                          ser tratado como um vetor com 'n' posições:*/
   printf("Escreva os números pertencentes ao vetor:\n");

   for(i = 0 ; i < n ; i++) {                                   
   scanf("%d",&num[i]);  }                                //lê os números que fazem parte do vetor

   p = fork(); 
   if(p == 0 )                                            //avalia como verdadeiro
{ 
   /*Executando o processo filho */

   /*utilizando bubble sort para organizar o vetor de forma crescente.
   A posição atual é comparada com a próxima posição e se a posição atual 
   for menor que a posição seguinte então é feita a troca, caso contrário, 
   a troca não é feita e passa para o próximo par de comparação
   */                                             
   for(i = 0 ; i < n ; i++ ){             
   for(j = 0 ; j < n-i-1 ; j++){
   if(num[j] > num[j+1]) {
   temp = num[j];
   num[j] = num[j+1];    
   num[j+1] = temp;
} 
} 
}

   printf("\nO vetor organizado é:\n");
   for(i = 0 ; i < n ; i++){
   printf(" %d \n",num[i]); }                             //Mostra o vetor ordenado
}  
   return 0; 
} 

   
    

