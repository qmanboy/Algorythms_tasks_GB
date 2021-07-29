#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <ctype.h>

int calcTempId(int key, int from, int to, char str_i, int sz) { //расчет значения из алфавита
    int temId;
    if (key < 0) {
        if ((str_i + key) > to)
            temId = from + ((str_i + key) % sz);
        else if ((str_i + key) < from)
            temId = (to + 1) - ((from - (str_i + key)) % sz);
        else
            temId = (str_i + key);
    }
    else
        temId = from + (((str_i + key) % (to + 1)) - from);
    if (temId < from && key > 0) temId +=from;
    return temId;
}

void caesarCrypt(char* str, int key) { //шифрование цезаря
    int tempId;
    int k = 0;
    const int size = 26;
    for (int j = 0; str[j] != '\0'; j++) {
        if (isalpha(str[j])) {
            if (islower(str[j]))
                tempId = calcTempId(key,97 ,122, str[j], size);
            else
                tempId = calcTempId(key,65 ,90, str[j], size);
            str[k++] = (char)tempId;
        }
    }
    str[k] = '\0';
}

void caesarEncrypt(char* str, int key) { //дешифрование Цезаря
    caesarCrypt(str, 0 - key);
}

int lenStr(char *str) { //подсчет длины строки
    int len = 0;
    for (int i = 0; str[i] != '\0'; i++)
        len++;
    return len;
}

char* copyStr(char* str , int len) { //копирование строки
    int k = 0;
    char* st = (char*) malloc(len);
    for (int c = 0; str[c] != '\0'; c++) {
        if (!(isalpha(str[c])))
            continue;
        st[k++] = str[c];
    }
    return st;
}

void reShuffleCrypt(char* str, int key) { //шифрование по количеству столбцов
    int k = 0;
    int len = lenStr(str);
    char* st = copyStr(str, len); //создание новой строки из букв переданной
    int lenSt = lenStr(st);
    int firstLenSt = lenSt;
    if ((lenSt % key) != 0) //если длина новой строки не кратна ключу, сделать кратной
        lenSt += (key - (lenSt % key));

    for (int i = firstLenSt; i < lenSt; i++) //заполнение недостающих символов рандомными буквами
        st[i] = (char)(97 + (rand() % 26));
    st[lenSt] = '\0';

    for (int j = 0; j < key; j++) { //заполнение переданной строки шифрованной последовательностью
        for (int i = j; i < lenSt; i += key) {
            str[k++] = st[i];
        }
    }
    str[k] = '\0';

}

void reShuffleEncrypt(char* str, int key) { //расшифрование по количеству столбцов
    int k = 0;
    int stepIndx = 0;
    int j;
    int len = lenStr(str);
    int newkey = len/key; //определение шага перехода по строке
    char* st = copyStr(str, len);

    for (int i = 0; i < newkey; i++) { //заполнение строки расшифрованной последовательностью
        k = i;
        for (j = stepIndx; k < len; j++) {
            str[j] = st[k];
            k += newkey;
        }
        stepIndx += key;
    }
    str[k] = '\0';
}


int main() {
    int key = 5; // Ключ шифрования
    const char* st = "Christmas Day is one of the most favorite American holidays";
    char* str = (char*) malloc(sizeof(char) * strlen(st));
    strcpy(str, st);
    printf("Original string> %s\n", str);

    caesarCrypt(str, key);
    printf("Caesar crypted(%d)> %s\n", key, str);

    caesarEncrypt(str, key);
    printf("Caesar encrypted > %s\n", str);

    strcpy(str, st);

    reShuffleCrypt(str, key);
    printf("Reshuffle crypted(%d)> %s\n", key, str);

    reShuffleEncrypt(str, key);
    printf("Reshuffle encrypted > %s\n", str);

    return 0;
}