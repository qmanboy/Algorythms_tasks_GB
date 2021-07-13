#include <stdio.h>
#include <malloc.h>
#include <string.h>
#define T char
#define true 1 == 1
#define false 1 != 1

#define checkelemnt(x,y,z) ((str[i] == x) || (str[i] == y) || (str[i] == z))

#define compare(instack,instring) ((str[i] == instring) && (stack->head->dat == instack))


typedef int bool;

typedef struct Node {
    T dat;
    struct Node *next;
} Node;

typedef struct Nodelist {
    int dat;
    struct Nodelist *next;
} Nodelist;

typedef struct {
    Nodelist* head;
    int size;
} List;

void ins(List* list, int data) {
    Nodelist *new = (Nodelist*) malloc(sizeof(Nodelist));
    new->dat = data;
    new->next = NULL;

    Nodelist* current = list->head;
    if (current == NULL) {
        list->head = new;
        list->size++;
        return;
    } else {
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new;
        list->size++;
    }
}

Nodelist* remov(List* list, int data) {
    Nodelist* current = list->head;
    Nodelist* parent = NULL;
    if (current == NULL)
        return NULL;
    while (current->next != NULL && current->dat != data) {
        parent = current;
        current = current->next;
    }
    if (current->dat != data)
        return NULL;
    if (current == list->head) {
        list->head = current->next;
        list->size--;
        return current;
    }
    parent->next = current->next;
    list->size--;
    return current;

}

void initlist(List* list) {
    list->head = NULL;
    list->size = 0;
}

typedef struct {
    Node *head;
    int size;
} Stack;

void init(Stack *stack) {
    stack->head = NULL;
    stack->size = 0;
}

bool push(Stack *stack, T value) {
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

T pop(Stack *stack) {
    if (stack->size == 0) {
        printf("Stack is empty \n");
        return -1;
    }
    Node *tmp = stack->head;
    T data =  stack->head->dat;
    stack->head = stack->head->next;
    free(tmp);
    stack->size--;
    return data;
}

void printNodelist(Nodelist *n) {
    if (n == NULL) {
        printf("[]");
        return;
    }
    printf("[%d]", n->dat);
}

void printList(List *list) {
    Nodelist *current = list->head;
    if (current == NULL) {
        printNodelist(current);
    } else {
        do {
            printNodelist(current);
            current = current->next;
        } while (current != NULL);
    }
    printf(" Size: %d \n", list->size);
}

bool copyList(List *list1, List *list2) {
    Nodelist *current = list1->head;
    if (current == NULL)
        return false;
    do {
        ins(list2, current->dat);
        current = current->next;
    } while (current != NULL);
    printf("Copy is completed\n");
    return true;
}

bool checkSort(List *list) {
    int count = 0;
    Nodelist *current = list->head;
    Nodelist *current2 = list->head;
    if (current == NULL)
        return false;
    while (current->next != NULL) {
        current = current->next;
        if (current2->dat < current->dat) {
            count++;
            current2 = current2->next;
        }
    }
    if (count == (list->size) - 1)
        return true;
    else
        return false;
}

bool check(T* str, int size, Stack *stack) {
    int i = 0;
    while (i < size) {
        if (checkelemnt('(','{','['))
            push(stack, str[i]);
        else
            while (i < size) {
                if (stack->size != 0) {
                    if ((compare('(', ')')) || (compare('{', '}')) || (compare('[', ']'))) {
                        pop(stack);
                        break;
                    } else if (i == size - 1)
                        return false;
                }
                if (checkelemnt('(','{','[')) {
                    i--;
                    break;
                } else if (checkelemnt(')', '}', ']')) {
                    return false;
                }
                i++;
            }
            i++;
    }
    if (stack->size != 0)
        return false;
    return true;
}


int main() {
    Stack *st = (Stack*) malloc(sizeof(Stack));
    init(st);
    T* str = "2 (+ 5 (-1)[8-10]{1,2,3.4})";
    printf("String> %s\n", str);
    int i = 0;
    int cnt = 0;
    while (str[i++] != '\0') {
        cnt++;
    }
    printf("Result> %d\n", check(str, cnt, st));

    List *lst = (List*) malloc(sizeof(List));
    List *lst2 = (List*) malloc(sizeof(List));
    initlist(lst);
    initlist(lst2);
    ins(lst, 1);
    ins(lst, 2);
    ins(lst, 3);
    ins(lst, 4);
    printf("List1> ");
    printList(lst);

    printf("Check Sort> %d\n", checkSort(lst));

    copyList(lst,lst2);

    printf("List1> ");
    printList(lst);
    printf("List2> ");
    printList(lst2);
    return 0;
}