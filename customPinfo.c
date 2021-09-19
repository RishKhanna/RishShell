#include "Header.h"
#include "customCd.h"

void customPinfo(char *in_text){

	int start = 5;
	int end = strlen(in_text);
	for (int i = 5; i < strlen(in_text); i++){
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


	int pid;
	if( start>=end ){
		pid = getpid();
	}
	else{
		// count num args
		for(int i=0;i<strlen(in_text);i++){
			if( (in_text[i]==' ') || (in_text[i]=='\t') ){
				printf("pinfo: Too many arguments.\n");
				return;
			}
		}
		pid = atoi(in_text);
	}
	// printf("%d\n",pid);
	// printf("%s\n",in_text );
	char process[1024];
    sprintf(process, "/proc/%d/stat", pid);
    FILE *fp = fopen(process, "r");
    char info[1024];
    if( fp==NULL ){
    	printf("pinfo: Process doesn't exist\n");
    	return;
    }
    else{
    	fscanf(fp, "%[^\n]s", info);
        fclose(fp);
    }
	char stat_stuff[106][4096];
	int arg_counter = 0, no_no = 0, info_counter = 0;
	while (info[info_counter] != '\0'){
		if (info[info_counter] != ' ' ){
			while (info[info_counter] != ' ' && info[info_counter] != '\0'){
				stat_stuff[arg_counter][no_no++] = info[info_counter++];
			}
			stat_stuff[arg_counter++][no_no] = '\0';
			no_no = 0;
		}
		info_counter++;
	}
	printf("pid: %d\n", pid);
    printf("Process Status: %s", stat_stuff[2]);
	// check if pid==this executable's pid
	if( (pid==getpid()) && ((*stat_stuff[2]=='R')||(*stat_stuff[2]=='S')) ){
		printf("+");
	}
	printf("\nMemory: %s\n", stat_stuff[22]);
    char exe_path[1024];
    char exe_path_link[1024];
    sprintf(exe_path,"/proc/%d/exe", pid);
    int check_read=readlink(exe_path, exe_path_link, 1024);
    if(check_read<0)
        printf("Executable path does not exist\n");
    else{
        printf("Executable Path: %s\n", exe_path_link);
    }

	return;
}