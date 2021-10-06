#include "Header.h"
#include "customCd.h"

void customRedirect(char *in_text){

	char str1[1000];
	char str2[1000];
	int counter = 0;
	int i=0;
	while(in_text[i]!='|'){
		str1[counter++] = in_text[i++];
	}
	str1[counter] = '\0';
	printf("%s\n", str1);
	// strcpy(str1, temp);
	counter = 0;
	i++;
	while(in_text[i]!='\0'){
		str2[counter++] = in_text[i++];
	}
	str2[counter] = '\0';
	printf("%s\n", str2);
	
	// remove initial spaces from str2
	while((str2[0]==' ') || (str2[0]=='\t')){
		for
	}


	return;
}