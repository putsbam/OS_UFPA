// Bibliotecas padrão do C
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  // Inclui chamadas de sistema Posix

// Outras bibliotecas necessárias
#include <sys/types.h>
#include <sys/wait.h>

/*
    Este programa lê uma entrada do usuário (sendo esta um inteiro "n");
    Após isso, cria "n" processos e threads.
*/

int main() {

    int n, counter;
    char term;
    pid_t pid;

    printf("\tDigite o número de filhos (inteiro) que deseja criar:\n");

    int scanned = scanf("%d%c", & n, & term); // Valor do scanf para determinar se o input é inteiro

    if (scanned != 2 || term != '\n') { // Caso não seja inteiro

        printf("\tApenas inteiros!\n");

        return 0; // Retorna

    } else { // Caso seja inteiro (válido) continua-se

        printf("\t=== %d FILHOS (PROCESSOS) SERAO CRIADOS ===\n", n);

        sleep(2);

        for (counter = 1; counter <= n; counter++) { // Loop for (valor_inicio; condicao_de_parada; incremento)
        
        // Contador (counter) começa em 1 e para quando igual a "n", enquanto não for, incrementa + 1 a si mesmo
        // Tudo dentro do loop será executado até o contador (counter) ser <= a "n"

            pid = fork();

            if (pid < 0) { // Lidar com possíveis erros (pid < 0), o output mostrará o erro

                perror("Erro: ");

                exit(-1);

            } else { // Caso não tenha nenhum erro, o output mostrará o "counter" e "PID" 

                printf("\t[%d] Sou o processo: %d\n", counter, getpid());
                sleep(2);

            }

        }

        return 0; // fim da execução
    }
}