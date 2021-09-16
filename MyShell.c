#include "Header.h"
#include "customPwd.h"
#include "customEcho.h"

int main(){

	char home_dir[PATH_MAX];
    getcwd(home_dir, PATH_MAX);
    char prev_directory[PATH_MAX];
    int prev_directory_set = 0;
	char hostname[HOST_NAME_MAX];
    char username[LOGIN_NAME_MAX];
    char cwd[PATH_MAX];
    cwd[0] = '~'; cwd[1] = '\0';

    while(1){

        gethostname(hostname, HOST_NAME_MAX);
        getlogin_r(username, LOGIN_NAME_MAX);
        printf("<%s@%s: %s>", username, hostname, cwd);

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
        // getline doens't add \0
        command[num_char_read-1] = '\0';
        // remove intial spaces and tabs
        int counter = 0;
        while( (command[counter]==' ') || (command[counter]=='	') )
        	counter++;
        for(int i=counter; i<=strlen(command);i++ )
        	command[i-counter] = command[i];
        // printf("%s", command);

        // WE NOW HAVE THE COMMANDS GIVEN IN A SINLGE INPUT
        // TIME TO LOOP THROUGH ALL THE COMMMANDS
        char *token;
        token = strtok(command, ";");
        while (token != NULL){

            // EXTRACT THE FIRST WORD (COMMAND WIHOUT ARGS)
            char curr_command[1024];
            curr_command[0] = '\0'; counter = 0;
            for(int i=0; i<=strlen(token); i++){
                if((token[i]==' ') || (token[i]=='\t')){
                    curr_command[counter] = '\0';
                    break;
                }
                curr_command[counter++] = token[i];
            }

            if ( strcmp(curr_command,"pwd")==0 )
                customPwd();
            else if ( strcmp(curr_command,"echo")==0 )
                customEcho(token);
            else if ( (strcmp(curr_command,"quit")==0) || (strcmp(curr_command,"exit")==0) || (strcmp(curr_command,"bye")==0)){
                printf("Bubyyeeee :)\n");
                return 0;
            }

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