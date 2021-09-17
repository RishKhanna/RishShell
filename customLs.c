#include "Header.h"
#define MAX(a,b) (((a)>(b))?(a):(b))

void print_with_l(char *in_text){
	// printf("%s ",in_text);
	struct stat buffer;
	stat(in_text, &buffer);

	// print the directories and permissions stuff
	if (S_ISDIR(buffer.st_mode))
        printf("d");
    else
        printf("-");
    if (buffer.st_mode & S_IRUSR)
        printf("r");
    else
        printf("-");
    if (buffer.st_mode & S_IWUSR)
        printf("w");
    else
        printf("-");
    if (buffer.st_mode & S_IXUSR)
        printf("x");
    else
        printf("-");
    if (buffer.st_mode & S_IRGRP)
        printf("r");
    else
        printf("-");
    if (buffer.st_mode & S_IWGRP)
        printf("w");
    else
        printf("-");
    if (buffer.st_mode & S_IXGRP)
        printf("x");
    else
        printf("-");
    if (buffer.st_mode & S_IROTH)
        printf("r");
    else
        printf("-");
    if (buffer.st_mode & S_IWOTH)
        printf("w");
    else
        printf("-");
    if (buffer.st_mode & S_IXOTH)
        printf("x");
    else
    	printf("-");

    printf("%*ld", 4, buffer.st_nlink);
    
    uid_t uid = buffer.st_uid;
    struct passwd *temp1;
    temp1 = getpwuid(uid);
    printf("%*s", 15, temp1->pw_name);
    
    gid_t gid = buffer.st_gid;
    struct group *temp2;
    temp2 = getgrgid(gid);
    printf("%*s", 15, temp2->gr_name);

	long int size = buffer.st_size;
	printf("%*ld", 8, size);


	time_t now;
	time(&now);
	struct tm *tm = localtime(&(buffer.st_ctime));
	int then_month = tm->tm_mon;
	int then_date = tm->tm_mday;
	char with_time[20];
	char with_year[20];
	strftime(with_year, 20, "%b %e  %Y", tm);
	strftime(with_time, 20, "%b %e %R", tm);
	struct tm *now_info = localtime(&now);
	if (now_info->tm_mon - then_month > 6)
		printf(" %s", with_year);
	else if (now_info->tm_mon - then_month == 6){
		if (now_info->tm_mday > then_date)
			printf(" %s", with_year);
		else
			printf(" %s", with_time);
	}
	else
		printf(" %s", with_time);

	return;
}

void  printlsstuff(int a_check, int l_check, char *path, int num_paths){

	// printf("a :%d\nd :%d\npath :%s\n\n", a_check, l_check, path);
	if (num_paths){
		printf(":\n");
	}
	int dir_flag = 0;
	struct stat buffer;
	int exist = stat(path, &buffer);
	if( exist == -1 ){
		printf("ls: %s cannot be accessed: No such file/directory.\n", path);
		return;
	}
	else{
		// it can be accessed, now to check if it's a dir or a file
		if( S_ISDIR(buffer.st_mode) ){
			dir_flag = 1;
			// to check if the dir be acessed
			int read_acc = access( path, R_OK );
			if(read_acc == -1){
				printf("ls: %s cannot be accessed: Read permission denied.\n", path);
				return;
			}
		}
	}

	char ls_list[1024][2024];
	int ls_list_counter = 0;
	if( dir_flag ){
		struct dirent **entry;
		int count = scandir(path, &entry, NULL, alphasort);
		for(int i=0; i<count;i++){
			strcpy(ls_list[ls_list_counter++], entry[i]->d_name);
		}
	}
	else{
		strcpy(ls_list[0], path);
		ls_list_counter = 1;
	}

	char path_and_file[PATH_MAX];
	strcpy(path_and_file, path);
	path_and_file[strlen(path)] = '/';
	path_and_file[strlen(path)+1] = '\0';
	int str_count = strlen(path_and_file);

	if( (a_check==0) && (l_check==0)){
		for( int i=0; i<ls_list_counter; i++ ){
			if( ls_list[i][0] != '.' ){
				printf("%s  ", ls_list[i]);
			}
		}
		printf("\n");
	}
	else if( (l_check==0)){
		for( int i=0; i<ls_list_counter; i++ ){
			printf("%s  ", ls_list[i]);
		}
		printf("\n");
	}
	else if( a_check == 0 ){
		for(int i=0;i<ls_list_counter;i++){
			if( ls_list[i][0] != '.' ){
				for(int j=0;j<=strlen(ls_list[i]);j++){
					path_and_file[str_count++] = ls_list[i][j];
				}
				print_with_l(path_and_file);
				printf("  %s\n", ls_list[i]);
				str_count = strlen(path) + 1;
			}
		}
	}
	else{
		for(int i=0;i<ls_list_counter;i++){
			for(int j=0;j<=strlen(ls_list[i]);j++){
				path_and_file[str_count++] = ls_list[i][j];
			}
			print_with_l(path_and_file);
			printf("  %s\n", ls_list[i]);
			str_count = strlen(path) + 1;
		}
	}


	if(num_paths){
		printf("\n");
	}
	return;
}

