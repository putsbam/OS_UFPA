#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>  // Biblioteca POSIX para uso de threads


/*
    Este programa calcula a soma entre a área de um triângulo e de um retângulo.    
    Para isso, o usuário passa as medidas de base e altura das figuras como argumentos.
    Então, o programa cria duas threads.
    Uma delas calcula a área do triângulo; outra, a área do retângulo.
    Por fim, a soma dessas duas áreas é impressa na tela.
*/

float areaT = 0;  // Área do triângulo (global)
float areaR = 0;  // Área do retângulo (global)

// Cabeçalhos das rotinas das threads
void * calcula_areaT(void *arg);
void * calcula_areaR(void *arg);


int main(int argc, char *argv[]) {
    

    pthread_t thread_tri, thread_ret;  // Cria os identificadores para as threads

    float tri[2] = {atof(argv[1]), atof(argv[2])};  // Guarda as medidas do triângulo em um vetor
    float ret[2] = {atof(argv[3]), atof(argv[4])};  // Guarda as medidas do retângulo em um vetor
    
    int rstatus;

    
    // int pthread_create (*identificador, *atributo, rotina, void *argumento)
    // caso dê certo, retorna 0
    rstatus = pthread_create(&thread_tri, NULL, calcula_areaT, (void*) tri);  // Cria PRIMEIRA thread (tri)

    if (rstatus != 0) {                                         // Deu certo?
        printf("Erro ao tentar criar a thread_tri\n");          // Não!
        exit(EXIT_FAILURE);                                     // Encerra o programa
    }

    //printf("Thread_tri criada com sucesso\n");                  // Tudo certo!
    

    rstatus = pthread_create(&thread_ret, NULL, calcula_areaR, (void*) ret);  // Cria SEGUNDA thread (ret)

    if (rstatus != 0) {                                         // Deu certo?
        printf("Erro ao tentar criar a thread_ret\n");          // Não!
        exit(EXIT_FAILURE);                                     // Encerra o programa
    }

    //printf("Thread_ret criada com sucesso\n");                  // Tudo certo!



    rstatus = pthread_join(thread_tri, NULL);                   // Aguardar finalização da PRIMEIRA thread (tri)

    if (rstatus != 0) {                                         // Deu certo?
        printf("Erro ao aguardar finalização da thread_tri\n"); // Não!
        exit(EXIT_FAILURE);                                     // Encerra o programa
    }

    //printf("Thread_tri finalizada com sucesso!\n");             // Tudo certo!


    rstatus = pthread_join(thread_ret, NULL);                   // Aguardar finalização da SEGUNDA thread (ret)

    if (rstatus != 0) {                                         // Deu certo?
        printf("Erro ao aguardar finalização da thread_ret\n"); // Não!
        exit(EXIT_FAILURE);                                     // Encerra o programa
    }

    //printf("Thread_ret finalizada com sucesso!\n");             // Tudo certo!



    // Resultados
    printf("\n*Resultados*\n");
    printf("\tÁrea do triângulo: %.2fm²\n",areaT);
    printf("\tÁrea do retângulo: %.2fm²\n",areaR);
    printf("\tSoma das áreas: %.2fm²\n", (areaT + areaR));

    return 0;

}


// Rotina da thread 1
// Calcula a área do triângulo
void * calcula_areaT(void *arg) {

    float *tam;
    tam = (float*) arg;             // Resgata o tipo original do ponteiro
    areaT = (tam[0] * tam[1])/2;    // areaT recebe (base * altura / 2)

    pthread_exit(arg);              // Finaliza a PRIMEIRA thread

}


// Rotina da thread 2
// Calcula a área do retângulo
void * calcula_areaR(void *arg) {

    float *tam;
    tam = (float*) arg;       // Resgata o tipo original do ponteiro
    areaR = tam[0] * tam[1];  // areaR recebe (base * altura)

    pthread_exit(arg);

}
