#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*

	Este código tem como função executar o comando "passwd" para solicitar
	a troca de senha do usuário atual.

*/

int main() {

	char command[50]; // Variável char command com uma string de 50 caracteres

	strcpy(command, "passwd"); // Adicionar a string (comando) "passwd" à variável command

	system(command); // Executar command no system
	
	return 0;


}
