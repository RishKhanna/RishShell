#include "Header.h"
#include "sysCommands.h"

void add_bg(char *in_proc, int in_pid){
	
	struct bg_prc *a = malloc(sizeof(struct bg_prc));
    a = initial;
    while (!(a->next == NULL || a->pid == in_pid)){
        a = a->next;
    }
    
	if( a->pid == in_pid ){
		strcpy(a->name,in_proc);
	}
	else if( a->next == NULL ){
		a->size++;
		a->next = malloc(sizeof(struct bg_prc));
		a = a->next;
		strcpy(a->name,in_proc);
		a->pid = in_pid;
		a->next = NULL;
	}

}

char *find_bg(int in_pid){
    struct bg_prc *a = malloc(sizeof(struct bg_prc));
    a = initial;
    while (a->pid != in_pid){
        a = a->next;
    }
    return a->name;
}

void func(int signum){
    int stat;
    pid_t pid_change;
    while ((pid_change = waitpid((pid_t)(-1), &stat, WNOHANG)) > 0){
        char *na = find_bg(pid_change);
        int exit=WEXITSTATUS(stat);
        fprintf(stderr, "\n%s with pid %d exited with exit code %d\n", na, pid_change, exit);
    }
}



void sysCommands(char *in_text, int bg_flag){

	// remove & from command
	// printf("%s\n",in_text);
	if( bg_flag ){
		in_text[strlen(in_text)-1] = '\0';
	}

	char *wordslist[1024];
	int word_count = 0;
	int char_count = 0;
	char curr_word[1024][1024];
	for(int i=0;i<=strlen(in_text);i++){
		if( in_text[i]!=' '  && in_text[i]!='\0'){
			while( in_text[i]!=' '  && in_text[i]!='\0'){
				curr_word[word_count][char_count++] = in_text[i++];
			}
			curr_word[word_count][char_count] = '\0';
			wordslist[word_count] = curr_word[word_count];
			word_count++;
			char_count = 0;
		}
	}
	wordslist[word_count] = NULL;

	
	int pid = fork();
	if( pid<0 ){
		printf("Could not create new process.\n");
		return;
	}
	else if(pid==0){
		if( bg_flag==1 ){
			setpgid(0, 0);
		}
		if (execvp(wordslist[0], wordslist) < 0){
			printf("%s\n", wordslist[0]);
	        printf("Could not run command.\n");
	        exit(0);
	    }
	}
	else{
		if( bg_flag==1 ){
			setpgid(pid, 0);
			add_bg(wordslist[0], pid);
			signal(SIGCHLD, func);
			return;
		}
		else{
			int stat;
            waitpid(pid, &stat, 0);
            return;
		}
	}

	return;
}