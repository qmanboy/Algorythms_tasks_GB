#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define sz 7
#define SIZE 10

typedef struct {
    int prior;
    int dat;
} Node;

Node* arr[sz];
int emptycnt;
int items;

int cursor = -1;
int Stack[SIZE];

void init() {
    for (int i = 0; i < sz; i++)
        arr[i] = NULL;
    emptycnt = 0;
    items = 0;
}

void ins(int pr, int dat) {
    Node *node = (Node*) malloc(sizeof(Node));
    node->dat = dat;
    node->prior = pr;

     if (items == sz) {
        printf("%s \n", "Queue is full");
        printf("No place for (%d, %d) \n",pr, dat);
        return;
    } else {
         arr[items++] = node;
     }
}

int MaxPr() {
    int max = 0;
    for (int i = 0 ; i < sz; i++) {
        if (arr[i] != NULL)
            if (arr[i]->prior > max)
                max = arr[i]->prior;
    }
    return max;

}

Node* rem() {
    int id = 0;
    int idx = 0;
    int del = 0;
    int max = MaxPr();
    if (items == 0)
        return NULL;
    else {
        for (id = 0; id < sz; id++) {
            if (arr[id] != NULL) {
                if (arr[id]->prior == max) {
                    items--;
                    Node *tmp = arr[id];
                    del = ((sz - (++emptycnt % (sz - id))) - id);
                    for (int j = 0; j < del; j++) {
                        idx = id + 1;
                        while ((idx > 0) && (idx < sz)) {
                            if (arr[idx + j] != NULL) {
                                arr[id + j] = arr[idx + j];
                                arr[idx + j] = NULL;
                                idx = 0;
                            } else if ((idx + j) == (sz - 1)) {
                                arr[id + j] = NULL;
                                idx = 0;
                            } else
                                idx++;
                        }
                    }
                    return tmp;
                }
            }
        }
    }
}

void printQueue() {
    printf("[ ");
    for (int i = 0; i < sz; i++)
        if (arr[i] == NULL)
            printf("(*, *)");
        else
            printf("(%d, %d) ", arr[i]->prior, arr[i]->dat);
    printf("]\n");
}

void insert(int amnt) {
    srand(time(NULL));
    for (int i = 0; i < amnt; i++) {
        int pr = rand() % 10;
        int dat = rand() % 100;
        ins(pr, dat);
    }
}

void remov(int amnt){
    for (int i = 0; i < amnt; i++) {
        Node* n = rem();
        if (n != NULL)
            printf("%d remove: pr = %d, dat = %d \n", (i+1), n->prior, n->dat);
    }
}

void push(int num) {
    if (cursor < SIZE)
        Stack[++cursor] = num;
     else
    printf("\nStack overflow");
}

int pop() {
    if (cursor != -1)
        return Stack[cursor--];
    else {
        printf("Stack is empty");
        return -1;
    }
}

void DecToBin(int num){
    printf("%d\n",num);
    int idx = 0;
     do {
        push(num % 2);
        num /=2;
        idx++;
    } while (num > 0);
    while (idx > 0) {
        printf("%d",pop());
        idx--;
    }
    printf("\n");
}



int main() {
    DecToBin(7);
    init();
    insert (8);
    printQueue();
    remov(10);
    printQueue();
    insert(10);
    printQueue();

}
