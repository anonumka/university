#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <limits.h>

// Чтение двумерного массива
void read_array(FILE *in, int **arr, int n, int k)
{
	for (size_t i = 0; i < n; i++)
	{
		for (size_t j = 0; j < k; j++)
		{
			fscanf(in, "%d", &arr[i][j]);
		}
	}
}

// Вывод двумерного массива
void print_array_A(int **arr, int n, int k)
{
	printf("Array A:\n");
	for (size_t i = 0; i < n; i++)
	{
		for (size_t j = 0; j < k; j++)
		{
			printf("%5d ", arr[i][j]);
		}
		printf("\n");
	}
}

// Вывод одномерного массива 
void print_array_B(int *arr, int n)
{
	printf("\nArray B:\n");
	for (size_t i = 0; i < n; i++)
	{
		printf("%5d ", arr[i]);
	}
	printf("\n");
}

// Выделение памяти для двумерного массива
int **allocate_array(int n, int k)
{
	int **arr = malloc(sizeof(int *) * n);
	for (size_t i = 0; i < n; i++)
	{
		arr[i] = malloc(sizeof(int) * k);
	}
	return arr;
}

// Освобождение памяти для двумерного массива
void free_array(int **arr, int n)
{
	for (size_t i = 0; i < n; i++)
	{
		free(arr[i]);
	}
	free(arr);
}

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

// Вывод таблица выделенной памяти
void print_ipcs_memory_table(int shared_memory_id)
{
	char command[100];
	snprintf(command, 100, "ipcs -m -i %d", shared_memory_id);
	system(command);
}

// Поиск минимального элемента в строке двумерного массива
int get_min(int **arr, int n, int k)
{
	int min = INT_MAX;
	for (size_t i = 0; i < k; i++)
	{
		if (arr[n][i] < min)
		{
			min = arr[n][i];
		}
	}
	return min;
}

// Поиск максимального элемента в одномерном массиве
int get_max(int *arr, int n)
{
	int max = INT_MIN;
	for (size_t i = 0; i < n; i++)
	{
		if (arr[i] > max)
		{
			max = arr[i];
		}
	}
	return max;
}

int main()
{
	// Открытие файла и запись размеров массива
	FILE* ist = fopen("inputa.txt", "r");
	int n; int k;
	fscanf(ist, "%d %d", &n, &k);
	
	// Создание и запись массива А
	int **arr_a = allocate_array(n, k);
	read_array(ist, arr_a, n, k);
	fclose(ist);

	// Создание разделяемой памяти и вывод информации об выделенном сегменте
	int shared_memory_id;
	int *arr_b = get_shared_memory(sizeof(int) * n, &shared_memory_id);
	printf("Our shared memory segment ID is %d \n", shared_memory_id);
	print_ipcs_memory_table(shared_memory_id);

	// Создание n процессов
	for (size_t i = 0; i < n; i++)
	{
		if (fork() == 0)
		{
			// Нахождение минимального элемента в каждой строчке
			// массива А и запись найденного числа в массив В
			arr_b[i] = get_min(arr_a, i, k);
			return 0;
		}
	}

	// Ожидание выполнения всех процессов
	while (wait(NULL) != -1);
	
	// Вывод массивов
	print_array_A(arr_a, n, k);
	print_array_B(arr_b, n);
	
	// Нахождение и вывод максимального элемента в массиве В
	int max = get_max(arr_b, n);
	printf("\nMaximum element is %d\n", max);

	// Освобождение памяти
	release_shared_memory(shared_memory_id, arr_b);
	free_array(arr_a, n);

	return 0;
}
