#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <limits.h>
#include <linux/sched.h>

//
typedef struct Node
{
    int value;
    struct Node *next;
} Node;

// Глобальные переменные
Node **arr_nodes;
int count = 0;
int index_nodes = -1;

// Функция добавления узла
void node_add(Node** head, int value)
{
	Node* tmp = (Node*)malloc(sizeof(Node));
	tmp->value = value;
	tmp->next = (*head);
	(*head) = tmp;
}

// Чтение односвязного списка
void read_array(FILE *ist, Node **arr, int n)
{
	for (size_t i = 0; i < n; i++)
	{
		Node* head = (Node*)malloc(sizeof(Node));
        int k;
        fscanf(ist, "%d", &k);
        for (size_t j = 0; j < k; j++)
        {
            int tmp_value;
            fscanf(ist, "%d", &tmp_value);
            node_add(&head, tmp_value);
        }
        arr[i] = head;
	}
}

// Выделение памяти под массив узлов
Node **allocate_array(int n)
{
	Node **arr = malloc(sizeof(Node*) * n);
	return arr;
}

// Освобождение памяти для двумерного массива
void free_array(Node **arr, int n)
{
    for (size_t i = 0; i < n; i++)
    {
        Node* head = arr[i];
        while (head->next)
        {
            Node * prev = NULL;
            prev = head;
            head = head->next;
            free(prev);
        }
        free(head);
    }
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

// Подсчет количества положительных чисел в односвязном списке
void get_count_pos_num_node(void* param)
{
	int n = *(int *)param;
	const Node* head = arr_nodes[n];
	int tmp_count = 0;
	while (head->next)
	{
		if (head->value > 0) {
			tmp_count = tmp_count + 1;
		}
		head = head->next;
	}

	if (tmp_count > count)
	{
		count = tmp_count;
		index_nodes = n;
	}

}

// Вывод односвязного списка
void print_node_list(int i)
{
	const Node* head = arr_nodes[i];
	while (head->next)
	{
		printf("%d ", head->value);
		head = head->next;
	}
	printf("\n");
}

int main()
{
	// Открытие файла и запись размеров массива
	FILE* ist = fopen("inputb.txt", "r");
	int n;
	fscanf(ist, "%d", &n);
	
	// Создание и запись массива А
	arr_nodes = allocate_array(n);
	read_array(ist, arr_nodes, n);
	fclose(ist);

	int stack[1000];
	int param[1];

	// Создание n потоков
	for (size_t i = 0; i < n; i++)
	{
		param[i] = i;
		clone(get_count_pos_num_node, (void*)(stack+1000-1), CLONE_VM|CLONE_VFORK, param+i);
	}
	
	// Вывод массивов
	printf("All nodes: \n");
	for (size_t i = 0; i < n; i++)
	{
		print_node_list(i);
	}
	printf("\nMaximum count is %d, index array nodes is %d\n", count, index_nodes);
	print_node_list(index_nodes);
	
	free_array(arr_nodes, n);

	return 0;
}
