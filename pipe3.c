#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <time.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <assert.h>
#include <fcntl.h>


#define READ  0
#define WRITE 1

int main() {

  pid_t pid;
  int   fd1[2]; 
  char *nombre_archivo =  "numeroRandom.txt";
  int numero_aleatorio = 0;

  if (pipe(fd1) == -1) {
	perror("Creating pipe");
	exit(EXIT_FAILURE);
  }


  pid = fork();
 
  switch (pid) {
    case -1:
      perror("fork() failed)");
      exit(EXIT_FAILURE);
      break;
    case 0:
         // The child process will execute wc.
        // Close the pipe write descriptor.
        close(fd1[WRITE]);
        // Redirect STDIN to read from the pipe.
        dup2(fd1[READ], STDIN_FILENO);
        
        char buffer1[20];
        fscanf(stdin,"%s",buffer1);

        //pasero de char a int
        int numero = atoi(buffer1);
        //verificar si es mayor a 500
        if (numero > 500) {
          printf("mayor o igual a 500\n");
        } else {
          printf("menor que 500\n");
        }
        
      break;
    default:
        // Close the pipe read descriptor.
        close(fd1[READ]);
        // Redirect STDOUT to write to the pipe.
        dup2(fd1[WRITE], STDOUT_FILENO);

        //generar un numero aleatorio del 1 al 1000
        srand(time(NULL));
        numero_aleatorio = rand() % 1000 + 1;
        printf("%d\n", numero_aleatorio);

        //como el toma la salidad como entrada, lo que recibe es la impresion

    break;
  }

  return 0;
}