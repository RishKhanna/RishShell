#include "Header.h"
#include "jobs_sort.h"
#include "sysCommands.h"

char getstatus(int pid){
    char path[1024];
    sprintf(path,"/proc/%d/status", pid);
    FILE* fd = fopen(path, "r");
    if(fd==NULL){
        fprintf(stderr, "jobs: Error: could not open %s\n", path);
        return '1';
    }
    else{
        int linecount=0;
        char line[1024];
        while(linecount<3){
            fgets(line,sizeof(line), fd);
            linecount++;
        }
        int trav=0;
        while(line[trav]!='\t'){
            trav++;
        }
        fclose(fd);
        return line[trav+1];
    }
}

void jobs(char *in_text){
	jobs_sort();
	int r_flag=0;
	int s_flag=0;
	int flag_check =0;
	for(int i=0;i<strlen(in_text);i++){
		if(in_text[i]=='-'){
			flag_check = 1;
			if(in_text[i+1]=='r'){
				r_flag=1;
				if(in_text[i+2]=='s'){
					s_flag=1;
				}
			}
			else if(in_text[i+1]=='s'){
				s_flag=1;
				if(in_text[i+2]=='r'){
					r_flag=1;
				}
			}
			else{
				printf("jobs: Invalid flags.\n");
				return;
			}
		}
	}
	if(flag_check==0){
		r_flag=1;
		s_flag=1;
	}
	// printf("%d %d\n",r_flag, s_flag);
	int counter=0;
	struct bg_prc *temp;
    temp = initial->next;
    while(temp!=NULL){
    	char stat;
    	counter++;
    	stat = getstatus(temp->pid);
    	printf("%c\n",stat );
		if((stat=='T')&&(s_flag==0)){
			continue;
		}
		else if((stat!='1')&&(r_flag==0)){
    		continue;
    	}
    	printf("[%d]", counter);
		if((stat=='T')){
			printf(" Stopped ");
		}
		else if((stat!='1')&&(r_flag==0)){
			printf(" Running ");
    	}
    	printf("%s", temp->name);
    	printf("[%d]\n", temp->pid);
    	temp=temp->next;
    }


	return;
}