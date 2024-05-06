#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_COMMANDS 256
#define MAX_ARGS 16
#define MAX_PATH_LEN 1024

char current_directory[MAX_PATH_LEN];

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define MAX_PATH_LEN 1024

void mycd(char *directory) {
    if (directory != NULL & strlen(directory)>0) {
        // If no directory is provided, print the current directory
        if (chdir(directory) != 0) {
        // If changing directory fails, print an error
        perror("mycd error");
        return;
    }
    } 
    else {
       if (getcwd(current_directory,sizeof(current_directory))==NULL){
       perror("getcwd error");
       return;
       }
       printf("current directory is: %s\n",current_directory);
    }
    
    if (getcwd(current_directory,sizeof(current_directory))!=NULL){
       char env_variable[1040];
       snprintf(env_variable,sizeof(env_variable),"PWD=%s",current_directory);
       putenv(env_variable);
       printf("current directory: %s\n",current_directory);
       }
       else {
       perror("error updating pwd");
       }
      }



void myclr() {
    // Clear the screen using ANSI escape codes
    printf("\033[H\033[J");
}

void mydir(char *directory) {
    DIR *dir;
    struct dirent *entry;

    if (directory == NULL) {
        // If no directory is provided, use the current directory
        directory = current_directory;
    }

    dir = opendir(directory);
    if (dir == NULL) {
        perror("mydir");
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        printf("%s\n", entry->d_name);
    }

    closedir(dir);
}

void myenviron() {
    extern char **environ;
    char **env = environ;

    while (*env) {
        printf("%s\n", *env++);
    }
}

void myecho(char *comment) {
    // Simply print the comment followed by a newline
    printf("%s\n", comment);
}

void myhelp() {
    // Use more to display the user manual
    system("more myshell_manual.txt");
}

void mypause() {
    // Pause until Enter is pressed
    printf("Press Enter to continue...");
    getchar(); // Read a single character (Enter)
}

void myquit() {
    // Quit the shell
    exit(0);
}

void welcomeScreen() {
    myclr();
    printf("\n\t============================================\n");
    printf("\t               Welcome to myShell\n");
    printf("\t--------------------------------------------\n");
    printf("\t             Created by SNAILS\n");
    printf("\t============================================\n");
    printf("\n\n");
}

void shell() {
    char *command;
    char *argv[MAX_ARGS];  // Declaring argv locally
    char *token;
    const char delim[2] = " ";
    int argc;

    while (1) {
        printf("%s> ", current_directory);
        command = (char *)malloc(MAX_COMMANDS * sizeof(char));
        if (command == NULL) {
            perror("malloc");
            exit(EXIT_FAILURE);
        }

        // Read the command from stdin
        if (fgets(command, MAX_COMMANDS, stdin) == NULL) {
            free(command);
            perror("fgets");
            exit(EXIT_FAILURE);
        }


        // Remove newline character if present
        size_t len = strlen(command);
        if (len > 0 && command[len - 1] == '\n') {
            command[len - 1] = '\0';
        }

        // Tokenize the command
        token = strtok(command, delim);
        argc = 0;
        while (token != NULL && argc < MAX_ARGS - 1) {
            argv[argc++] = token;
            token = strtok(NULL, delim);
        }
        argv[argc] = NULL;

        // Handle internal commands
        if (strcmp(argv[0], "mycd") == 0) {
            mycd(argv[1]);
        } else if (strcmp(argv[0], "myclr") == 0) {
            myclr();
        } else if (strcmp(argv[0], "mydir") == 0) {
            mydir(argv[1]);
        } else if (strcmp(argv[0], "myenviron") == 0) {
            myenviron();
        } else if (strcmp(argv[0], "myecho") == 0) {
            // Reconstruct the comment
            char comment[MAX_COMMANDS];
            strcpy(comment, argv[1]);
            for (int i = 2; i < argc; i++) {
                strcat(comment, " ");
                strcat(comment, argv[i]);
            }
            myecho(comment);
        } else if (strcmp(argv[0], "myhelp") == 0) {
            myhelp();
        } else if (strcmp(argv[0], "mypause") == 0) {
            mypause();
        } else if (strcmp(argv[0], "myquit") == 0) {
            myquit();
        } else {
            // External commands
            pid_t pid = fork();
            if (pid == 0) {
                execvp(argv[0], argv);
                perror("execvp");
                exit(EXIT_FAILURE);
            } else if (pid > 0) {
                wait(NULL);
            } else {
                perror("fork");
            }
        }

        free(command);
    }
}

int main() {
    // Initialize current directory
    getcwd(current_directory, sizeof(current_directory));

    // Display welcome screen
    welcomeScreen();

    // Start the shell
    shell();

    return 0;
}
