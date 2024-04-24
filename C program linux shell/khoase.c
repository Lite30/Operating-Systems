#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

(void)argc, (void)argv;
char *buf = NULL, *token;
size_t count = 0;
ssize_t nread;
pid_t child_pid;   //child process 
int i, status;
char **array;

void MyShell(){

  while (1){  //infinite loop
    
      write(STDOUT_FILENO, "MyShell$ ", 9);  //print statement

      nread = getline(&buf, &count, stdin); //get line from user input 

      if (nread ==  -1) {
        
        perror("Exiting shell");
        exit(1);
    }

      token = strtok(buf, " \n");

      array = malloc(sizeof(char*) * 1024);
      i = 0;

      while (token){
        array[i] = token;
        token = strtok(NULL, " \n");
        i++;
      }

      array[i] = NULL;

      child_pid = fork();

      if (child_pid == -1){
          
            perror("Failed to create.");
            exit (41);
        }

      if (child_pid == 0){
          if (execve(array[0], array, NULL) == -1){
            
              perror("Failed to execute");
              exit(97);
            }
          }
      else{
            wait(&status);
            }
    }
  free(buf);
}

void get_command();
void convert_command();
void make_directry();
void pause();
void clear();
void 


int main()
       

        
