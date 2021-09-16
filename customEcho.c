#include "Header.h"

void customEcho(char *in_text){

	int counter = 0;
	char *token;
    char command_without_space_or_tab[strlen(in_text)];
    token = strtok(in_text, "	");
    while(token!=NULL){
    	for(int i=0;i<strlen(token);i++)
    		command_without_space_or_tab[counter++] = token[i];
    	command_without_space_or_tab[counter++] = ' ';
    	token = strtok(0, "	");
    }
    command_without_space_or_tab[--counter] = '\0';
    strcpy(in_text, command_without_space_or_tab);
    strcpy(command_without_space_or_tab, "");
    counter = 0;
    token = strtok(in_text, " ");
    while(token!=NULL){
    	for(int i=0;i<strlen(token);i++)
    		command_without_space_or_tab[counter++] = token[i];
    	command_without_space_or_tab[counter++] = ' ';
    	token = strtok(0, " ");
    }
    command_without_space_or_tab[--counter] = '\0';
    for(int i=5; i<=strlen(command_without_space_or_tab); i++){
    	command_without_space_or_tab[i-5] = command_without_space_or_tab[i];
    }

	printf("%s\n"command_without_space_or_tab);

	return;
}