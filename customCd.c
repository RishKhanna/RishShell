#include "Header.h"

void updateCwd(char *home_dir, char *final){
	char curr_dir[PATH_MAX];
	getcwd(curr_dir, PATH_MAX);

	if( strlen(curr_dir)<strlen(home_dir) ){
		strcpy(final, curr_dir);
		return ;
	}
	else{
		// check if ~ is there in path
		int flag = 0;
		for(int i=0;i<strlen(home_dir);i++){
			if( curr_dir[i]!=home_dir[i] ){
				flag = 1;
			}
		}
		if( flag ){
			strcpy(final, curr_dir);
			return ;
		}
		else{
			curr_dir[0] = '~';
			int home_dir_len = strlen(home_dir);
			for(int i=home_dir_len;i<=strlen(curr_dir);i++ ){
				curr_dir[i - home_dir_len + 1] = curr_dir[i];
			}
			strcpy(final, curr_dir);
			return ;
		}
	}

}




int customCd(char *in_text,char *curr_dir, char *home_dir, char *prev_directory){

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
	if( start>=end ){
		// strcpy(final_path, home_dir);
		// final_counter = strlen(home_dir);
		chdir(home_dir);
		return 1;
	}

	// printf("%s\n", in_text);

	// CHECK NUMBER OF ARGUMENTS GIVEN
	for(int i=0;i<strlen(in_text);i++ ){
		if( (in_text[i]==' ') && (in_text[i]!='\\')){
			printf("cd: Too many arguments.");
			return 0;
		}
	}

	int final_counter = 0;
	if( strcmp(in_text, "-")==0 ){
		// if(prev_dir_flag==0){
		// 	printf("cd: No previous directory\n");
		// 	return 0;
		// }
		// else{
			for(int i=0; i<=strlen(prev_directory);i++){
				if( prev_directory[i]=='~' ){
					for(int j=0; j<strlen(home_dir);j++){
						final_path[final_counter++] = home_dir[j];
					}
				}
				else{
					final_path[final_counter++] = prev_directory[i];
				}
			}
			final_path[final_counter] = '\0';
		// }
	}
	else if( strcmp(in_text, ".")==0 ) {
		return 1;
	}
	else{
		for(int i=0; i<=strlen(in_text);i++){
			if( in_text[i]=='~' ){
				for(int j=0; j<strlen(home_dir);j++){
					final_path[final_counter++] = home_dir[j];
				}
			}
			else{
				final_path[final_counter++] = in_text[i];
			}
		}
		final_path[final_counter] = '\0';
	}

	// now to check if the destination exists
	struct stat st;
    int exist = stat(final_path, &st);
    if (exist != 0){
        printf("cd: Directory/file doesn't exist\n");
        return 0;
    }

    // check if the destination is a dir
    if( S_ISDIR(st.st_mode) ){
    	// check permissions
    	if (st.st_mode & S_IXUSR){
    		chdir(final_path);
			if( strcmp(in_text, "-")==0 ){
				char print_path[PATH_MAX];
				strcpy(print_path, final_path);
				updateCwd(home_dir,print_path);
				printf("%s\n", print_path);
			}
    		return 1;
    	}
    	else{
    		printf("cd: Permission Denied\n");
    		return 0;
    	}
    }
    else{
    	printf("cd: Not a directory\n");
    	return 0;
    }


	return 0;
}