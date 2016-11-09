#include "servidor.h"


int main(int argc, char *argv[])
{
	int s, b, l, fd, sa, bytes,bytes2, on = 1;
	int loop=1;

  	char buf[BUF_SIZE];  
  	char buf2[BUF_SIZE];
  	char confirmacion[TAM_MSG];
  	char nombre[90];
  	char opcion[10];

  	struct sockaddr_in channel;  
  	foo=1;

  	if (argc != 2)
  		fatal("Usar : servidor <puerto-servidor>");

	memset(&channel, 0, sizeof(channel));

	channel.sin_family = AF_INET;
	channel.sin_addr.s_addr = htonl(INADDR_ANY);
	channel.sin_port = htons(atoi(argv[1]));
  	
  	puerto_id = socket(PF_INET, SOCK_STREAM, 0);  
	
	if (puerto_id < 0) fatal("falla en socket ");
  	
  	setsockopt(puerto_id, SOL_SOCKET, SO_REUSEADDR, (char *) &on, sizeof(on)); 
    b = bind(puerto_id, (struct sockaddr *) &channel, sizeof(channel));
  	
  	if (b < 0) fatal("falla en bind");
  	
  	l = listen(puerto_id, QUEUE_SIZE);

  	  

  	if ( l < 0 ) fatal("falla en listen");
  	
  	signal(SIGINT, &catch);

  	while (1) {
    	sa = accept(puerto_id, 0, 0);  

      	if (sa < 0) fatal("falla en accept");

      	memset(buf,'\0',sizeof(buf));
      	if (read(sa, buf, BUF_SIZE) != 0)
      	{  
      	
      		memset(nombre,'\0',sizeof(nombre));
			memset(opcion,'\0',sizeof(opcion));
      		recuperar(nombre , opcion ,buf);

      		//printf("%s\n",nombre);
      		//printf("%s\n",opcion );
      		
      		if (strcmp(opcion,"recibir")==0)
      		{
      			printf("responder recibir \n");
      			fd = open(nombre, O_RDONLY);  

      			if (fd < 0) 
      			{
      			   printf("Falla en open\n");
				       memset(confirmacion,'\0',sizeof(confirmacion));
				      strcpy(confirmacion,"Error");
				      write(sa,confirmacion,TAM_MSG);
      			}
      			else
      			{
				      memset(confirmacion,'\0',sizeof(confirmacion));
				      strcpy(confirmacion,"Existe");
				      write(sa,confirmacion,TAM_MSG);
              read(sa,buf,BUF_SIZE);
              
      				while (1) {
						    bytes = read(fd, buf, BUF_SIZE); 
						    if (bytes <= 0) break;  

						    write(sa, buf, bytes);  
					     }	
      			}
				    close(fd);  	
      		
      		}
      		if (strcmp(opcion,"enviar")==0)
      		{
      			remove(nombre);
      			printf("\nRecibiendo %s \n",nombre);

      			strcpy(confirmacion,"El servidor Recibira archivo ahora");

      			write(sa,confirmacion,TAM_MSG);

      			fd = open(nombre,O_WRONLY | O_CREAT, S_IRUSR|S_IWUSR);

      			while (1)
				{
					bytes2 = read (sa, buf2,BUF_SIZE);
					write(fd,buf2,bytes2);
					if (bytes2 <=0 )
					{
						break;
					}
					memset(buf2,'\0',sizeof(buf2));
				}
				close(fd);
				printf("\n%s Recibido con exito \n",nombre);

				memset(confirmacion,'\0',sizeof(confirmacion));
				strcpy(confirmacion,"Servidor Recibio archivo con exito");
				write(sa,confirmacion,TAM_MSG);
      		}
      	}
      	close(sa);
 	}
}