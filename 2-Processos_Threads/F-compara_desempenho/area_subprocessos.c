// Bibliotecas padrão do C
#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>  // Inclui chamadas de sistema Posix

// Outras bibliotecas necessárias
#include <sys/types.h>  
#include <sys/wait.h>


/*
    Este programa calcula a soma entre a área de um triângulo e de um retângulo.    
    Para isso, o usuário passa as medidas de base e altura das figuras como argumentos.
    Então, o programa cria um subprocesso,
    que calcula as áreas do triângulo e do retângulo.
    Por fim, a soma dessas duas áreas é impressa na tela.
*/


int main(int argc, char *argv[]) {
    
    pid_t pid;                                              // Variável que receberá a informação de PID
    
    pid = fork();                                           // Cria subprocesso

    if (pid < 0) {                                          // Fork funcionou?
        perror ("Erro: ");                                  // Não
        exit (-1);                                          // Encerra o processo original
    }
    else
        if (pid > 0) {                                      // Sou o processo pai

            wait(NULL);                                     // Espero o filho concluir
            exit(0);                                        // Encerra o Pai

        }
        else {                                              // Sou o processo filho

            float tri[2] = {atof(argv[1]), atof(argv[2])};  // Guarda as medidas do triângulo em um vetor
            float ret[2] = {atof(argv[3]), atof(argv[4])};  // Guarda as medidas do retângulo em um vetor

            float areaT = 0;                                // Área do triângulo
            float areaR = 0;                                // Área do retângulo

            areaT = (tri[0] * tri[1])/2;                    // areaT recebe (base * altura / 2)
            areaR = ret[0] * ret[1];                        // areaR recebe (base * altura)

            // Resultados
            printf("\n*Resultados*\n");
            printf("\tÁrea do triângulo: %.2fm²\n",areaT);
            printf("\tÁrea do retângulo: %.2fm²\n",areaR);
            printf("\tSoma das áreas: %.2fm²\n", (areaT + areaR));
            
            exit(0);                                        // Encerra o filho

        }

}
