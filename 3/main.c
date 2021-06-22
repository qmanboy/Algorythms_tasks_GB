#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void DectoBin(int num) {
    if (num/2 == 1) {
        printf("%d",(num/2));
    } else
        DectoBin(num/2);
        printf("%d",(num % 2));
}

int degree(int num, int deg) {
    if (deg == 1)
        return num;
    return num * degree(num, deg-1);
}

int newdegree(int num, int deg) {
    if (deg % 2 == 0) {
        if (deg == 2)
            return num;
        return (num*num) * newdegree((num*num), deg/2);
    } else
        degree(num, deg);
}
void routes(int x, int y) {
     //инициализация и вывод массива препятсвий
        int k = 0;
        int bar[x][y];
        for (int j = 0; j < y; j++) {
            srand(time(NULL));
            for (int i = 0; i < x; i++) {
                if (i == 0 && j == 0)
                    bar[i][j] = 0;
                else {
                    bar[i][j] = rand() % 2;
                    if ((bar[i][j] == 1) && (k < 4))
                        k++;
                    else bar[i][j] = 0;
                }
                printf("%5d", bar[i][j]);
            }
            printf("\n");
        }
        printf("\n");
        int arr[x][y];
        for (int i = 0; i < x; ++i) {
            for (int j = 0; j < y; ++j) {
                    if (i == 0 && j == 0)
                        arr[i][j] = 0;
                    else if (i == 0 ^ j == 0) {
                        if (bar[i][j] == 0)
                            arr[i][j] = 1;
                        else {
                            if (i == 0)
                                for (int z = j; z < y;z++) {
                                    arr[0][z] = 0;
                                    bar[0][z] = 1;
                                }
                            else
                                for (int z = i; z < x;z++) {
                                    arr[z][0] = 0;
                                    bar[z][0] = 1;
                                }

                        }
                    }
                        else if (bar[i][j] == 0)
                            arr[i][j] = arr[i][j - 1] + arr[i - 1][j];
                        else arr[i][j] = 0;
            }
        }
        for (int j = 0; j < y; j++) { //вывод маршрутов
            for (int i = 0; i < x; i++) {
                printf("%5d", arr[i][j]);
            }
            printf("\n");
        }
}

int main() {
    DectoBin(14);
    printf("\n");
    printf("%d", degree(5,4));
    printf("\n");
    printf("%d", newdegree(5,4));
    printf("\n");
    routes(5,5);
    return 0;
}