void customLs(char *in_text, char *home_dir){

	// CHECKING FLAGS
	int a_check=0, l_check=0, wrong_flag = 0;
	for(int i=0;i<strlen(in_text);i++){
		if (in_text[i]=='-'){
			if( in_text[i+1]=='l' ){
				l_check = i+1;
				if (in_text[i+2]=='a')
					a_check = i+2;
				else if ((in_text[i+2]!=' ') && (in_text[i+2]!='\t') && (in_text[i+2]!='\0'))
					wrong_flag = 1;
			}
			else if( in_text[i+1]=='a' ){
				a_check = i+1;
				if (in_text[i+2]=='l')
					l_check = i+2;
				else if ((in_text[i+2]!=' ') && (in_text[i+2]!='\t') && (in_text[i+2]!='\0'))
					wrong_flag = 1;
			}
			else{
				wrong_flag = 1;
			}
		}
	}

	if (wrong_flag){
		printf("Please Enter the flags of the ls command properly.\n");
		return;
	}

	// extract path if there is any
	int max_index = MAX(MAX(1,a_check), MAX(1,l_check)) + 1;
	// printf("%d\n", max_index);
	for(int i=max_index;i<=strlen(in_text);i++){
		in_text[i - max_index] = in_text[i];
	}
	// printf("after max index:%s\n", in_text);
	int start = 0;
	int end = strlen(in_text);
	for (int i = 0; i < strlen(in_text); i++){
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

	// printf("path list:%s\n",in_text);
	// WE WILL NOW LOOP THROUGHT THE PATHS AND PRINT THEM 
	// ONE BY ONE USING THE PRINTLS FUNCTION
	char path_curr[PATH_MAX];
	path_curr[0] = '\0';
	int path_curr_pointer = 0;
	int num_spaces = 0;
	int num_spaces_flag = 0;
	if( start>=end ){
		getcwd(path_curr, PATH_MAX);
		printlsstuff(a_check, l_check, path_curr,num_spaces--);
		return;
	}
	for(int i=0; i<strlen(in_text);i++){
		if( in_text[i]==' ' && ( (in_text[i+1]>='a' && in_text[i+1]<='z') || (in_text[i+1]>='A' && in_text[i+1]<='Z')  ||
				(in_text[i+1]=='.') || (in_text[i+1]=='/') || (in_text[i+1]=='~')) ){
			printf("Hello");
			num_spaces++;
			num_spaces_flag = 1;
		}
	}
	for(int i=0; i<=strlen(in_text)+1; i++){

		if(  in_text[i]=='~' ){
			if (num_spaces_flag){
				printf("~");
			}
			for(int j=0;j<strlen(home_dir);j++){
				path_curr[path_curr_pointer++] = home_dir[j];
			}
		}
		else if( (in_text[i]==' ') || (in_text[i]=='\0') ){
			if (strlen(path_curr)){
				if( (num_spaces==0) && (num_spaces_flag==1) ){
					printf(":\n");
				}
				printlsstuff(a_check, l_check, path_curr, num_spaces--);
			}
			else
				continue;
			path_curr[0] = '\0';
			path_curr_pointer = 0;
		}
		else{
			if(num_spaces_flag){
				printf("%c", in_text[i]);
			}
			path_curr[path_curr_pointer++] = in_text[i];
			path_curr[path_curr_pointer] = '\0';
		}
	}


	return;
}