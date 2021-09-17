// Bibliotecas padrão do C
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  // Inclui chamadas de sistema Posix

// Outras bibliotecas necessárias
#include <sys/types.h>
#include <sys/wait.h>


/*
    Esse programa cria um subprocesso que, por sua vez, cria outro subprocesso.
    Quando o processo Pai é eliminado, o processo Filho se torna filho do processo que gerencia o boot do SO (systemd).
    Atente para a nomenclatura utilizada:
        Nomes iniciados com letra maiúscula indicam posição absoluta (Avô, Pai, Filho)
        Nomes iniciados com letra minúscula indicam posição relativa (pai, filho)
*/

int main() {
    pid_t pid, pid2;

    pid = fork();

    if (pid < 0) { // Primeiro fork funcionou?
        perror("Erro: "); // Não
        exit(-1); // Encerra o processo original (Avô)
    } else
    if (pid > 0) { // Sou o processo pai (Avô)
        printf("CRIAÇÃO DOS PROCESSOS\n");
        sleep(1);
        printf("\tSou o Avô, processo %d\n", getpid());
        wait(0); // Espero o filho (Pai) terminar

    } else { // Sou o processo filho (Pai)

        pid2 = fork();

        if (pid2 < 0) { // Segundo fork funcionou?

            perror("Erro: "); // Não
            exit(-1); // Encerra o subprocesso (Pai)

        } else {

            if (pid2 > 0) { // Sou o processo pai (Pai)
                
                sleep(3);
                printf("\tEu sou o Pai, processo %d, filho de %d\n", getpid(), getppid());

                sleep(3); // Irá encerrar o pai (Pai) antes do sleep(4) do filho*

                printf("\tMatando o pai...\n");

                exit(0); // Encerra o pai

            } else { // Sou o processo filho (Filho)

                sleep(4);
                printf("\tSou o Filho, processo %d, filho de %d\n", getpid(), getppid());

                sleep(4); // *

                printf("\tSou o Filho, processo %d, meu novo pai é o processo %d\n", getpid(), getppid());

                exit(0);

            }
        }
    }
}