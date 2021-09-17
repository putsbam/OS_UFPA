#include <stdio.h>

#include <stdlib.h>

#include <time.h>

#include <pthread.h> // Biblioteca de criação de threads

#include <unistd.h>  // Inclui chamadas de sistema Posix

// Outras bibliotecas necessárias
#include <sys/types.h>

/*

 	O Barbeiro Dorminhoco
 	
 O problema do barbeiro dorminhoco é um problema clássico de comunicação inter-processo e sincronização entre múltiplos processos.

• Se nao ha clientes, o barbeiro adormece;
• Se a cadeira do barbeiro estiver livre, um cliente pode
ser atendido imediatamente;
• O cliente espera pelo barbeiro se houver uma cadeira de
espera vazia.
• Se nao tive onde sentar, o cliente vai embora...

*/

// MAX representa o número de cadeiras da sala de espera
#define MAX 3

// Variaveis de inicializaçao
// Utiliza-se MAX+1, pois deve-se levar em conta a cadeira do barbeiro
int begin = 0, end = 0, size = 0, fila[MAX + 1];

/*

Mutex: Mutual Exclusion Device

Serve para proteger o conteúdo de structures compartilhadas, que são modificadas constantemente. Ajuda a organizar e monitorar os processos.

"Um mutex é como uma chave de banheiro em um posto de gasolina, garantindo que apenas uma pessoa possa usar o banheiro de cada vez E que ninguém mais possa usar o banheiro até que o ocupante atual termine e a chave seja devolvida."

*/

pthread_mutex_t travaFila;

int vazio() { // function para retornar o a quantidade de cadeiras vazias
    return !size;
}

void enqueue(int cliente) { // function para colocar o cliente na fila, ou mandar ele embora (ultimo caso)

    if (size < MAX + 1) { // Caso hajam cadeiras disponiveis

        if (vazio()) // Caso esteja vazio (primeiro cliente)
            printf("O cliente %d acorda o barbeiro e senta em sua cadeira.\n", cliente);

        else // Caso a cadeira do barbeiro esteja ocupada, senta em uma cadeira de espera
            printf("O cliente %d senta em uma das cadeiras vagas da sala de espera.\n", cliente);

        fila[end] = cliente; // fila[0] = 1 | fila[1] = 2 ...
        end = (end + 1) % (MAX + 1); // end recebe o resto da divisao | end = (0+1) % (3+1) => end = 1 | esse valor vai passar na fila[end] a cada loop
        size++; // incrementa o size das cadeiras (cadeiras ocupadas)

    } else // Caso nao hajam cadeiras disponiveis
        printf("Todas as cadeiras estavam ocupadas, o cliente %d foi embora.\n", cliente);
}

int denqueue() { // function geral para remover (decrementar) processos da fila

    if (!vazio()) { // caso haja clientes

        /*
        
        "srand(time(NULL))" serve para prevenir repeticao de sequencias a cada run do programa
        
        Faz uso do relógio interno do computador para controlar a escolha do argumento. 
        Visto que o tempo está mudando continuamente, o argumento vai mudar para sempre.
        
        */

        srand(time(NULL));

        sleep(rand() % 4 + 1); // Intervalo de tempo que o barbeiro demora para cortar o cabelo do cliente (entre 1 4 segundos)
        printf("O barbeiro termina de cortar o cabelo do cliente %d, que vai embora.\n", fila[begin]);

        // após o barbeiro terminar de cortar o cabelo do cliente anterior, a fila segue

        int cliente = fila[begin]; // num do cliente | cliente = fila[0] | cliente = fila [1] ...

        begin = (begin + 1) % (MAX + 1); // begin recebe o resto da divisao | begin = (0+1) % (3+1) => begin = 1 | esse valor vai passar na fila[begin] a cada loop

        size--; // decrementa o numero de clientes (atendido, fila diminui)

        if (vazio()) // caso nao haja clientes esperando (vazio), o barbeiro dorme
            puts("Não há clientes para serem atendidos, o barbeiro vai dormir.");

        else // do contrario, segue o atendimento
            printf("O cliente %d senta na cadeira do barbeiro.\n", fila[begin]);

        return cliente; // retorna o valor do cliente

    } else
        // O barbeiro está dormindo, portanto nada ocorre e a função retorna -1 como código de erro
        return -1;
}

void * cliente(void * argumento) { // function para controle dos clientes

    unsigned long idCliente = * ((unsigned long * ) argumento);

    pthread_mutex_trylock( & travaFila);

    /*
    
    "pthread_mutex_trylock" tem a funcao de bloquear o mutex especificado (travaFila)
    mas sem suspender as threads caso esta ja esteja bloqueada (ocupada)
    Caso esteja desbloqueado, será bloqueado até o encerramento da thread.
    
    */

    enqueue(idCliente); // chama a function de colocar o cliente na fila, passando o id do mesmo como argumento

    /*
    
    "pthread_mutex_unlock" tem a funcao de desbloquear o mutex especificado (travaFila), assumindo que esteja bloqueado
    
    */

    pthread_mutex_unlock( & travaFila);

}

void * barbeiro(void * argumento) { // function para controle do barbeiro

    for (;;) { // loop infinito (condiçao sempre verdadeira)

        pthread_mutex_trylock( & travaFila);

        denqueue(); // chama a function de retirar o cliente da fila

        pthread_mutex_unlock( & travaFila);

    }

}

// Bloco principal (onde sao usadas as funcoes anteriores) c/ loop

int main() {

    // Passando NULL nas inicializaçoes/criaçoes de thread, esta será criada com os atributos-padrão

    pthread_mutex_init( & travaFila, NULL); // inicio do mutex 

    int i;

    pthread_t threadBarbeiro, threadCliente; // inicializacao das variaveis de thread

    pthread_create( & threadBarbeiro, NULL, barbeiro, NULL); // criacao da thread do barbeiro

    srand(time(NULL));

    for (i = 0;; ++i) { // loop infinito (sem condicao de parada)

        sleep(rand() % 4 + 1); //Intervalo de tempo para a chegada de clientes
        pthread_create( & threadCliente, NULL, cliente, & i); // continuamente criando threads de clientes

    }

    return 0; // fim da execucao
}