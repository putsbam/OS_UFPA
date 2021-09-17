//Bibliotecas usadas:
#include <unistd.h>         //biblioteca que inclui chamadas de sistema Posix
#include <stdlib.h>         //biblioteca de propósito geral padrão da linguagem de programação C
#include <stdio.h>          //biblioteca de funções de entrada/saída
#include <pthread.h>        //biblioteca de criação de threads
#include <semaphore.h>      //biblioteca de criação de semáforos
#define READERS    20       //quantidade de leitores
#define WRITERS    3        //quantidade de escritores

/*    Leitor x Escritor
O problema dos leitores/escritores acontece em programação concorrente, um conjunto de processos ou threads acessam de forma concorrente uma área de memória comum, compartilhada, na qual podem ler ou escrever valores. As leituras podem ser feitas simultaneamente, já que não interferem umas com as outras, mas as escritas têm de ser feitas com acesso exclusivo da área compartilhada, para que dessa forma seja evitada condições de disputa.

Há diferentes abordagens para esse problema, pode-se , por exemplo, dar preferência ao escritor, que uma vez desejando acesso à memória compartilhada o escritor a obtém mesmo que processos leitores estivessem esperando antes. Outra abordagem seria dar preferência aos leitores, assim o escritor só obtem acesso à memória compartilhada quando todos os escritores liberarem o acesso, a solução a seguir da prioridade aos leitores.

Essa solução usa geração randômica de valores para simular os tempos que o escritor levará para pensar no que irá escrever e o tempo que demora escrevendo na base de dados, o consumidor terá valores randômicos para simular o tempo em que fica no banco de dados e o tempo em que fica processando as informações adquiridas.
*/

pthread_mutex_t db;         //exclusão mutúa para regiões críticas, controla o acesso ao banco de dados
pthread_mutex_t mutex;      //exclusão mutúa para regiões criíticas, controla o acesso a variável rc
int   rc;                   //quantidade de leitores lendo ou querendo ler a base de dados
//prototipos:
void read_data_base(void);
void use_data_read(void);
void think_up_data(void);
void write_data_base(void);


void reader() {                             //rotina da thread leitor:
while (1) {                                 // loop eterno 

      pthread_mutex_lock(&mutex);           //down(&mutex); garante acesso exclusivo a variavel rc
      rc=rc+1;                              //um novo leitor

      if(rc==1)  pthread_mutex_lock(&db);   //caso este seja o primeiro leitor
      pthread_mutex_unlock(&mutex);         //up(&mutex); libera o acesso a variavel rc

      read_data_base();                     //le a base de dados
      pthread_mutex_lock(&mutex);           //down(&mutex); garante acesso exclusivo a variavel rc
      rc=rc-1;                              //um leitor a menos

      if(rc==0) pthread_mutex_unlock(&db);  //caso este seja o ultimo leitor
      pthread_mutex_unlock(&mutex);         //up(&mutex); libera o acesso a variavel rc

      use_data_read();                      //utiliza as informações da base de dados
    }
}

void writer() {                     //rotina da thread escritor:

while(1)                            //loop eterno

    {
        think_up_data();            //pensa em informações para adicionar a base de dados
        pthread_mutex_lock(&db);    //down(&db); garante acesso exclusivo a base de dados
        write_data_base();          //escreve as informacoes novas na base de dados
        pthread_mutex_unlock(&db);  //up(&db); libera o acesso a base de dados
    }
}

void read_data_base(){             //para controle da leitura da base de dados

/*quanto tempo o leitor continuará lendo a base de dados*/
int readingtime;
readingtime = rand() % 3;          //readingtime pega número aleatorio entre 0 e 3
printf("Usuário lendo banco de dados. Total de %d leitores lendo agora.\n",rc);
sleep(readingtime);                //utiliza número aleatório gerado em readingtime anteriormente para definir os segundos do sleep
}


void use_data_read(){               //para controle de informações dos dados 

/*quanto tempo o leitor continuará utilizando os dados lidos*/
int usetime;
usetime = rand() % 20;             //usetime pega número aleatorio entre 0 e 20
printf("Usuário utilizando conhecimento adquirido no banco de dados\n");
sleep(usetime);                    //utiliza número aleatório gerado em usetime anteriormente para definir os segundos do sleep
}


void think_up_data(){                //para controle de pensamento de info adicionadas a base de dados

/*quanto tempo o escritor utiliza pensando no que irá escrever*/
int thinktime;
thinktime = rand() % 10;             //thinkingtime pega número aleatorio entre 0 e 10
printf("Escritor pensando no que irá escrever\n");
sleep(thinktime);                    //utiliza número aleatório gerado em thinktime anteriormente para definir os segundos do sleep
}


void write_data_base(){              //para controle da escritura dos dados

/*quanto tempo o escritor utiliza escrevendo na base de dados*/
int writetime;
writetime = rand() % 6;             //writetime pega número aleatorio entre 0 e 6
printf("Escritor escrevendo no banco de dados\n");
sleep(writetime);                   //utiliza número aleatório gerado em writetime anteriormente para definir os segundos do sleep
}




int main(){                                               //Função main 

pthread_t writerthreads[WRITERS], readerthreads[READERS]; //criando writerthreads[WRITERS], readerthreads[READERS] do tipo thread
int i;

//inicializando os semáforos:
    pthread_mutex_init(&db, NULL);
    pthread_mutex_init(&mutex, NULL);



    for(i=0;i<WRITERS;i++){
    pthread_create( &writerthreads[i], NULL,(void *) writer, NULL); //criando as threads independentes de escritores
}


    for(i=0;i<READERS;i++){
    pthread_create( &readerthreads[i], NULL,(void *) reader, NULL); //criando as threads independentes de leitores
}

    for(i=0;i<WRITERS;i++){
    pthread_join(writerthreads[i], NULL);    //espera as threads de escritores terminar
}

    for(i=0;i<READERS;i++){
    pthread_join(readerthreads[i], NULL);   //espera as threads de leitores terminar
}


exit(0);
}

