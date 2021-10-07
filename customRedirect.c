#include "Header.h"
#include "customCd.h"

void customRedirect(char *in_text){

	char str1[1000];
	char str2[1000];
	int counter = 0;
	int pre_counter = 0;
	int post_counter = 0;
	int i=0;
	while(in_text[i]!='|'){
		str1[counter++] = in_text[i];
		if( (in_text[i]!=' ') && (in_text[i]!='\t') ){
			pre_counter++;
		}
		i++;
	}
	str1[counter] = '\0';
	counter = 0;
	i++;
	while(in_text[i]!='\0'){
		str2[counter++] = in_text[i];
		if( (in_text[i]!=' ') && (in_text[i]!='\t') ){
			post_counter++;
		}
		i++;
	}
	str2[counter] = '\0';

	// return error if there is no command before/after the |
	if(pre_counter==0){
		printf("piping: Enter a Command before the '|'\n");
		return;
	}
	if(post_counter==0){
		printf("piping: Enter a Command after the '|'\n");
		return;
	}

	// remove initial spaces from str2
	while((str2[0]==' ') || (str2[0]=='\t')){
		for(int j=1;j<strlen(str2);j++){
			str2[j-1] = str2[j];
		}
		str2[strlen(str2)-1] = '\0';
	}

	printf("%s\n", str1);
	printf("%s\n", str2);

	return;
}