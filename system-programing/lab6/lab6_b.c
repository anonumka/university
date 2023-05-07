#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <limits.h>
#include <string.h>

struct msgbuf
{
    long msgtype;
    int msgdata;
};

int choose()
{
	int choise = 0;
	printf("[PID %d] Выберите режим работы:\n",getpid());
	puts("1. Ввести число");
	puts("2. Умножить введенное число на два");
	puts("3. Вывести результат на экран");
	puts("4. Выход");
	do
	{
		printf(">> ");
		scanf("%i", &choise);
	}
	while (choise < 1 && choise > 4);
	return choise;
}

void doFirst(int msgid)
{
	int st;
	signal(SIGCHLD, SIG_IGN);
	if (fork() == 0)
	{
		int num;
		printf("Enter number: ");
		scanf("%d", &num);
		
		struct msgbuf message;
		message.msgtype = 1;
    	message.msgdata = num;
    	msgsnd(msgid, &message, sizeof(struct msgbuf), 0);
	}
	wait(&st);
}

void doSecond(int msgid)
{
	int st;
	signal(SIGCHLD, SIG_IGN);
	if (fork() == 0)
	{
		struct msgbuf message;
		msgrcv(msgid, &message, sizeof(struct msgbuf), 1, 0);
		int get_num = message.msgdata;
		get_num = get_num * 2;
		
		message.msgtype = 2;
		message.msgdata = get_num;
		msgsnd(msgid, &message, sizeof(struct msgbuf), 0);
	}
	wait(&st);
}

void doThird(int msgid)
{
	int st;
	signal(SIGCHLD, SIG_IGN);
	if (fork() == 0)
	{
		struct msgbuf message;
		msgrcv(msgid, &message, sizeof(struct msgbuf), 2, 0);
    	int getting_num = message.msgdata;
    	printf("Number equal %d\n", getting_num);
	}
	wait(&st);
}

int get_message_queue()
{
    // создать очередь сообщений
    int msgid = msgget(IPC_PRIVATE, IPC_CREAT | 0666);

    //если не удалось создать очередь сообщений, завершить выполнение
    if (msgid < 0) {
        fprintf(stdout, "\nError");
        return 0;
    }

    return msgid;
}

void release_message_queue(int message_queue_id)
{
    struct msqid_ds info;
    msgctl(message_queue_id, IPC_RMID, &info);
}

int main()
{
    int msgid = get_message_queue();
	while (1)
	{
		int choise = choose();
		switch(choise)
		{
			case 1:
			doFirst(msgid);
			break;
			case 2:
			doSecond(msgid);
			break;
			case 3:
			doThird(msgid);
			break;
			default:
			return 0;
		}
	}

	return 0;

    release_message_queue(msgid);
}
