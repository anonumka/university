#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

#define SERVER_PATH "/tmp/server"

int main()
{ 
	int sd,num; //sd – дескриптор сокета
	char buf[256]; //для посылки и получения данных
	struct sockaddr_un serveraddr;
	sd = socket(AF_UNIX, SOCK_STREAM, 0);
	if (sd<0) 
	{ 
		fprintf(stdout, "Невозможно создать сокет\n");
		return 0;
	} 

	memset(&serveraddr, 0, sizeof(serveraddr));
    serveraddr.sun_family = AF_UNIX;
    strcpy(serveraddr.sun_path, SERVER_PATH);

	int rc = connect(sd, (struct sockaddr *)&serveraddr, SUN_LEN(&serveraddr));
	if (rc < 0)
	{
		perror("connect() failed");
		return 1;
	}

	
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
