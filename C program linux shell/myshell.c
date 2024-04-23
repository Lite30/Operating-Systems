//C Program to implement a shell i Linux
#include<stdio.h> 
#include<string.h> 
#include<stdlib.h> 
#include<unistd.h> 
//research following includes
#include<sys/types.h> 
#include<sys/wait.h> 
#include <sys/types.h>
#include <termios.h>
#include <unistd.h>

#define MAXCHARS 1000 // max number of characters in a command to be supported 
#define MAXCOMMANDS 100 // max number of commands to be supported 

//global variables 

char cmd[MAXCHARS]; //string holder for commands
char *argv[MAXCOMMANDS];
pid_t pid;
char i;
// Clearing the shell using escape sequences 
//#define clear() printf("\033[H\033[J") 

// Function prototypes
void mycd(char *directory);
void myclr();
void mydir();
void myenviron();
void myecho(char *comment);
void myhelp();
void mypause();
void myquit();

//function to clear the terminal
void myclr() {
    printf("\033[H\033[J"); // ANSI escape code to clear screen
    fflush(stdout); // Flush output buffer
}
/**
 * Method for welcome screen to shell
 */
void welcomeScreen(){
        myclr();
        printf("\n\t============================================\n");
        printf("\t               Welcome to myShell\n");
        printf("\t--------------------------------------------\n");
        printf("\t             Created by Liteboho Maseli\n");
        printf("\t============================================\n");
        printf("\n\n");

}
void myquit() {
    exit(0);
}
void mydir() 
{ 
	char cwd[1024]; 
	getcwd(cwd, sizeof(cwd)); 
	printf("\nDir: %s", cwd); 
} 
void get_cmd() {
    printf("%s> ", getcwd(NULL, 0));
    fgets(cmd, MAXCHARS, stdin);
    if ((strlen(cmd) > 0) && (cmd[strlen(cmd) - 1] == '\n'))
        cmd[strlen(cmd) - 1] = '\0';
}
int main()
{
    while(1){
        welcomeScreen();
        get_cmd();
        mydir();


    }
    return 0;
}