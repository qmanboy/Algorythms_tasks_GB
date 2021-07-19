#include <stdio.h>
#include <malloc.h>
#define T char
#define true 1 == 1
#define false 1 != 1

typedef int bool;

typedef struct Node {
    int dat;
    struct Node *next;
} Node;

typedef struct {
    Node *head;
    int size;
} OneLinkList;

typedef struct TwoLinkNode {
    int dat;
    struct TwoLinkNode *next;
    struct TwoLinkNode *prev;
} TwoLinkNode;

typedef struct {
    struct TwoLinkNode *head;
    struct TwoLinkNode *tail;
    int size;
} TwoLinkList;

int get2dInt(int** array, const int row, const int col) {
    return *((*(array + row)) + col);
}

void initTwoLinkList(TwoLinkList *lst) {
    lst->head = NULL;
    lst->tail = NULL;
    lst->size = 0;
}

bool TwoLinkEnqueue(TwoLinkList *queue, T value) {
    TwoLinkNode *tmp = (TwoLinkNode*) malloc(sizeof(TwoLinkNode));
    if (tmp == NULL) {
        printf("Out of memory! \n");
        return false;
    }
    tmp->dat = value;
    tmp->next = NULL;
    tmp->prev = queue->tail;

    if (queue->tail != NULL) {
        queue->tail->next = tmp;
    }
    if (queue->head == NULL) {
        queue->head = tmp;
    }

    queue->tail = tmp;
    queue->size++;
    return true;
}
T TwoLinkDequeue(TwoLinkList *queue) {
    if (queue->size == 0) {
        printf("Queue is empty \n");
        return -1;
    }
    TwoLinkNode *tmp = queue->head;
    T data = queue->head->dat;

    queue->head = queue->head->next;

    if (queue->head != NULL) {
        queue->head->prev = NULL;
    }
    if (tmp == queue->tail) {
        queue->tail = NULL;
    }

    free(tmp);
    queue->size--;
    return data;
}

void set2dInt(int** array, const int row, const int col, int value) {
    *((*(array + row)) + col) = value;
}
int** init2dIntArray(int** array, const int row, const int col) {
    array = (int**) calloc(sizeof(int*), row);
    for (int i = 0; i < row; ++i) {
        *(array + i) = (int*) calloc(sizeof(int), col);
    }
    return array;
}

typedef struct {
    Node *head;
    int size;
} Stack;

void init(Stack *stack) {
    stack->head = NULL;
    stack->size = 0;
}

bool push(Stack *stack, int value) {
    Node *tmp = (Node*) malloc(sizeof(Node));
    if (tmp == NULL) {
        printf("Stack overflow \n");
        return false;
    }
    tmp->dat = value;
    tmp->next = stack->head;

    stack->head = tmp;
    stack->size++;
    return true;
}

int pop(Stack *stack) {
    if (stack->size == 0) {
        printf("Stack is empty \n");
        return -1;
    }
    Node *tmp = stack->head;
    int data =  stack->head->dat;
    stack->head = stack->head->next;
    free(tmp);
    stack->size--;
    return data;
}

#define sz 6
int id;
int visited[sz];
int neighCount = 0;
int link[sz] = {-1};

void initlinks() {
    for (int i = 0; i < sz; i++) {
        link[i] = -1;
    }
}

void resetArr() {
    for (int i = 0; i < sz; i++) {
        visited[i] = 0;
    }
}

void depthTravers(Stack* stck, int** matrix, int nodNum, int size) {
    //обход в глубину с использованием стека рекурсивно
    printf("%d ", nodNum);
    visited[nodNum] = 1;
    for (int col = 0; col < size; col++) {
        if (matrix[nodNum][col] == 1 && !visited[col] ) {
            if (nodNum == 0 || matrix[col][0] == 1) //подсчет вершин, смежных стартовой
                neighCount++;
            push(stck, col);
            visited[col] = 1;
        }
    }
    if (!stck->size) {
        printf("\nAdjacent vertices> %d", neighCount);
        neighCount = 0;
        resetArr();
        return;
    }
    depthTravers(stck, matrix, pop(stck), size);
}

void halfApp(int **matrix, int index) { //подсчет полузаходов в вершину
    int temp = 0;
    do {
        if (matrix[temp++][index] == 1)
            neighCount++;
    } while (temp < sz);
    link[index] = neighCount; //запись кол-ва полузаходов в массив
    neighCount = 0;
}

