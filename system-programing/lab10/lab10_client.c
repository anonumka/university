#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#define PORT 1125 

int main()
{ 
	int sd,num; //sd – дескриптор сокета
	char buf[256]; //для посылки и получения данных
	sprintf(buf,"Привет!");
	struct sockaddr_in saddr; //адрес сервера
	bzero(&saddr, sizeof(saddr)); //очистить адрес
	saddr.sin_family = AF_INET;
	saddr.sin_port = PORT;
	saddr.sin_addr.s_addr = INADDR_ANY;//клиент и сервер выполняются на одной машине
	sd=socket(AF_INET, SOCK_STREAM, 0);
	if (sd<0) 
	{ 
		fprintf(stdout, "Невозможно создать сокет\n");
		return 0;
	} 
	if ( connect(sd, (struct sockaddr *)&saddr, sizeof(saddr)) < 0 )
	{
		fprintf(stdout,"Невозможно установить соединение с сервером\n");
		return 0;
	} 
	else
		fprintf(stdout,"Успешное подключение к серверу\n");
		
	// Ожидание второго клиента
	int ready = 0, flag = 0;
	num = recv(sd,buf,60,0);
	while (1)
	{
		
		if (strcmp(buf, "Ready") == 0)
		{
			fprintf(stdout,"Оба клиента готовы к игре. Начинаем!\n");
			ready = 1;
		}

		if (ready)
		{
			num=recv(sd,buf,sizeof(buf),0);
			if (num<0)
			{
				fprintf(stdout,"\nСоединение прервано\n");
				return 0;
			}
			else if (strcmp(buf, "End") == 0)
			{
				return 1;
			}
			else 
				fprintf(stdout,"%s",buf);
		}
	}
	
	return 1;
}
