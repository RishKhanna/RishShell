#include "Header.h"

int customCd(char *in_text,char *curr_dir, char *home_dir, char *prev_directory, int prev_dir_flag){

	// printf("%s\n", in_text);
	char final_path[PATH_MAX];

	// code to remove starting and ending's spaces
	int start = 2;
	int end = strlen(in_text);
	for (int i = 2; i < strlen(in_text); i++){
		if( (in_text[i]==' ') || (in_text[i]=='\t'))
			start = i;
		else
			break;
	}
	for (int i = strlen(in_text)-1; i >= 0; i--){
		if( (in_text[i]==' ') || (in_text[i]=='\t'))
			end = i;
		else
			break;
	}
	// printf("start:%d;end:%d", start, end);
	for( int i=start+1; i<end; i++ ){
		in_text[i-start-1] = in_text[i];
	}
	in_text[end-start-1] = '\0';

	printf("%s\n", in_text);
	if( start>=end ){
		strcpy(final_path, home_dir);
	}

	// CHECK NUMBER OF ARGUMENTS GIVEN
	for(int i=0;i<strlen(in_text);i++ ){
		if( (in_text[i]==' ') && (in_text[i]!='\\')){
			printf("cd: Too many arguments.");
			return 0;
		}
	}


	// if( strcmp(in_text,".")==0 ){
		
	// }

	return 1;
}