#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <pwd.h>
#include <sys/stat.h>

char shell[50];
char userinput[100];
char dir[50];
char usern[25];
char cwd[1024];
int count = 0;
char *parse[50];


int main(int argc, char *argv[]){

  char *pid_ls[] = {"ls", NULL};
  char *pid_ff[] = {"fastfetch", NULL};
  char *pid_nf[] = {"neofetch", NULL};
  char *pid_clear[] = {"clear", NULL};
  char *pid_pwd[] = {"pwd", NULL};

  printf("\nNIXIE SHELL V1\n");
  printf("NixolaTesla on GitHub\n\n");
  printf("type 'help' for more information on the usage of nixieshell.\n");

while(1){

  count = 0;

  struct passwd *pw = getpwuid(getuid());

if (pw != NULL && getcwd(cwd, sizeof(cwd)) != NULL) {
    printf("%s:~%s$ ", pw->pw_name, cwd);
}

  fgets(userinput, sizeof(userinput), stdin);
  userinput[strcspn(userinput, "\n")] = '\0';

  // parse user input

  char *token = strtok(userinput, " ");

  while(token != NULL && count < sizeof(parse) / sizeof(parse[0])){

    parse[count] = token;
    count++;

    token = strtok(NULL, " \n");
  }

  // USER INPUT TO THE SHELL (EXECVP)
  

  // help
  
  
  if(strcmp(userinput, "help") == 0){
    printf("\ncommands: ls,cd,pwd,fastfetch,neofetch,exit,clear\n\n");
    printf("to use cd, type cd and hit enter, you will then be prompted to input your desired directory.\n\n");
    printf("(to return to the previous directory, just type in ..)\n\n");
  }

  // ls

  if(strcmp(userinput, "ls") == 0){
    pid_t pid = fork();

    if(pid == 0){
    execvp(pid_ls[0], pid_ls);
    perror("EXECVP FAILED");
   }

    else{
     waitpid(pid, NULL, 0);
   }
  }

  // fastfetch

    if(strcmp(userinput, "fastfetch") == 0){
    pid_t pid = fork();

    if(pid == 0){
    execvp(pid_ff[0], pid_ff);
    perror("EXECVP FAILED");
   }

    else{
      waitpid(pid, NULL, 0);
    }
  }

    // neofetch

    if(strcmp(userinput, "neofetch") == 0){
    pid_t pid = fork();

    if(pid == 0){
    execvp(pid_nf[0], pid_nf);
    perror("EXECVP FAILED");
   }

    else{
     waitpid(pid, NULL, 0);
   }
  }

  // clear
 
   if(strcmp(userinput, "clear") == 0){
     pid_t pid = fork();

     if(pid == 0){
       execvp(pid_clear[0], pid_clear);
       perror("EXECVP FAILED");
     }

     else{
       waitpid(pid, NULL, 0);
     }
   }



   // pwd

   if(strcmp(userinput, "pwd") == 0){
      pid_t pid = fork();

      if(pid == 0){
	printf("\n");
        execvp(pid_pwd[0], pid_pwd);
	perror("EXECVP FAILED");
    }

      else{
        waitpid(pid, NULL, 0);
    }
  }

  // mkdir
  

    if(strcmp(userinput, "mkdir") == 0){
      printf("INPUT DIR NAME: ");
      fgets(dir, sizeof(dir), stdin);
      dir[strcspn(dir, "\n")] = '\0';
      mkdir(dir, 0755); 
    }
 

  // cd
   
    if(strcmp(parse[0], "cd") == 0){
      chdir(parse[1]);
      perror("cd");
  }

    // EXIT SHELL

  if(strcmp(userinput, "exit") == 0){
    break;
  }
}
  
  
  return 0;
}
