#include "Header.h"

void customEcho(char *in_text){

	if(strlen(in_text)==4){
		printf("\n");
		return;
	}

	char final_out[strlen(in_text)];
	int counter = 0;
	for(int i=5;i<=strlen(in_text);i++){
		if ((in_text[i]==' ')  ||  (in_text[i]=='	')){
			if ((final_out[counter-1]!=' ')  && counter!=0)
				final_out[counter++] = ' ';
		}
		else{
			final_out[counter++] = in_text[i];
		}
	}
	final_out[counter] = '\0';
	if( strcmp(final_out," ")==0 ){
		printf("\n");
		return;
	}
	printf("%s\n", final_out);
	return;
}