void printLinks() { //вывод кол-ва полузаходов в вершины
    for (int i = 0; i < sz; i++)
        if (link[i] > -1)
            printf("\n%d link(s) to vertice %d", link[i], i);
}

void depthTraversTwo(int** matrix, int start, const int size) {
    //обход в глубину
    initlinks();
    Stack *stackTravers = (Stack*) malloc(sizeof(Stack));
    init(stackTravers);
    int siZe = 0;
    do {
        halfApp(matrix, start);
        printf("%d ", start);
        visited[start] = 1;
        for (int col = 0; col < size; col++) {
            if (matrix[start][col] == 1 && !visited[col] ) {
                push(stackTravers, col);
                visited[col] = 1;
            }
        }
        if ((siZe = stackTravers->size) != 0)
            start = pop(stackTravers);
    } while (siZe > 0);
    printLinks();
    resetArr();
}

void clearVisit(int *arr, int size) {
    for (int i=0; i < size; i++)
        arr[i] = 0;
}

void widthTravers(int** matrix, int start, const int size) {
    //обход в ширину
    initlinks();
    TwoLinkList* queue = (TwoLinkList*)malloc(sizeof(TwoLinkList));
    initTwoLinkList(queue);
    int visit[size];
    clearVisit(visit, size);
    TwoLinkEnqueue(queue, start);
    while (queue->size > 0) {
        int indx = TwoLinkDequeue(queue);
        if (visit[indx] == 1) continue;
        visit[indx] = 1;
        printf("%d ", indx);
        halfApp(matrix, indx);
        for (int i = 0; i < size; i++) {
            if ((get2dInt(matrix, indx, i)) == 1 && visit[i] == 0)
                TwoLinkEnqueue(queue,i);
        }
    }
    printLinks();
    resetArr();
}

int maxSearch(int* arr, int size) {
    int max = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i] >= max && arr[i] >= 0) {
            max = link[i];
        }
    }
    return max;
}

void sortPrint(int* arr, const int size) { //Сортировка
    int cnt = 0;
    int max;
    int j = 0;
    int tempArr[size];
    printf("%s", "vert> ");
        while (j < size) {
            max = maxSearch(arr, size);
            if (arr[j] == max && visited[j]) {
                for (int k = j; k < size; k++) {
                    if (arr[k] == max) {
                        printf("%d ", k);
                        tempArr[cnt++] = arr[k];
                        arr[k] = -1;
                    }
                }
                j = 0;
            } else
                j++;
        }
    printf("\n");
    printf("%s", "link> ");
    for (int i = 0; i < cnt; i++)
        printf("%d ", tempArr[i]);
}

void traversMatrix(int** matrix, int size) {
    initlinks();
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (((get2dInt(matrix, i, j)) == 1 || (get2dInt(matrix, j, i)) == 1) && !visited[j]) {
                visited[j] = 1;
                halfApp(matrix, j);
            }
        }
    }
    sortPrint(link, size);
}

int main() {
    const int SZ = sz;
    Stack *st = (Stack*) malloc(sizeof(Stack));
    init(st);

    int** adjacency = init2dIntArray(adjacency, SZ, SZ);
    set2dInt(adjacency, 0, 1, 1);
    set2dInt(adjacency, 0, 3, 1);
    set2dInt(adjacency, 1, 3, 1);
    set2dInt(adjacency, 1, 0, 1);
    set2dInt(adjacency, 1, 5, 1);
    set2dInt(adjacency, 3, 4, 1);
    set2dInt(adjacency, 3, 1, 1);
    set2dInt(adjacency, 5, 3, 1);

    depthTravers(st, adjacency, 0, SZ);
        //обход в глубину через стек рекурсивно, подсчет смежных со стартовой вершин
    printf("\n");

    depthTraversTwo(adjacency, 0, SZ);
        //обход в глубину, подсчет количества ссылок на каждый узел
    printf("\n");

    widthTravers(adjacency, 0, SZ);
        //обход в ширину, подсчет количества ссылок на каждый узел
    printf("\n");

    traversMatrix(adjacency, SZ);
        //обход графа по матрице смежности, вывод списка вершин в порядке убывания ссылок на них

    return 0;
}