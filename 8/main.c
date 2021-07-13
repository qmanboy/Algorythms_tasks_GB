#include <stdio.h>
#include <malloc.h>
#include <time.h>
#define true 1 == 1
#define false 1 != 1

typedef int bool;

typedef struct Node {
    int key;
    struct Node *left;
    struct Node *right;
} TreeNode;

TreeNode* treeInsert(TreeNode *t, int data) { //вставка в дерево
    TreeNode *newNode;
    newNode = (TreeNode *) malloc(sizeof(TreeNode));
    newNode->key = data;
    newNode->left = NULL;
    newNode->right = NULL;
    TreeNode *current = t;
    TreeNode *parent = t;
    if (t == NULL) {
        t = newNode;
    } else {
        while (current->key != data) {
            parent = current;
            if (current->key > data) {
                current = current->left;
                if (current == NULL) {
                    parent->left = newNode;
                    return t;
                }
            } else {
                current = current->right;
                if (current == NULL) {
                    parent->right = newNode;
                    return t;
                }
            }
        }
    }
    return t;
}

void printTree(TreeNode *root) { //скобочная печать дерева
    if (root) {
        printf("%d", root->key);
        if (root->left || root->right) {
            printf("(");
            if (root->left)
                printTree(root->left);
            else
                printf("NULL");
            printf(",");
            if (root->right)
                printTree(root->right);
            else
                printf("NULL");
            printf(")");
        }
    }
}

TreeNode* getSuccessor(TreeNode *node) {
    TreeNode *current = node->right;
    TreeNode *parent = node;
    TreeNode *s = node;

    while(current != NULL) {
        parent = s;
        s = current;
        current = current->left;
    }
    if (s != node->right) {
        parent->left = s->right;
        s->right = node->right;
    }
    return s;
}

bool delete(TreeNode *root, int key) { //удаление элемента из дерева по значению
    TreeNode *current = root;
    TreeNode *parent = root;
    bool isLeftChild = true;

    while (current->key != key) {
        parent = current;
        if (key < current->key) {
            current = current->left;
            isLeftChild = true;
        } else {
            current = current->right;
            isLeftChild = false;
        }
        if (current == NULL)
            return false;
    }

    if (current->left == NULL && current->right == NULL) {
        if (current == root)
            root == NULL;
        else if (isLeftChild)
            parent->left = NULL;
        else
            parent->right = NULL;
    }
    else if(current->right == NULL) {
        if (isLeftChild)
            parent->left = current->left;
        else
            parent->right = current->left;
    }
    else if(current->left == NULL) {
        if (isLeftChild)
            parent->left = current->right;
        else
            parent->right = current->right;
    }
    else {
        TreeNode *successor = getSuccessor(current);
        if (current == root)
            root = successor;
        else if (isLeftChild)
            parent->left = successor;
        else
            parent->right = successor;
        successor->left = current;
    }
    return true;
}

int countTree(TreeNode *tree) { //подсчет количества элементов в дереве
    if (tree == NULL)
        return 0;
    return countTree(tree->right) + countTree(tree->left) + 1;
}

int balanceCheck(TreeNode *tree) { //подсчет кол-ва элементов в поддеревьях и
    if (tree == NULL)              //возврат 1 если разница между ними не более 1
        return -1;
    else {
        if (abs(countTree(tree->left) - countTree(tree->right)) <= 1) {
            return 1;
        }
    }
    return 0;
}

bool binSearch(TreeNode *root, int value) { //рекурсивный бинарный поиск по дереву
    if (root == NULL)
        return false;
    if (root->key == value)
        return true;
    if (value < root->key)
        return binSearch(root->left, value);
    if (value > root->key)
        return binSearch(root->right, value);
}

int main() {
    int balanceCount = 0;
    const int treeCount = 50;
    const int nodeCount = 10000;
    TreeNode* arr[treeCount];
    srand(time(NULL));
    for (int i = 0; i < treeCount; i++) {
        TreeNode *tree = NULL;
        tree = treeInsert(tree, (rand() % nodeCount));
        for (int j = 1; j < nodeCount; j++) {
            treeInsert(tree, (rand() % nodeCount));
        }
        arr[i] = tree;
        balanceCount += balanceCheck(arr[i]);
    }
    printf("BalCount > %d\n", balanceCount);
    printf("Balanced %3.1f%c\n", (((double)balanceCount / (double)treeCount) * 100), '%');
    int val = 0;
    printf("Input your number for search>");
    scanf("%d", &val);
    printf("%s", (binSearch(arr[0], val)) ? "Found" : "Not found");
    return 0;
}