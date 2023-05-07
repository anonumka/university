#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <limits.h>
#include <signal.h>

int msgid;

struct msgbuf
{
    long msgtype;
    int msgdata;
} message;

int get_message_queue()
{
    // создать очередь сообщений
    msgid = msgget(IPC_PRIVATE, IPC_CREAT | 0666);

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

int *allocate_array(int n)
{
	int *arr = malloc(sizeof(int) * n);
	return arr;
}

void change_array(int* arr, int start, int end)
{
    for (size_t i = start; i < end; i++)
        {
            if (arr[i] < 0)
            {
                arr[i] = 1;
            }
            else if(arr[i] > 0)
            {
                arr[i] = 0;
            }
        }
}

int count_elements_array(int* arr, int start, int end, int flag)
{
    int count = 0;
    for (size_t i = start; i < end; i++)
    {
        if (arr[i] == flag)
        {
            count = count + 1;
        }
        
    }
    return count;
}

void print_array(int *arr, int n) 
{
    for (size_t i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void set_reliable_signal(int signum, void(*sighandler)(int))
{
    struct sigaction act;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    act.sa_handler = sighandler;
    sigaction(signum, &act, 0);
}

void recieve_message(int signum)
{
    signal(SIGUSR1, recieve_message);
    msgrcv(msgid, &message, sizeof(struct msgbuf), 1, 0);
    release_message_queue(msgid);
}

void terminated_by_alarm(int signum)
{
    signal(SIGALRM, recieve_message);

    printf("Terminated by alarm\n");
    release_message_queue(msgid);

    exit(EXIT_FAILURE);
}

int main()
{
    int mode = 0;
    printf("Choise a mode:\n1. Non-trust signal\n2. Trust signal\n>> ");
	scanf("%d", &mode);
    if (mode == 1)
        signal(SIGALRM, terminated_by_alarm);
    else
        set_reliable_signal(SIGALRM, terminated_by_alarm);

    int n, time_alarm;

    FILE *ist = fopen("lab7.txt", "r");
    fscanf(ist, "%d %d", &n, &time_alarm);
    alarm(time_alarm);

    int *arr = allocate_array(n);
    for (int i = 0; i < n; i++) {
        fscanf(ist, "%d", &arr[i]);
    }

    int flag;
    printf("Find 0 or 1? ");
	scanf("%d", &flag);

    fclose(ist);

    printf("\nSize of array: %d\n", n);
    printf("\nOriginal array: \n");
    print_array(arr, n);

    change_array(arr, 0, n);

    printf("\nChanged array: \n");
    print_array(arr, n);

    get_message_queue();

    if (fork() == 0)
    {
        message.msgtype = 1;
        message.msgdata = count_elements_array(arr, 0, n, flag);
        msgsnd(msgid, &message, sizeof(struct msgbuf), 0);

        sleep(1);
        kill(getppid(), SIGUSR1);

        exit(EXIT_SUCCESS);
    }

    printf("\nFinish!\n");
    if (mode == 1)
        signal(SIGUSR1, recieve_message);
    else
        set_reliable_signal(SIGUSR1, recieve_message);
    
    pause();

    int count = message.msgdata;
    release_message_queue(msgid);
 
    printf("In array %d count of %d\n", count, flag);

    free(arr);
    return EXIT_SUCCESS;
}
