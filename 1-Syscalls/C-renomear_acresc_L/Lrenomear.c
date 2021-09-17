#include <stdio.h> 
#include <stdlib.h>

// Bibliotecas necessárias para gerenciamento de memória/diretório
#include <dirent.h> 
#include <string.h>
#include <memory.h>

/*

    Este código tem como finalidade passar por todos os arquivos do diretório,
    renomeando-os, colocando a string "L" no começo.

*/

 
int main(void) {
  DIR * d; // Variável de referência ao diretório
  struct dirent * dir; // Entrada do diretório, definida pela biblioteca <dirent.h>
  d = opendir("."); // Função para abrir o diretório atual
  int rf; // Usado para receber o valor da função rename, usada posteriormente
  char L[] = "L"; // Caractere "L" que será adicionado ao renomear
 
  if (d) { // Caso o diretório exista

    while ((dir = readdir(d)) != NULL) { 

    // Enquanto o valor da função readdir(d) for diferente de NULL, será executado o loop
    // Ou seja, caso sucedida, será executado o loop e retornará um ponteiro
    // para um objeto de tipo "struct dirent" (dir)

      char * filename = dir -> d_name; // Variável para armazenar o nome do arquivo

      // malloc serve para alocar espaço na RAM, para um bloco consecutivo de bytes
      // sendo estes bytes definidos pelo tamanho do nome do arquivo

      char * result = (char *) malloc(1 +sizeof(char*) * (strlen(L)+ strlen(filename)));

      strcpy(result, L); // Copiar a string "L" para o resultado acima (nome do arquivo alocado)
      strcat(result, filename); // Concatenar (juntar) duas strings, no caso o nome do arquivo com L na variável result
 
      rf = rename(filename, result); // Função para renomear o arquivo (retorna 0 caso sucedida)
 
      if(rf == 0){ // Se bem-sucedida, print dos resultados

      printf("Arquivo renomeado: %s\n", result);

      } else { // Caso não, dispara a exceção

        printf("Erro ao renomear o arquivo: %s", filename);
        exit(-1);

      }
    }

    closedir(d); // Fechar o diretório após execução

  }

  return(0); // Fim da execução

}
