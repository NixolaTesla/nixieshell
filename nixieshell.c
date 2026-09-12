#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <pwd.h>
#include <sys/stat.h>

char shell[50];
char userinput[100];
char usern[25];
char cwd[1024];
int count = 0;
int count1 = 0;
char *parse1[50];
char *parse2[50];
int postpipe = 0;
float version = 3.2;


int main(int argc, char *argv[]){

  printf("\nNIXIE SHELL\n");
  printf("NixolaTesla on GitHub\n\n");
  printf("type 'help' for more information on the usage of Nixie Shell.\n");

while(1){

  count = 0;
  count1 = 0;
  postpipe = 0;

  struct passwd *pw = getpwuid(getuid());

  if(pw != NULL && getcwd(cwd, sizeof(cwd)) != NULL) {
    printf("%s:~%s$ ", pw->pw_name, cwd);
 }

  if(fgets(userinput, sizeof(userinput), stdin) == NULL){
    printf("\n");
    break;
 }

  userinput[strcspn(userinput, "\n")] = '\0';

  // parse user input
  
  char *token = strtok(userinput, " ");

  while(token != NULL && count < sizeof(parse1) / sizeof(parse1[0]) && count1 < sizeof(parse2) / sizeof(parse2[0])){

    if(*token == '|'){
      postpipe = 1;
    }

    else if(postpipe == 0){
      parse1[count] = token;
      count++;
    }

    else{
      parse2[count1] = token;
      count1++;
    }

    token = strtok(NULL, " \n");
    parse1[count] = NULL;
    parse2[count1] = NULL;
  }

  // USER INPUT TO THE SHELL (EXECVP)
  
  if(parse1[0] == NULL){
    printf("\n");
    continue;
  }

  // help
  
  
  if(strcmp(parse1[0], "help") == 0){
    printf("\nWelcome to Nixie Shell! a lightweight unix shell written purely in C, you can also use it to larp better and show off the fact that you use a niche shell no one has ever heard of ;)\n\n");
  }

  // nixie
 
    if(strcmp(parse1[0], "nixie") == 0){

       if(strcmp(parse1[1], "--version") == 0){
          printf("%0.1f\n", version);
       }
    }

  // mkdir
  

    if(strcmp(parse1[0], "mkdir") == 0){
       if(parse1[1] == NULL){
          perror("mkdir");
       }
       else{
      mkdir(parse1[1], 0755);
      }
    }
 

  // cd
   
 if(strcmp(parse1[0], "cd") == 0){
      chdir(parse1[1]);
  }

    // EXIT SHELL

  if(strcmp(parse1[0], "exit") == 0){
    break;
  }

  // other commands ig idk
  
  // PIPING STUFF IDFK THIS SHIT WAS SO CONFUSING TO FIGURE OUTT REUGHQOGWERHGEHGQPFHWFetesg
 
  if(parse2[0] != NULL){
    int fd[2];

    pipe(fd);

    pid_t pid67 = fork();
    // hahaha six seven

    if(pid67 == 0){
       dup2(fd[1], STDOUT_FILENO);

        close(fd[0]);
        close(fd[1]);

        execvp(parse1[0], parse1);

        perror("execvp");
        _exit(1);
    }

    pid_t pid69 = fork();

    // hahaha
    // sixty nine
    // nice

       if(pid69 == 0){

        dup2(fd[0], STDIN_FILENO);

        close(fd[0]);
        close(fd[1]);

        execvp(parse2[0], parse2);

        perror("execvp");
        _exit(1);
    }

    close(fd[0]);
    close(fd[1]);

    waitpid(pid67, NULL, 0);
    waitpid(pid69, NULL, 0);
  }

  // normal fucking child process

  else{
    pid_t pid = fork();

    if(pid == 0){
      execvp(parse1[0], parse1);
    }

    else{
      waitpid(pid, NULL, 0);
    }
  }

 // v end of while(1) loop v
}
  
  
  return 0;
}
