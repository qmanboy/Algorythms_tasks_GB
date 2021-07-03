#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void SwapAr(int *a, int *b) { //Смена местами двух значений
    int buf = *a;
    *a = *b;
    *b = buf;
}

void Qsort (int* arr, int first, int last) { //Быстрая сортировка
    int f = first;
    int l = last;
    int piv = arr[(f + l) / 2];
    while (f <= l) {
        while (arr[f] < piv)
            f++;
        while (arr[l] > piv)
            l--;
        if (f <= l) {
            SwapAr(&arr[f++], &arr[l--]);
        }
    }
    if (first < l)
        Qsort(arr, first, l);
    if (last > f)
        Qsort(arr, f, last);
}

void InSort(int* arr, int n) { //Сортировка вставками
    for (int i = 1; i < n; i++)
        for (int j = i; j > 0 && arr[j - 1] > arr[j]; j--)
            SwapAr(&arr[j - 1], &arr[j]);
}

void BetQsort(int* arr, int first, int last) { //Улучшенная быстрая сортировка
    if ((last+1) > 10) {
        int mid = (first+last)/2;
        int medid;
        if ((arr[first] <= arr[mid]) && (arr[mid] <= arr[last]))
            medid = mid;
        else if ((arr[mid] <= arr[first]) && (arr[first] <= arr[last]))
            medid = first;
        else
            medid = last;
        if (mid != medid)
            SwapAr(&arr[mid], &arr[medid]);
        Qsort(arr, first, last);
    } else
        InSort(arr, (last + 1));
}

void BlockSort(int* arr, int n, int evenlen) { // блочная сортировка четных чисел массива
                                                // evenlen - количество четных чисел в передаваемом массиве
    int* ar = (int*) calloc(sizeof(int), evenlen);
    int id = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] % 2 == 0)
            ar[id++] = arr[i];
    }

    const int max = evenlen;
    const int b = 10;
    int buck[b][max+1];
    for (int i = 0; i < b; i++) {
        buck[i][max] = 0;
    }

    for (int digit = 1; digit < 1000000000; digit*=10) {
        for (int i = 0; i < max; i++) {
            int d = (ar[i] / digit) % b;
            buck[d][buck[d][max]++] = ar[i];
        }
        int idx = 0;
        for (int i = 0; i < b; i++) {
            for (int j = 0; j < buck[i][max]; j++)
                ar[idx++] = buck[i][j];
            buck[i][max] = 0;
        }
    }
    int idn = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] % 2 == 0)
            arr[i] = ar[idn++];
    }
}

int EvenCnt(int* arr, int len) { //подсчет количества четных элементов в массиве
    int count = 0;
    for (int i = 0; i < len; i++)
        if (arr[i] % 2 == 0)
            count++;
    return count;
}

void PrntArr(int* arr, int len) {
    printf("\n");
    for (int i = 0; i < len; i++)
        printf("%3d", arr[i]);
}

int main() {
    const int x = 36;
    int* ar = (int*) calloc(sizeof(int), x);
    srand(time(NULL));
    for (int i = 0; i < x; i++) {
        ar[i] = rand() % 100;
        printf("%3d", ar[i]);
    }

    BlockSort(ar, x, EvenCnt(ar, x));
    PrntArr(ar, x);
    BetQsort(ar, 0, (x-1));
    PrntArr(ar, x);



}
