#include <sys/types.h>  
/* Éste es el código del servidor */
#include <sys/fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>

#define TAM_MSG 100
#define BUF_SIZE 4096  
#define QUEUE_SIZE 10

int puerto_id;
int foo;



void fatal(char* string);
void catch(int sig);
void recuperar(char *nombre , char *opcion ,char mensaje[]);