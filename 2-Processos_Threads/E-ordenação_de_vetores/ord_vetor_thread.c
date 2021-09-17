#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

/*declarando as variaveis globais do vetor e tamanho*/
int *vprimario;
int tam;


typedef struct vetor_struct {                             //estrutura para passar argumentos para a função da thread
    int *vetor_ord_1;
    int *vetor_ord_2;
} vetorStruct;

/*Faz a ordenação da primeira metade do vetor*/
void *ord_1(void *args)
{
    vetorStruct *pVetorStruct = args;

    int tam1 = tam/2;
    int temp;

/*aplicando o bubble sort para ordenar o vetor*/
    for (int i = 0; i < tam1 - 1; ++i) {
    for (int j = 0; j < tam1 -i -1; ++j) {           
    if (pVetorStruct->vetor_ord_1[j] > pVetorStruct->vetor_ord_1[j + 1]){
       temp = pVetorStruct->vetor_ord_1[j];
       pVetorStruct->vetor_ord_1[j] = pVetorStruct->vetor_ord_1[j + 1];
       pVetorStruct->vetor_ord_1[j + 1] = temp;
}
}
}
    return NULL;
}

/*Faz a ordenação da segunda metade do vetor*/
void *ord_2(void *args)
{
    vetorStruct *vetorPrimarioStruct = args;
    int tam2 = tam - (tam/2);
    int temp;

/*aplicando o bubble sort para ordenar o vetor*/
    for (int i = 0; i < tam2 - 1; ++i) {
    for (int j = 0; j < tam2 -i -1; ++j) {
    if (vetorPrimarioStruct->vetor_ord_2[j] > vetorPrimarioStruct->vetor_ord_2[j + 1]){
         temp = vetorPrimarioStruct->vetor_ord_2[j];
         vetorPrimarioStruct->vetor_ord_2[j] = vetorPrimarioStruct->vetor_ord_2[j + 1];
         vetorPrimarioStruct->vetor_ord_2[j + 1] = temp;
}
}
}
    return NULL;
}

/*função merge para juntar e ordenar os vetores já ordenados*/
void *merge(void *args)
{
    vetorStruct *pVetorStruct = args;
    int tam1 = tam/2;
    int tam2 = tam - tam1;
    int i=0, j=0, k=0;

while (i<tam1 && j <tam2) {
        
    if (pVetorStruct->vetor_ord_1[i] < pVetorStruct->vetor_ord_2[j])       //se o ord_vetor_1 for menor que vetor_ord_2,
    vprimario[k++] = pVetorStruct->vetor_ord_1[i++];                       //coloca o elemento vetor 1 em vprimario        
     
    else                                                                   //Senão, coloca o elemento vetor_ord_2 em vprimario
    vprimario[k++] = pVetorStruct->vetor_ord_2[j++];
}
    
while (i < tam1)
    vprimario[k++] = pVetorStruct->vetor_ord_1[i++];                        //Armazena os elementos restantes de vetor_ord_1 
   
while (j < tam2)
    vprimario[k++] = pVetorStruct->vetor_ord_2[j++];                         //Armazena os elementos restantes de vetor_ord_2
    
    return NULL;
}

int main()
{
    pthread_t ord_thread_1;                                                //criando ord_thread_1 do tipo thread
    pthread_t ord_thread_2;                                                //criando ord_thread_2 do tipo thread
    pthread_t  merging_thread;                                             //criando merging_thread do tipo thread
    vetorStruct args;

    printf("Digite o tamanho do vetor\n");      
    scanf("%d",&tam);                                                       //lê o tamanho do vetor
    vprimario = (int *)malloc(tam * sizeof(int));
    args.vetor_ord_1 = (int *)malloc((tam/2) * sizeof(int));
    args.vetor_ord_2 = (int *)malloc((tam - (tam/2)) * sizeof(int));

    printf("Informe os elementos pertencentes ao vetor: \n");
for (int i = 0; i < tam; ++i) {
    scanf("%d",&vprimario[i]);                                            //lê os números pertencentes ao vetor
}
   
for (int j = 0; j < tam/2; ++j) {
    args.vetor_ord_1[j] = vprimario[j];                                  //passando a primeira metade do vprimario para vetor_ord_1
}

for (int k = 0; k < tam - (tam/2); ++k) {
    args.vetor_ord_2[k] = vprimario[k + (tam / 2)];                       //passando a segunda metade do vprimario para vetor_ord_2
}

    pthread_create(&ord_thread_1, NULL, &ord_1, (void *)&args);            //cria ord_thread_1 e passa o vetor
    pthread_create(&ord_thread_2, NULL, &ord_2, (void *)&args);            //cria ord_thread_2 e passa o vetor
    
    pthread_join(ord_thread_1, NULL);                                       //espera ord_thread_1 terminar
    pthread_join(ord_thread_2, NULL);                                       //espera ord_thread_2 terminar

    pthread_create(&merging_thread, NULL, &merge, (void *)&args);           //cria merging thread e passa os dois vetores ordenados
    pthread_join(merging_thread,NULL);                                      //espera merging_thread terminar

    printf("\nO vetor ordenado é: ");
for (int l = 0; l < tam; ++l) {
    printf("%d ",vprimario[l]);                                             //imprime o vPrimario
}
    printf("\n");
}
