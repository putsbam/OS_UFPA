#include <stdio.h>
#include <stdlib.h>
 
int main() { 

    // Variáves FILE

    FILE *a1, *a2, *a3;
 
    // Variáveis char valores de string
    // Alocar espaço de 30 caracteres para o nome das variáveis de arquivo 

    char ch, arquivo1[31], arquivo2[31], arquivo3[31];
 
    // Função "gets" lê a entrada "arquivo" colocada no terminal

    printf("Entrada 1: Nome_do_primeiro_arquivo.extensão\n");    
    gets(arquivo1);

    printf("Entrada 2: Nome_do_segundo_arquivo.extensão\n");
    gets(arquivo2);
 
    printf("Saída: Nome_do_arquivo_saida.extensão\n");
    gets(arquivo3);
 
    // Função "fopen" abre o arquivo passando pelos argumentos (arquivo, tipo), "r" nesse caso, significa "read"
    // ou seja, abrir os arquivos arquivo1 e arquivo2 em modo de leitura
    // esse valor é atribuído às variáveis "a1" e "a2"

    a1 = fopen(arquivo1, "r"); 
    a2 = fopen(arquivo2, "r");
 
    // Lidar com erros caso os arquivos não existam, retornando EXIT_FAILURE (uma operação não completada), e finalizando o programa

    if(a1 == NULL || a2 == NULL) {
        perror("Error "); // Print Error
        printf("Aperte qualquer tecla para sair.\n");
        exit(EXIT_FAILURE);
    }
 
    // Aqui, a função fopen passará o arquivo de saída em modo "w", que sinaliza "write" (escrita)
    // esse valor é atribuído à variável "a3"

    a3 = fopen(arquivo3, "w");        

    // Lidar com erro na falta de arquivo novamente (no caso, se não for possível escrevê-lo)
 
    if(a3 == NULL) {
        perror("Error "); // Print Error
        printf("Aperte qualquer tecla para sair.\n");
        exit(EXIT_FAILURE);
    }
 
    // Loop 1 para copiar o conteúdo (char) do primeiro arquivo para o terceiro
    // Enquanto o conteúdo for diferente de EOF (End Of File), fputc é executada
    // A função fputc copia o conteúdo (char) de ch para o arquivo file

    while((ch = fgetc(a1)) != EOF)
        fputc(ch,a3);
 
    // Loop 2 para copiar o conteúdo (char) do segundo arquivo para o terceiro
 
    while((ch = fgetc(a2)) != EOF)
        fputc(ch,a3);
 
    printf("Arquivos concatenados com sucesso!\n > %s gerado.\n", arquivo3);
 
    // A função fclose fecha os arquivos especificados
    // Caso bem sucedida, retorna 0, do contrário, EOF é retornado

    fclose(a1);
    fclose(a2);
    fclose(a3);
 
    return 0;

}
