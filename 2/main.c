#include <stdio.h>
#include <stdbool.h>

bool Check(int num) {
    int sum = 0;
    if (num > 1) {
        for (int i = 1; i <= num; i++) {
            if ((num % i) == 0) {
                sum++;
            }
        }
    }
return (sum==2);
}

int main() {
    int numb;
    printf("Type your number >\n");
    scanf("%d", &numb);
    if (Check(numb)) {
        printf("Prime");
    } else {
        printf("Not Prime");
    }
    return 0;
}