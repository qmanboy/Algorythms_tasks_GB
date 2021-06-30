#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void BubSort(int** arr, int row, int col) {
    int buf;
    int z;
    int x;
    int j;
    int amnt;
    for (int k = 0; k < (row * col); k++) {
        amnt = 0;
        for (int i = 0; i < row; i++) {
            x = i;
            j = 0;
            while ((j < col) && (amnt < ((row * col) - 1))) {
                z = j;
                if (j == (col-1)) {
                    x += 1;
                    z = 0;
                }
                else
                    z += 1;
                if ((*((*(arr + i)) + j)) > (*((*(arr + x)) + z))) {
                    buf = *((*(arr + i)) + j);
                    *((*(arr + i)) + j) = *((*(arr + (x)) + (z)));
                    *((*(arr + (x)) + (z))) = buf;
                }
                j++;
                amnt ++;
            }
        }
    }
}

void PrintArr(int** arr, const int row,const int col) {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++)
            printf("%2d", *((*(arr + i)) + j));
        printf("\n");
    }
}

void TPK() {
    int k = 0;
    const int sz = 11;
    int arr[sz];
    for (int i = 0; i < sz; i++) {
        printf("Input %d number >", (i+1));
        scanf("%d", &arr[i]);
    }
    for (int i = (sz - 1); i >= 0; i--) {
        k = sqrt(fabs(arr[i])) + 5 * pow(arr[i], 3);
        if (k <= 400)
            printf("%5d %5d\n", arr[i], k);
        else
            printf("%5d Too large!\n", arr[i]);

    }

}

int main() {
    const int r = 3;
    const int c = 3;
    int** a;
    a = (int**) calloc(sizeof(int*), r);
    for (int i = 0; i < r; i++)
        (*(a + i)) = (int*) calloc(sizeof(int), c);
    a[0][0] = 1;
    a[0][1] = 9;
    a[0][2] = 2;
    a[1][0] = 5;
    a[1][1] = 7;
    a[1][2] = 6;
    a[2][0] = 4;
    a[2][1] = 3;
    a[2][2] = 8;
    //PrintArr(a, r, c);
    //BubSort(a, r, c);
    //printf("\n");
    //PrintArr(a, r, c);
    //printf("\n");
    TPK();

}
