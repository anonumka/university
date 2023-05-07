#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <time.h>
#include <sys/un.h>

#define SERVER_PATH "/tmp/server"

void write_result(char* buf, int player, int enemy, int i)
{
	strcpy(buf, "");

	if (player)
		strcat(buf, "Вы: белый шар\n");
	else
		strcat(buf, "Вы: черный шар\n");

	if (enemy)
		strcat(buf, "Противник: белый шар\n");
	else
		strcat(buf, "Противник: черный шар\n");

	if (player == enemy)
		strcat(buf, "Результат: ничья\n");
	else if (player)
		strcat(buf, "Результат: победа\n");
	else
		strcat(buf, "Результат: поражение\n");

	if (player || enemy || i == 2)
	{
		strcat(buf, "Конец игры\n");
	}
	else
	{
		strcat(buf, "Следующий раунд\n");
	}
}

int main()
{ 
	int sd,ns ; //sd – дескриптор сокета

	struct sockaddr_un serveraddr;
	unlink(SERVER_PATH);
	
	sd = socket(AF_UNIX, SOCK_STREAM, 0);
	if (sd<0)
	{
		fprintf(stdout,"Невозможно создать сокет ");
		return 0;
	} 
	else 
		fprintf(stdout,"Сокет создан ");

	memset(&serveraddr, 0, sizeof(serveraddr));
	serveraddr.sun_family = AF_UNIX;
	strcpy(serveraddr.sun_path, SERVER_PATH);

	int rc = bind(sd, (struct sockaddr *)&serveraddr, SUN_LEN(&serveraddr));
	if (rc < 0)
	{
		perror("bind() failed\n");
		return 0;
	}

	int res = listen(sd,2);
	if ( res < 0 )
	{
		fprintf(stdout,"\nОшибка вызова listen");
		return 0;
	}
	fprintf(stdout,"\nСервер запущен");
	
	int sd1 = 0, sd2 = 0;
	char buf[256] ; //для посылки и получения данных

	while(1)
	{
		int pid;
		socklen_t addrlen; //для получения размера адреса клиента
		sd1 = accept(sd, NULL, NULL);
		sd2 = accept(sd, NULL, NULL);
		
		// Оба клиента подключились
		if (sd1 > 0 && sd2 > 0)
		{
			// Инициализация
			srand(time(NULL));
			int box[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
			for (int i = 0; i < 2; i++)
			{
				int tmp_i = rand() % 8;
				box[tmp_i] = 1;
			}
			fprintf(stdout, "\nЯщик состоит из:\n");
			for (int i = 0; i < 8; i++)
			{
				printf("%d ", box[i]);
			}
		
			// Информирование клиентов о готовности сервера
			fprintf(stdout,"\nОба клиента подключились к серверу. Игра начинается!\n");
			int num;
			char buf2[80];
			sprintf(buf2,"Ready");
			num=send(sd1,buf2,sizeof(buf2),0);
			if (num<0)
			{
				fprintf(stdout,"\nОшибка записи ");
				return 0;
			}
			num=send(sd2,buf2,sizeof(buf2),0);
			if (num<0)
			{
				fprintf(stdout,"\nОшибка записи ");
				return 0;
			}

			// Дочерний процесс осуществляет коммуникации с клиентами
			pid=fork();
			if (pid<0)
			{
				fprintf(stdout,"\nНевозможно создать процесс");
				continue;
			}
			if (pid==0)
			{
				int num;
				close(sd); //дочернему процессу не нужен дескриптор sd
				
				// Игра
				for (int i = 0; i < 3; i++)
				{
					// Получение игроками "шаров"
					int first_player = box[i];
					int second_player = box[i+1];

					// Вывод информации на сервер
					fprintf(stdout,"Раунд №%d\nИгрок 1: %d\nИгрок 2: %d\n", i+1, first_player, second_player);

					// Рассылка информации игрокам
					char buf3[256];
					write_result(buf3, first_player, second_player, i);
					send(sd1,buf3,sizeof(buf3),0);
					write_result(buf3, second_player, first_player, i);
					send(sd2,buf3,sizeof(buf3),0);
					
					// Условия окончания игры
					if (first_player || second_player || i == 2)
					{
						fprintf(stdout,"Игра окончена\n");
						strcpy(buf, "End");
						send(sd1,buf,sizeof(buf),0);
						send(sd2,buf,sizeof(buf),0);
						return 1;
					}
				}
				return 1;
			}
			
			close(sd1); //родительскому процессу не нужен дескриптор sd1
			close(sd2); //родительскому процессу не нужен дескриптор sd2
			return 1;
		}
	}
	unlink(SERVER_PATH);
	return 1;
}

