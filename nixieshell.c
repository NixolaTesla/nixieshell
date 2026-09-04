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

  printf("\nNIXIE SHELL V 2.2\n");
  printf("NixolaTesla on GitHub\n\n");
  printf("type 'help' for more information on the usage of nixieshell.\n");

while(1){

  count = 0;

  struct passwd *pw = getpwuid(getuid());

if (pw != NULL && getcwd(cwd, sizeof(cwd)) != NULL) {
    printf("%s:~%s$ ", pw->pw_name, cwd);
}

  if (fgets(userinput, sizeof(userinput), stdin) == NULL) {
    printf("\n");
    break;
 }

  userinput[strcspn(userinput, "\n")] = '\0';

  // parse user input

  char *token = strtok(userinput, " ");

  while(token != NULL && count < sizeof(parse) / sizeof(parse[0])){

    parse[count] = token;
    count++;

    token = strtok(NULL, " \n");
    parse[count] = NULL;
  }

  // USER INPUT TO THE SHELL (EXECVP)
  
  if(parse[0] == NULL){
    printf("\nInvalid Input\n");
    continue;
  }

  // help
  
  
  if(strcmp(userinput, "help") == 0){
    printf("\nWelcome to Nixie Shell! a lightweight unix shell written purely in C, you can also use it to larp better and show off the fact that you use a niche shell no one has ever heard of ;)\n\n");
  }

  // mkdir
  

    if(strcmp(parse[0], "mkdir") == 0){
       if(parse[1] == NULL){
          perror("mkdir");
       }
       else{
      mkdir(parse[1], 0755);
      }
    }
 

  // cd
   
   else if(strcmp(parse[0], "cd") == 0){
      chdir(parse[1]);
  }

    // EXIT SHELL

  else if(strcmp(parse[0], "exit") == 0){
    break;
  }

  // other commands ig idk
  //
  else{
    pid_t pid = fork();

    if(pid == 0){
      execvp(parse[0], parse);
    }

    else{
      waitpid(pid, NULL, 0);
    }
  }

 // v end of while(1) loop v
}
  
  
  return 0;
}
