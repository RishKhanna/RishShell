#include "Header.h"
#include "customHistory.h"

void saveHistory(char *in_text){

	char in_text_copy[100000];
	strcpy(in_text_copy, in_text);
	
	// remove extraspaces and tabs
	int start = -1;
	int end = strlen(in_text_copy);
	for (int i = 0; i < strlen(in_text_copy); i++){
	    if( (in_text_copy[i]==' ') || (in_text_copy[i]=='\t'))
	        start = i;
	    else
	        break;
	}
	for (int i = strlen(in_text_copy)-1; i >= 0; i--){
	    if( (in_text_copy[i]==' ') || (in_text_copy[i]=='\t'))
	        end = i;
	    else
	        break;
	}
	// printf("start:%d;end:%d", start, end);
	for( int i=start+1; i<end; i++ ){
	    in_text_copy[i-start-1] = in_text_copy[i];
	}
	in_text_copy[end-start-1] = '\0';
	if( start>=end )
		return;

	char file_path[1024];
    sprintf(file_path, "%s/.RishShell_history", home_dir);
    int fd = open(file_path, O_RDWR | O_CREAT, 0666);
    if(fd<0){
        printf("history: Failed to write to history\n");
        return;
    }
    lseek(fd, 0, SEEK_SET);
    char line[100000] = {'\0'};
    int read_check = read(fd, line, 100000);
    if(read_check<0){
        printf("history: Failed to write to history\n");
        return;
    }
    int num_lines = 0;
    for (int i = 0; i < strlen(line); i++){
        if (line[i] == '\n'){
            num_lines++;
        }
    }
    // printf("num_lines:%d\n",num_lines);
    in_text_copy[strlen(in_text_copy)+1] = '\0';
    in_text_copy[strlen(in_text_copy)] = '\n';
    char last_com[100000];
    int last_com_counter = 0;

	// check last commands
    if( num_lines > 1 ){
    	// printf("a");
    	for(int i=strlen(line)-2; i>=0; i--){
    		if( line[i]=='\n' ){
    			// printf("1");
    			i++;
    			while( i<=strlen(line) ){
    				// printf("2");
    				last_com[last_com_counter++] = line[i++];
    				last_com[last_com_counter] = '\0';
    			}
    			break;
    		}
    	}
    }
    else if(num_lines==1){
    	// printf("b");
    	strcpy(last_com, line);
    }
    else{
    	// printf("c");
    	write(fd, in_text_copy, strlen(in_text_copy));
    	return;
    }
	

	// printf("last_com:%s",last_com);
	if( strcmp(last_com, in_text_copy)==0 ){
		// printf("boom");
		return;
	}

	if( num_lines>=20 ){
		char hist_list[30][2000];
		int char_count = 0;
		int ind=0;
		for(int i=0;i<strlen(line);i++ ){
			if( line[i]=='\n' ){
				char_count = 0;
				ind++;
			}
			else{
				hist_list[ind][char_count++] = line[i];
				hist_list[ind][char_count] = '\0';
			}
		}
		strcpy(hist_list[20], in_text_copy);
		// remove the last '\n'
		hist_list[20][strlen(hist_list[20]) - 1] = '\0';

		char_count = 0;
		char final_out[10000];
		for(int i=1;i<=20;i++){
			for(int j=0;j<strlen(hist_list[i]);j++){
				final_out[char_count++] = hist_list[i][j];
			}
			final_out[char_count++] = '\n';
		}
		// printf("%s", final_out);

		int fd1 = open(file_path, O_RDWR | O_TRUNC);
		write(fd1, final_out, strlen(final_out));
		close(fd1);
		close(fd);
	}
	else{
		write(fd, in_text_copy, strlen(in_text_copy));
	}

	return;	
}


void showHistory(char *in_text){

	int start = 7;
	int end = strlen(in_text);
	for (int i = 7; i < strlen(in_text); i++){
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
	for( int i=start+1; i<end; i++ ){
		in_text[i-start-1] = in_text[i];
	}
	in_text[end-start-1] = '\0';
	// printf("%s", in_text);


	int range = -1;
	if(start>=end){
		range = 10;
	}
	else{
		for(int i=0;i<strlen(in_text);i++ ){
			if( !((in_text[i]>='0') && (in_text[i]<='9')) ){
				printf("history: The 2nd argument has to be a positive integer\n");
				return;
			}
		}
		range = atoi(in_text);
	}
	// printf("range:%d",range);

	char file_path[1024];
	sprintf(file_path, "%s/.RishShell_history", home_dir);
	int fd = open(file_path, O_RDWR | O_CREAT, 0666);
	if(fd<0){
	    printf("history: Failed to open ~/.RishShell_history\n");
	    return;
	}
	lseek(fd, 0, SEEK_SET);
	char line[100000] = {'\0'};
	int read_check = read(fd, line, 100000);
	if(read_check<0){
	    printf("history: Failed to read history\n");
	    return;
	}

	char hist_list[30][2000];
	int char_count = 0;
	int ind=0;
	for(int i=0;i<strlen(line);i++ ){
		if( line[i]=='\n' ){
			char_count = 0;
			ind++;
		}
		else{
			hist_list[ind][char_count++] = line[i];
			hist_list[ind][char_count] = '\0';
		}
	}
	// printf("%d", ind);
	if( range > ind ){
		start = 0;
	}
	else{
		start = ind - range;
	}


	char_count = 0;
	char final_out[10000];
	for(int i=start;i<=ind-1;i++){
		for(int j=0;j<strlen(hist_list[i]);j++){
			final_out[char_count++] = hist_list[i][j];
		}
		final_out[char_count++] = '\n';
	}
	// final_out[strlen(final_out)-1] = '\0';
	printf("%s",final_out);
	// printf("pop");
}
