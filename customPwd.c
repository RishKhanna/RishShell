#include "Header.h"

void customPwd(void){
	char pwd[PATH_MAX];
    getcwd(pwd, PATH_MAX);
    printf("%s\n", pwd);	
	return;
}