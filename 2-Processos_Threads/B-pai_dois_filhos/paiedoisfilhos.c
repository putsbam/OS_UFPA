//usando fork() para produzir um pai e dois filhos
//o pai termina depois de todos os processos;
//o primeiro filho termina antes do pai e depois do segundo filho;
//o segundo filho termina antes do primeiro filho.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/types.h>  
#include <sys/wait.h>
  
// Driver code
int main()
{
    int pid, pid1;
  
    // a variavel pid (parent id) armazena o valor retornado da chamada fork()
    
    pid = fork();
  
    // se fork() returnar zero entao isto significa que e' o processo filho:
    
    if (pid == 0) {
  
        // o primeiro filho devera ser impresso depois, portanto este processo
        // dormira por tres segundos:
        
        sleep(3);
        
  
        // este e o primeiro processo filho. 
        // getpid() dara' a ID do processo pai e getppid() deve retornar o ID do 
	    // processo pai do processo de chamada:
 
        printf("filho[1] --> pid = %d e ppid = %d\n",
               getpid(), getppid());
    }
  
    else {
        pid1 = fork();
        if (pid1 == 0) {
            sleep(2);
            printf("filho[2] --> pid = %d e ppid = %d\n",
                   getpid(), getppid());
        }
            // se o valor retornado de fork() for diferente de zero e maior que zero            	   
            // isto significa que este e' o processo pai
          
            else {
                // é solicitado para ser impresso e portanto colocado 
                // para dormir por tres segundos
                wait(0);
                sleep(3);
                printf("pai --> pid = %d\n", getpid());
            }
        
    }
  
    return 0;
}
