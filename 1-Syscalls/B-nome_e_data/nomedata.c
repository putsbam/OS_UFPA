#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>

int main () {

    struct stat filestat;
    struct dirent *file;  // Ponteiro pra entrada do diretório


    // opendir retorna um ponteiro de tipo DIR,
    // o ponteiro do tipo DIR representa uma sequência ordenadas das entradas de determinado diretório
    DIR *folder = opendir(".");  


    // opendir retorna NULL quando não consegue abrir o diretório.
    if(folder ==  NULL) {
        printf("Nao conseguiu abrir o diretorio");
        exit(1);
    }
    

    // readdir retorna um ponteiro para uma estrutura dirent
    // que representa a próxima entrada de diretório no fluxo de diretório apontado por dirp,
    // retorna NULL ao atingir o final do fluxo ou se ocorrer um erro.
    while ((file = readdir(folder))!= NULL) {
        stat(file->d_name,&filestat);
        printf("Nome: %s\n", file-> d_name);
        printf("Data: %s\n", ctime(&filestat.st_mtime));
    }


    closedir(folder); 
    return(0);

}
