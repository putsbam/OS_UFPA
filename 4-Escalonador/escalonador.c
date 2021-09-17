/*
Este programa simula um escalonador de tarefas de um sistema operacional fictício.
Os algoritmos de escalonamento implementados são:
    FCFS (ou FIFO), Shortest Job First, Sorteio e Round Robin.

Obs.:
O programa considera que todas as tarefas estão na fila de prontas desde o tempo inicial.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define SIZE 10     // Quantidade máxima de processos simultâneos
#define ALG 4       // Quantidade de algoritmos de escalonamento
#define QUANTUM 3   // Tamanho do quantum = 3s

int espera[ALG], vida[ALG];  // Guarda tempos médios de espera e de vida para cada escalonador
char algoritmos[4][11] = {"FCFS    ", "SJF    ", "Sorteio", "Round-Robin"};  // Guarda os nomes de cada escalonador

// Definição da Fila Circular (simplificada)
    typedef struct {
        int items[SIZE];
        int front, rear;
    } fila_circular;

    
    void criafila(fila_circular *RR) {
            RR->front = RR->rear = -1;
        }

    // Verifica se a fila está cheia
    int isFull(fila_circular *RR) {
        if ((RR->front == RR->rear + 1) || (RR->front == 0 && RR->rear == SIZE - 1))
            return 1;
        return 0;
    }

    // Adiciona elemento ao fim da fila
    void enQueue(fila_circular *RR, int element) {
        if (isFull(RR))
            printf("\n Queue is full!! \n");
        else {
            if (RR->front == -1) RR->front = 0;
            RR->rear = (RR->rear + 1) % SIZE;
            RR->items[RR->rear] = element;
        }
    }



// Algoritmos para First Come, First Served (FCFS)
    // Calcula o Tempo de Espera para todos os processos
    void waitingtimeFCFS(int processes[], int n, int bt[], int wt[])
    { 
        // o tempo de espera para o primeiro processo é sempre nulo
        wt[0] = 0; 
        
        for (int i = 1; i < n; i++) 
            wt[i] = bt[i-1] + wt[i-1];
    }
            
	
    // Calcula o Tempo de Vida para todos os processos
    void lifetimeFCFS(int processes[], int n, int bt[], int wt[], int tat[]) 
    { 
	    for (int i = 0; i < n ; i++)
		    tat[i] = bt[i] + wt[i];
    }

    // Calcula as médias de execução FCFS
    void mediaFCFS(int processes[], int n, int bt[]) 
    { 
	    int wt[n], tat[n], total_wt, total_tat;
        total_wt = total_tat = 0;
	    waitingtimeFCFS(processes, n, bt, wt);
	    lifetimeFCFS(processes, n, bt, wt, tat);

	    // Exite os detalhes de cada processo
        printf("\n\nFIRST COME, FIRST SERVED");
	    printf("\nProcessos | Tempo de Proc. | Tempo de Espera | Tempo de Vida\n");
	    
	    // Calcula os tempos totais de espera e de vida
	    for (int i=0; i<n; i++) 
	    { 
		    total_wt = total_wt + wt[i]; 
		    total_tat = total_tat + tat[i]; 
		    printf(" %d ",(i+1)); 
		    printf("\t\t%d ", bt[i]); 
		    printf("\t\t%d ",wt[i]); 
		    printf("\t\t%d\n",tat[i]);
	    }

	    espera[0] = (float)total_wt / (float)n; 
	    vida[0] = (float)total_tat / (float)n; 
	    printf("Tempo médio de espera = %d",espera[0]); 
	    printf("\n"); 
	    printf("Tempo médio de vida = %d \n",vida[0]);
    }


// Algoritmos para Shortest Job First (SJF)

    // Ordena vetor em ordem crescente
    void quick_sort (int *a, int n) {
    int i, j, p, t;
    if (n < 2)
        return;
    p = a[n / 2];
    for (i = 0, j = n - 1;; i++, j--) {
        while (a[i] < p)
            i++;
        while (p < a[j])
            j--;
        if (i >= j)
            break;
        t = a[i];
        a[i] = a[j];
        a[j] = t;
    }
    quick_sort(a, i);
    quick_sort(a + i, n - i);
}

    // Calcula o Tempo de Espera para todos os processos
    void waitingtimeSJF(int processes[], int n, int bt[], int wt[])
    { 
        quick_sort(bt, n);  // Ordena o vetor em ordem crescente
        
        wt[0] = 0;
        
        for (int i = 1; i < n; i++) {
            wt[i] = bt[i-1] + wt[i-1];
        }
    }
            
	
    // Calcula o Tempo de Vida para todos os processos
    void lifetimeSJF(int processes[], int n, int bt[], int wt[], int tat[]) 
    { 
	    for (int i = 0; i < n ; i++)
		    tat[i] = bt[i] + wt[i];
    }

    // Calcula as médias de execução SJF
    void mediaSJF(int processes[], int n, int bt[]) 
    { 
	    int wt[n], tat[n], total_wt, total_tat;
        total_wt = total_tat = 0;
	    waitingtimeSJF(processes, n, bt, wt);
	    lifetimeSJF(processes, n, bt, wt, tat);

	    // Exite os detalhes de cada processo
        printf("\n\nSHORTEST JOB FIRST");
	    printf("\nProcessos | Tempo de Proc. | Tempo de Espera | Tempo de Vida\n");
	    
	    // Calcula os tempos totais de espera e de vida
	    for (int i=0; i<n; i++) 
	    { 
		    total_wt = total_wt + wt[i]; 
		    total_tat = total_tat + tat[i]; 
		    printf(" %d ",(i+1)); 
		    printf("\t\t%d ", bt[i]); 
		    printf("\t\t%d ",wt[i]); 
		    printf("\t\t%d\n",tat[i]);
	    }

	    espera[1] = (float)total_wt / (float)n; 
	    vida[1] = (float)total_tat / (float)n;  
	    printf("Tempo médio de espera = %d",espera[1]); 
	    printf("\n"); 
	    printf("Tempo médio de vida = %d \n",vida[1]); 
    }


// Algoritmos para Sorteio
    // Gera vetor de números aleatórios
    void sorteio(int array[], int n, int range, int type) {
        int x, p;
        int i=0;

        srand(time(NULL));

        // Gera 10 números aleatórios no intervalo [0,9]
        while(i < 10){
            int r=rand()%range + type;

            for (x = 0; x < i; x++) 
                if(array[x]==r)
                    break;
            
            if(x==i)
                array[i++]=r;
        }        
    }

    // Calcula o Tempo de Espera para todos os processos
    void waitingtimeSorteio(int processes[], int n, int bt[], int wt[], int bilhetes[])
    { 
        
        // Copia vetor
        for (int i = 0; i < n; i++) 
            bilhetes[i] = processes[i];
        
        sorteio(bilhetes, n, 10, 0);
        wt[bilhetes[0]] = 0;
        for (int i = 1; i < n; i++) {
            wt[bilhetes[i]] = bt[bilhetes[i-1]] + wt[bilhetes[i-1]];
        }
    }
            
	
    // Calcula o Tempo de Vida para todos os processos
    void lifetimeSorteio(int processes[], int n, int bt[], int wt[], int tat[]) 
    { 
	    for (int i = 0; i < n ; i++)
		    tat[i] = bt[i] + wt[i];
    }

    // Calcula as médias de execução Sorteio
    void mediaSorteio(int processes[], int n, int bt[]) 
    { 
	    int wt[n], tat[n], total_wt, total_tat, bilhetes[n];
        total_wt = total_tat = 0;
	    waitingtimeSorteio(processes, n, bt, wt, bilhetes);
	    lifetimeSorteio(processes, n, bt, wt, tat);

	    // Exite os detalhes de cada processo
        printf("\n\nSORTEIO");
        printf("\nResultado do sorteio: [ ");
        for (int i = 0; i < n; i++)
            printf("%d ", bilhetes[i] + 1);
        printf("]");
	    printf("\nProcessos | Tempo de Proc. | Tempo de Espera | Tempo de Vida\n");
	    
	    // Calcula os tempos totais de espera e de vida
	    for (int i=0; i<n; i++) 
	    { 
		    total_wt = total_wt + wt[i]; 
		    total_tat = total_tat + tat[i]; 
		    printf(" %d ",(i+1)); 
		    printf("\t\t%d ", bt[i]); 
		    printf("\t\t%d ",wt[i]); 
		    printf("\t\t%d\n",tat[i]);
	    }

	    espera[2] = (float)total_wt / (float)n; 
	    vida[2] = (float)total_tat / (float)n; 
	    printf("Tempo médio de espera = %d",espera[2]); 
	    printf("\n"); 
	    printf("Tempo médio de vida = %d \n",vida[2]); 
    }


// Algoritmos para Round Robin (RR)
    // Calcula o tempo de espera para todos os processos
        void waitingtimeRR(fila_circular *processes, int n, fila_circular *bt, int wt[], int quantum) {
            fila_circular rt = *bt;     // Tempo Restante
            int tp = 0;                 // Tempo total de execução
            int X = 0;
            int i;

            while (X < SIZE)                                // Enquanto X menor que 10
                for (i = 0; i < SIZE; i++) {                
                    if (rt.items[i] > quantum) {            // O processo "i" levará MAIS do que 1 quantum para finalizar
                        tp += quantum;                          // O tempo total de execução aumenta em 1 quantum
                        rt.items[i] -= quantum;                 // O tempo restante de "i" diminui em 1 quantum
                    }
                    else {                                  // O processo "i" levará MENOS do que 1 quantum para finalizar
                        if (rt.items[i] >= 0) {                 // Se este processo ainda não foi encerrado, faça:
                            tp += rt.items[i];                      // O tempo restante de "i" é acrescentado ao tempo total de execução
                            rt.items[i] = -1;                       // Indica que o processo "i" já encerrou
                            wt[i] = tp - bt->items[i];              // *Cálculo do tempo de espera de "i"*
                            X++;                                    // X é incrementado a cada processo que encerra
                        }
                    }
                }
        }

// Calcula o tempo de vida para todos os processos
    void lifetimeRR(fila_circular *processes, int n, fila_circular *bt, int wt[], int tat[]) 
    {
	    for (int i = 0; i < n ; i++)
		    tat[i] = bt->items[i] + wt[i];
    }
                
// Calcula as médias de execução RR
    void mediaRR(fila_circular *processes, int n, fila_circular *bt, int quantum) 
    { 
	    int wt[n], tat[n], total_wt, total_tat;
        total_wt = total_tat = 0;

	    waitingtimeRR(processes, n, bt, wt, quantum); 
	    lifetimeRR(processes, n, bt, wt, tat);

	    // Exite os detalhes de cada processo
        printf("\n\nROUND ROBIN");
	    printf("\nProcessos | Tempo de Proc. | Tempo de Espera | Tempo de Vida\n");
	    
	    // Calculate total waiting time and total turn around time 
	    for (int i=0; i<n; i++) 
	    { 
		    total_wt = total_wt + wt[i]; 
		    total_tat = total_tat + tat[i];
		    printf(" %d ",(i+1)); 
		    printf("\t\t%d ", bt->items[i]); 
		    printf("\t\t%d ",wt[i]); 
		    printf("\t\t%d\n",tat[i]); 
	    }

	    espera[3] = (float)total_wt / (float)n; 
	    vida[3] = (float)total_tat / (float)n;  
	    printf("Tempo médio de espera = %d",espera[3]); 
	    printf("\n"); 
	    printf("Tempo médio de vida = %d \n",vida[3]); 
    }


int main() 
{
	int processes[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};  // Index dos processos
    int burst_time[10];                                 // Guarda os tempos de execução
    
    
    sorteio(burst_time, SIZE, 20, 1); 


    fila_circular processesRR, burst_timeRR;
    criafila(&processesRR);
    criafila(&burst_timeRR);
    
    for (int i = 0; i < SIZE; i++)
        enQueue(&processesRR, processes[i]);

    for (int i = 0; i < SIZE; i++)
        enQueue(&burst_timeRR, burst_time[i]);

    printf("***FAKE OPERATING SYSTEM***\n");
    
    int x;  // Controla o laço
    do {
        printf("\nTempo de execução das tarefas na fila: [ ");
        for (int i = 0; i < SIZE; i++)
            printf("%d ", burst_time[i]);
        printf("]\n");
        
        printf("\nEscolha seu escalonador de tarefas\n");
        printf("\t1 - FIFO\n\t2 - SJF\n\t3 - Sorteio\n\t4 - Round-Robin\n\t5 - Todos\n");
    
        scanf("%d",&x);

        switch (x)
        {
        case 1:
            mediaFCFS(processes, SIZE, burst_time);
            break;
        case 2:
            mediaSJF(processes, SIZE, burst_time);
            break;
        case 3:
            mediaSorteio(processes, SIZE, burst_time);
            break;
        case 4:
            mediaRR(&processesRR, SIZE, &burst_timeRR, QUANTUM);
            break;
        case 5:
            mediaFCFS(processes, SIZE, burst_time);
            mediaSJF(processes, SIZE, burst_time);
            mediaSorteio(processes, SIZE, burst_time);
            mediaRR(&processesRR, SIZE, &burst_timeRR, QUANTUM);


            printf("\n\nTempo de execução das tarefas na fila: [ ");
            for (int i = 0; i < SIZE; i++)
                printf("%d ", burst_time[i]);
            printf("]\n");

            printf("\nTABELA DE MÉTRICAS");
            printf("\nAlgoritmo | T. Médio de Espera | T. Médio de Vida\n");
            for (int i = 0; i < ALG; i++) {
                printf(" %s ", algoritmos[i]); 
                printf("\t\t%d ", espera[i]); 
                printf("\t\t%d\n", vida[i]);
            }
            break;
        default:
            x = 0;
            printf("Opção inválida!\n");
            sleep(2);
            system("clear");  // Limpa a tela
            break;
        }
    } while (x == 0);
    
    return 0;
}
