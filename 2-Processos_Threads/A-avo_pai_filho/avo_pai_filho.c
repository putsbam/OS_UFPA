// Bibliotecas padrão do C
#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>  // Inclui chamadas de sistema Posix

// Outras bibliotecas necessárias
#include <sys/types.h>  
#include <sys/wait.h>


/*
    Esse programa cria um subprocesso que, por sua vez, cria outro subprocesso.
    Atente para a nomenclatura utilizada:
        Nomes iniciados com letra maiúscula indicam posição absoluta (Avô, Pai, Filho)
        Nomes iniciados com letra minúscula indicam posição relativa (pai, filho)
*/

int main() {
    pid_t pid, pid2;    


    pid = fork();

    if (pid < 0) {                                          // Primeiro fork funcionou?
        perror ("Erro: ");                                  // Não
        exit (-1);                                          // Encerra o processo original (Avô)
    }
    else
        if (pid > 0) {                                      // Sou o processo pai (Avô)?
            printf("CRIAÇÃO DOS PROCESSOS\n");
            sleep(1);
            printf("\tSou o Avô\n");                        // Sim
            wait(0);                                        // Espero o filho (Pai) concluir

            sleep(1);

            printf("\tAvô tá indo...\n");
            exit(0);                                        // Encerra o Avô
        }
        else {                                              // Sou o processo filho (Pai)
            pid2 = fork();
            
            if (pid2 < 0) {                                 // Segundo fork funcionou?
            perror ("Erro: ");                              // Não
            exit (-1);                                      // Encerra o subprocesso (Pai)
            }
            else {
                if (pid2 > 0) {                             // Sou o processo pai (Pai)?
                    sleep(2);
                    printf("\tSou o Pai\n");                // Sim
                    wait(0);                                // Espero o filho (Filho) concluir
                    
                    sleep(1);

                    printf("\tPai tá indo...\n");
                    exit(0);                                // Encerra o pai
                }
                else {                                      // Sou o processo filho (Filho)
                    sleep(3);
                    printf("\tSou o Filho\n");
                    
                    sleep(1);
                    printf("\nAguarde a execução...\n");

                    sleep(3);

                    printf("\nFINALIZAÇÃO DOS PROCESSOS\n");
                    sleep(1);
                    printf("\tFilho tá indo...\n");
                    exit(0);                                // Encerra o Filho
                }
            }
        }
}
