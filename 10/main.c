#include <stdio.h>
#include <malloc.h>
#include <math.h>

int hash(char* str) {
    int i = 0;
    unsigned int sum = 0;
    while (str[i] != '\0') {
        sum += (int)str[i++];
    }
    return sum;
}

char* inputStr() {
    char* str = (char*) malloc(sizeof(char));
    printf("Input your string>");
    gets(str);
    return str;
}

int profitCalculation(int* coin, int num, const int size) {
    int cnt = 0;
    int amount = 0;
    for (int i = 0; amount != num; i++) {
        while ((amount + coin[i]) <= num) {
            amount += coin[i];
            printf("%d ", coin[i]);
            cnt++;
        }
    }
    return cnt;
}

int main() {
    printf("Hash> %d\n", hash(inputStr()));

    const  int N = 6;
    int coin[] = {100, 50, 10, 5, 2, 1};

    printf("\nNumber of coins> %d", profitCalculation(coin, 97, N));
    return 0;
}