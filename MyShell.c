#include "Header.h"
#include "customPwd.h"
#include "customEcho.h"
#include "customLs.h"
#include "customCd.h"
#include "customPinfo.h"
#include "sysCommands.h"
#include "customHistory.h"
#include "Execute.h"  // KEEP THIS LAST

int main(){

	// initialise dir stuff
    // char home_dir[PATH_MAX];
    char prev_directory[PATH_MAX];
    getcwd(home_dir, PATH_MAX);
    getcwd(prev_directory, PATH_MAX);
    // int prev_directory_set = 0;
    char hostname[HOST_NAME_MAX];
    char username[LOGIN_NAME_MAX];
    char cwd[PATH_MAX];
    cwd[0] = '~'; cwd[1] = '\0';

    // initialise linkedlist for bg process
    initial = malloc(sizeof(struct bg_prc));
    initial->size = 0;
    initial->next = NULL;
    initial->pid = getpid();

    while(1){

        gethostname(hostname, HOST_NAME_MAX);
        getlogin_r(username, LOGIN_NAME_MAX);
        printf("<%s@%s:%s>", username, hostname, cwd);

        // NOW WE ATTEMPT TO INPUT COMMANDS FROM THE TERMINAL
        char *command;
        command = malloc(1024 * sizeof(char));
        size_t bufsize = 1024;
        int num_char_read = getline(&command, &bufsize, stdin);
        // getline returns '-1' when cntr+D [exit command] is used
        if(num_char_read == -1){
        	printf("\nBubyyeeee :)\n");
        	return 0;
        }
        // printf("%ld;%s",strlen(command), command);
        // getline doens't add \0
        command[num_char_read-1] = '\0';
        // printf("%ld;%s",strlen(command), command);
        saveHistory(command);
        // remove intial spaces and tabs
        int counter = 0;
        while( (command[counter]==' ') || (command[counter]=='	') ){
        	counter++;
        }
        for(int i=counter; i<=strlen(command);i++ ){
        	command[i-counter] = command[i];
        }

        // WE NOW HAVE THE COMMANDS GIVEN IN A SINLGE INPUT
        // TIME TO LOOP THROUGH ALL THE COMMMANDS
        char *token;
        token = strtok(command, ";");
        while (token != NULL){

            Execute(token, cwd, home_dir, prev_directory);

        	// moves to the next command
            token = strtok(NULL, ";");
            if(token==NULL)
                continue;
            while( (token[0]==' ') || (token[0]=='\t') ){
                for(int i=1;i<strlen(token);i++){
                    token[i-1] = token[i];
                }
                token[strlen(token)-1] = '\0';
            }

        }



    }

	return 0;
}