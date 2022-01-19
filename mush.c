#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main (){

    char s[2048];
    char *token;
    int i;
    char *argv[128];

    for(;;){
        char path[200];
        getcwd(path, 200);

        printf("%s$", path);
        fflush(stdout);
        fgets(s, sizeof s, stdin);

        i = 0;

        if ((token = strtok(s, " \t\n\r")) != NULL) {
            do {
                argv[i] = token;
                i++;
            } while ((token = strtok(NULL, " \t\n\r")) != NULL);
        }  
        argv[i] = NULL;


        if(strcmp(argv[0], "cd") == 0){
            int errid;
            errid = chdir(argv[1]);
            if(errid == -1){
                perror("chdri Error");
            }
            continue;
        }

        pid_t pid = fork();
        if(pid == 0){
            execvp(argv[0], argv);
            printf("Error: Command Not Found\n"); //If reach here: error. Child process should have terminated
        }
        wait(NULL);
        
        
    }
}