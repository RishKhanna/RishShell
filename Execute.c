#include "Header.h"
#include "customPwd.h"
#include "customEcho.h"
#include "customLs.h"
#include "customCd.h"
#include "customPinfo.h"
#include "customRepeat.h"
#include "sysCommands.h"
#include "customHistory.h"
#include "customRedirect.h"
#include "Execute.h"

void Execute(char * token, char * cwd, char * home_dir, char * prev_directory){

	// CHECK FOR PIPING
	for(int i=0;i<=strlen(token);i++){
		if(token[i]=='|'){
			customRedirect(token);
			return;
		}
	}


	// EXTRACT THE FIRST WORD (COMMAND WIHOUT ARGS)
	char curr_command[1024];
	curr_command[0] = '\0';
	int counter = 0;
	for(int i=0; i<=strlen(token); i++){
	    if((token[i]==' ') || (token[i]=='\t')){
	        curr_command[counter] = '\0';
	        break;
	    }
	    curr_command[counter++] = token[i];
	}

	if( strcmp(curr_command,"")==0 ){
	    int cool = 0;
	}
	else if( strcmp(curr_command,"cd")==0 ){
	    int cd_check = customCd(token, cwd, home_dir, prev_directory);
	    if (cd_check){
	        strcpy(prev_directory,cwd);
	        updateCwd(home_dir, cwd);
	    }
	}
	else if ( strcmp(curr_command,"pwd")==0 )
		customPwd();
	else if ( strcmp(curr_command,"echo")==0 )
		customEcho(token);
	else if ( strcmp(curr_command,"ls")==0 )
		customLs(token, home_dir);
	else if( strcmp(curr_command,"pinfo")==0 )
		customPinfo(token);
	else if( strcmp(curr_command,"repeat")==0 )
		customRepeat(token, cwd, home_dir, prev_directory);
	else if( strcmp(curr_command,"history")==0 )
		showHistory(token);
	else if ( (strcmp(curr_command,"quit")==0) || (strcmp(curr_command,"exit")==0) || (strcmp(curr_command,"bye")==0)){
	    printf("Bubyyeeee :)\n");
	    exit(0);
	}
	else{
	    // remove starting and ending's spaces
	    int start = -1;
	    int end = strlen(token);
	    for (int i = 0; i < strlen(token); i++){
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
	    // check if last element is &
	    if( token[strlen(token) - 1]=='&' ){
	        sysCommands(token, 1);
	    }
	    else{
	        sysCommands(token,0);
	    }
	}



	return;
}