#include "servidor.h"

void fatal(char* string)	 
{
	printf("%s\n",string);
	exit(1);
}


void catch(int sig)
{
	if(sig== SIGINT){
		printf("Señal SIGINT: %d atrapada!\n", sig);
		foo = 0;
		close(puerto_id);
		exit(1);
	}else{
		printf("Señal: %d atrapada!\n", sig);
	}
}

void recuperar(char *nombre , char *opcion ,char mensaje[])
{
	int i=0;
	int j=0;


	while(mensaje[i]!=':')
	{
		nombre[i]=mensaje[i];
		i++;
	}
	i++;

	while(i < strlen(mensaje) )
	{
		opcion[j]=mensaje[i];
		i++;
		j++;
	}

}