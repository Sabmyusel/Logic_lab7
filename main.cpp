#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>

int** G, **matr;
int size2 = 0;

struct node
{
	int inf;  // полезная информация
	struct node* next; // ссылка на следующий элемент 
};

struct node* Shead = NULL, * Slast = NULL;

/* Последовательное добавление в стек элемента (в вершину)*/
void stack_push(int s)
{
	struct node* p = NULL;

	if ((p = (node*)malloc(sizeof(struct node))) == NULL)  // выделяем память под новый элемент списка
	{
		printf("Ошибка при распределении памяти\n");
		exit(1);
	}

	p->inf = s;

	p->next = NULL;

	if (Shead == NULL && p != NULL)	// если списка нет, то устанавливаем голову списка
	{
		Shead = p;
		Slast = p;
	}
	else if (Shead != NULL && p != NULL) // список уже есть, то вставляем в вершину
	{
		p->next = Shead;
		Shead = p;
	}
	return;
}

/* Последовательное удаление из стека (из вершины)*/
int stack_pop() {
	
	if (Shead == NULL) {
		return NULL;
	}
	struct node* sch = Shead->next;

	int in = Shead->inf;
	free(Shead);
	Shead = sch;


	return in;
}

bool stack_len() {
	struct node* sch = Shead->next;
	if (sch == NULL)
		return false;
	else
		return true;
}

int** gen(int size) {
	int temp = 0;
	int** arr;
	arr = new int* [size];
	for (int i = 0; i < size; i++)
		arr[i] = new int[size] {0};

	srand(time(NULL));

	for (int i = 0; i < size; i++)
		for (int k = i + 1; k < size; k++) {
			temp = rand() % 2;
			if(temp == 1)
				temp = rand() % 2;
			arr[i][k] = temp;
			arr[k][i] = temp;
		}
	return arr;
}

void print(int** graph, int size, int var) {

	if (var == 1) {
		printf("   ");
		for (int i = 0; i < size; i++)
			printf(" %d ", i + 1);

		printf("\n    ");
		for (int i = 0; i < size; i++)
			printf("-- ");

		for (int i = 0; i < size; i++) {
			printf("\n %d | ", i + 1);
			for (int k = 0; k < size; k++) {
				printf("%d  ", graph[i][k]);
			}
		}
	}

	if (var == 2) {// 
		size2 = 0;
		for (int i = 0; i < size; i++)
			for (int k = i + 1; k < size; k++)
				if (graph[i][k] == 1)
					size2++;

		matr = new int* [size];
		for (int i = 0; i < size; i++)
			matr[i] = new int[size2] {0};

		size2 = 0;
		for (int i = 0; i < size; i++)
			for (int k = i + 1; k < size; k++)
				if (graph[i][k] == 1) {
					matr[i][size2] = 1;
					matr[k][size2] = 1;
					size2++;
				}

		printf("\n\n");
		for (int i = 0; i < size; i++) {
			printf("%d | ", i + 1);
			for (int k = 0; k < size2; k++) {
				printf("%d  ", matr[i][k]);
			}
			printf("\n");
		}
		printf("\n\n");
	}
}

void DFS(int v, bool *num, int size) {

	if (!num[v]) {
		num[v] = true;
		printf("%d  ", v + 1);

		for (int i = 0; i < size; i++)
			if (G[v][i] == 1 && num[i] == false)
				DFS(i, num, size);
	}
}

void DFS2(int v, bool* num, int size) {

	if (!num[v]) {
		num[v] = true;
		printf("%d  ", v + 1);

		for (int i = 0; i < size2; i++)
			if (matr[v][i] == 1)
				for (int k = 0; k < size; k++)
					if (matr[k][i] == 1 && num[k] == false)
						DFS2(k, num, size);
	}
}

void DFS3(int v, bool* num, int size) {

	stack_push(0);
	stack_push(v);

	while (stack_len()) {
		v = stack_pop();
		if (!num[v]) {
			num[v] = true;
			printf("%d  ", v + 1);

			for (int i = size; i > 0; i--)
				if (G[v][i] == 1 && num[i] == false)
					stack_push(i);
		}
	}
}

void InDep(int size, int type, int v) {

	bool* num = new bool[size] {false};

		switch (type) {
		case 1:
			DFS(v, num, size);
			break;
		case 2:
			DFS2(v, num, size);
			break;
		case 3:
			DFS3(v, num, size);
			break;
		}
}

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int size = 0;
	int k = 1;
	while(1){
		do {
			printf("Введите кол-во вершин графа: ");
			scanf("%d", &size);
		} while (size <= 0);

		G = gen(size);
		print(G, size, 1);
		print(G, size, 2);


		printf("Обход: \n");
		InDep(size, 1, k-1);
		printf("\n\n");

		printf("Обход (по матрице смежности): \n");
		InDep(size, 2, k-1);
		printf("\n\n");

		printf("Обход (без рекурсии): \n");
		InDep(size, 3, k-1);
		printf("\n");

		system("pause");
		system("cls");
	}
	return 0;
}