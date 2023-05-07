#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <limits.h>

struct msgbuf
{
    long msgtype;
    int msgdata;
};

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
    printf("\nChanged array: ");

    for (size_t i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main()
{
    int n;
    printf("Enter size of array: ");
    scanf("%d", &n);

    int *arr = allocate_array(n);
    for (int i = 0; i < n; i++)
    {
        printf("Enter element a[%d] = ", i);
        scanf("%d", &arr[i]);
    }

    int k;
    do
	{
		printf("\nEnter count of threads (2 <= count <= %d): ", n/2);
		scanf("%d", &k);
	}
	while (k < 2 && k > n/2);

    int flag;
    printf("\nFind 0 or 1? ");
	scanf("%d", &flag);
    print_array(arr, n);

    // for (size_t i = 0; i < k; i++) {
    //     if (fork() == 0)
    //     {
    //         int end = (i + 1) * chunk;
    //         if (i == k - 1)
    //         {
    //             end = n;
    //         }
    //         change_array(arr, i * chunk, end);
    //         exit(EXIT_SUCCESS);
    //     }
    // }
    // Ожидание выполнения всех процессов
	// while (wait(NULL) != -1);

    change_array(arr, 0, n);
    print_array(arr, n);
    int chunk = n / k;

    struct msgbuf message;
    int msgid = get_message_queue();

    for (size_t i = 0; i < k; i++) {
        if (fork() == 0)
        {
            int end = (i + 1) * chunk;
            if (i == k - 1)
            {
                end = n;
            }
            int tmp_count = 0;
            tmp_count = count_elements_array(arr, i * chunk, end, flag);

            message.msgtype = i + 1;
            message.msgdata = tmp_count;
            //послать сообщение в очередь
            msgsnd(msgid, &message, sizeof(struct msgbuf), 0);
            exit(EXIT_SUCCESS);
        }
    }
    // Ожидание выполнения всех процессов
	while (wait(NULL) != -1);

    printf("\nFinish!");
    int count = 0;
    for (size_t i = 0; i < k; i++)
    {
        msgrcv(msgid, &message, sizeof(struct msgbuf), i + 1, 0);
        count = count + message.msgdata;
    }
    release_message_queue(msgid);
    printf("\n%d found in array %d\n", count, flag);
    return 0;
}
