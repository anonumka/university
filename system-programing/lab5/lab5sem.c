#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/wait.h>

// Выделение памяти разделяемой памяти
void *get_shared_memory(int size, int *out_shared_memory_id)
{
	*out_shared_memory_id = shmget(IPC_PRIVATE, size, IPC_CREAT|0666);

	if (*out_shared_memory_id < 0)
	{
		fprintf(stdout, "\nError. Can not get shared memory.");
		exit(EXIT_FAILURE);
	}
	return shmat(*out_shared_memory_id, NULL, 0);
}

// Освобождение выделенной разделяемой памяти
void release_shared_memory(int shared_memory_id, void* addr)
{
	shmdt(addr);
	struct shmid_ds info;
	shmctl(shared_memory_id, IPC_RMID, &info);
}

void print_ipcs_memory_table(int shared_memory_id)
{
    char command[100];
    snprintf(command, 100, "ipcs -m -i %d", shared_memory_id);
    system(command);
}

void print_ipcs_semaphore_table(int semaphore_id)
{
    char command[100];
    snprintf(command, 100, "ipcs -s -i %d", semaphore_id);
    system(command);
}

int get_semaphore()
{
    //создать группу семафоров, состоящую из одного семафора
    int semaphore_id = semget(IPC_PRIVATE, 1, IPC_CREAT|0666);

    //если не удалось создать группу семафоров, завершить выполнение
    if (semaphore_id < 0)
    {
        printf("\nError. Can not get semaphore ID.");
        return 0;
    }

    return semaphore_id;
}

void release_semaphore(int semaphore_id)
{
    // удалить семафор с индексом 0 в группе с id = semaphore_id
    semctl(semaphore_id, 0, IPC_RMID);
}

// Выделение памяти для одномерного массива типа строк
char **allocate_array(int n)
{
	char **arr = malloc(sizeof(char*) * n);
    for (size_t i = 0; i < n; i++)
    {
        arr[i] = malloc(40 * sizeof(char));
    }
    
	return arr;
}

void string_to_array(char string[255], char** array, int n)
{
    char* buf = strtok(string, " ");
    for (size_t i = 0; i < n; i++)
    {
        array[i] = buf;
        buf = strtok(NULL, " ");
    }
}

void print_array(char** array, int n)
{
    printf("Array strings: \n");
    for (size_t i = 0; i < n; i++)
    {
        printf("%s\n", array[i]);
    }
    printf("\n");
}

int count_words(char string[255])
{
    int count = 1;
    for (size_t i = 0; i < strlen(string) - 1; i++)
    {
        if ( (string[i] == ' ') && (string[i + 1] != ' ') )
        {
            count = count + 1;
        }
        
    }
    return count;
}

int check_palindrom(char* word)
{
    int len_pal = 0;
    int tmp_len = strlen(word);
    for(int i = 0; i < tmp_len/2; ++i)
	{
		if(word[i] == word[tmp_len-i-1])
		{
			len_pal = len_pal + 1;
		}
        else
        {
            break;
        }
	}
    if (len_pal != 0)
    {
        return tmp_len;
    }
    return 0;
}

int main()
{
    FILE* ist = fopen("input_sem.txt", "r");
	char input_string[255];
	fgets(input_string, 255, ist);
    fclose(ist);
    printf("Input string: %s\n", input_string);

    int n = 0;
    n = count_words(input_string);
    char **arr_strings = allocate_array(n);
    string_to_array(input_string, arr_strings, n);
    print_array(arr_strings, n);

    int semaphore_id = get_semaphore();
    print_ipcs_semaphore_table(semaphore_id);
    int shared_memory_id;
    int *arr_len_str = get_shared_memory(sizeof(int) * n, &shared_memory_id);

    for (int i = 0; i < n; i++)
    {
        if(fork() == 0)
        {
            arr_len_str[i] = check_palindrom(arr_strings[i]);
            struct sembuf plus_1 = {0, 1, 0}; //операция прибавляет единицу к семафору с индексом 0
            semop(semaphore_id, &plus_1, 1);
            exit(EXIT_SUCCESS);
        }
    }
    print_ipcs_semaphore_table(semaphore_id);

    struct sembuf minus_alphabet_length = {0, -n, 0};
    semop(semaphore_id, &minus_alphabet_length, 1);
    print_ipcs_semaphore_table(semaphore_id);
    release_semaphore(semaphore_id);
    print_ipcs_semaphore_table(semaphore_id);

    int max_ind = -1;
    int max_len = 0;
    for (size_t i = 0; i < n; i++)
    {
        if ((arr_len_str[i] != 0) && (arr_len_str[i] > max_len))
        {
            max_ind = i;
            max_len = arr_len_str[i];
        }
    }

    release_shared_memory(shared_memory_id, arr_len_str);
    print_ipcs_memory_table(shared_memory_id);
    
    if (max_ind != -1) {
        printf("Palindrom with %d len is %s\n", max_len, arr_strings[max_ind]);
    }
    else {
        printf("Palindrom not founded\n");
    }

    free(arr_strings);
    return 0;
}