#include "Header.h"
#include "Execute.h"
#include "customRepeat.h"

void customRepeat(char * token, char * cwd, char * home_dir, char * prev_directory){

	int start = 6;
	int end = strlen(token);
	for (int i = 6; i < strlen(token); i++){
	    if( (token[i]==' ') || (token[i]=='\t'))
	        start = i;
	    else
	        break;
	}
	for (int i = strlen(token)-1; i >= 0; i--){
	    if( (token[i]==' ') || (token[i]=='\t'))
	        end = i;
	    else
	        break;
	}
	// printf("start:%d;end:%d", start, end);
	for( int i=start+1; i<end; i++ ){
	    token[i-start-1] = token[i];
	}
	token[end-start-1] = '\0';
	if( start>=end ){
		printf("repeat: Enter 2 Arguments.\n");
		return;
	}

	// printf("%s\n", token);
	// check if there's only 1 arg
	int flag = 0;
	for (int i = 0; i < strlen(token); i++){
		if( token[i]==' ' || token[i]=='\t' ){
			flag = 1;
		}
	}
	if(flag==0){
		printf("repeat: Too few arguments.\n");
		return;
	}

	// EXTRACT THE NUMBER
	char arg1[15];
	int arg1_int = 0;
	int last_pointer = -1;
	for (int i = 0; i < strlen(token); i++){
		if( token[i]==' ' || token[i]=='\t' ){
			break;
		}
		else{
			if( (token[i]>='0') && (token[i]<='9')){
				arg1[arg1_int++] = token[i];
				arg1[arg1_int] = '\0';
				last_pointer = i;
			}
			else{
				printf("repeat: The first argument has to be an positive integer.\n");
				return;
			}
		}
	}

	// REMOVE ARG_1 AND ANY GAPS AFTER THAT
	start = last_pointer + 1;
	end = strlen(token);
	for (int i = last_pointer + 1; i < strlen(token); i++){
	    if( (token[i]==' ') || (token[i]=='\t'))
	        start = i;
	    else
	        break;
	}
	for (int i = strlen(token)-1; i >= 0; i--){
	    if( (token[i]==' ') || (token[i]=='\t'))
	        end = i;
	    else
	        break;
	}
	// printf("start:%d;end:%d", start, end);
	for( int i=start+1; i<end; i++ ){
	    token[i-start-1] = token[i];
	}
	token[end-start-1] = '\0';
	// printf("%s\n", token);


	arg1_int = atoi(arg1);
	// printf("%d\n",arg1_int);
	for(int i=0; i<arg1_int;i++ ){
		Execute(token, cwd, home_dir, prev_directory);
	}



	return;
}