#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

#define READ  0 //entrada estandar STDIN. 
#define WRITE 1 //Salida estandar STDOUT. 

int main() {
  
  pid_t pid;
  int   fd[2];
  char *vector1[2]; 
  char *vector2[3]; 
  
  //char *args[1]; 

  if (pipe(fd) == -1) { // si el arreglo de fd es igual a -1 entonces hay un error al momento de llamar al pipe. 
	perror("Creating pipe"); //produce un mensaje que va a a la salida estandar de errores. stderr [2]
	exit(EXIT_FAILURE);
  }





  switch(pid = fork()) { //con fork estamos haciendo la llamada al sistema que nos permite crear otro proceso nuevo.

  case 0: //proceso hijo del fork que se creo .

//   lo que se hace arriba l0 va
//   a ejecutar tambien en el nuevo proceso
    //args = [ "sort", NULL]; 


	// The child process will execute wc.
	// Close the pipe write descriptor.
	close(fd[WRITE]);
	// Redirect STDIN to read from the pipe.
	dup2(fd[READ], STDIN_FILENO);

    vector1[0] = "sort"; 
    vector1[1] = NULL; 
	// Execute wc
	execvp(vector1[0], vector1);

    break; 
  case -1:
	perror("fork() failed)");
    exit(EXIT_FAILURE);
    break; 

  default:
	// The parent process will execute ls.
	// Close the pipe read descriptor.
	close(fd[READ]);
	// Redirect STDOUT to write to the pipe.
	dup2(fd[WRITE], STDOUT_FILENO);

    vector2[0] = "cat"; 
    vector2[1] = "/etc/hosts"; 
    vector2[2] = NULL;
	// Execute ls -l
	execvp(vector2[0], vector2);
    
    break; 
  }
}
