#include "parser.h"
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

/* Разбирает строку вида "12 + 3" на два числа и оператор.
   Возвращает 1 при успехе, 0 при ошибке. */
int readExpression(const char* line, double* a, double* b, char* op) {
    char buf[256];
    int i = 0, j = 0;

    /* Убираем пробелы */
    while (line[i] && j < 255) {
        if (!isspace((unsigned char)line[i])) buf[j++] = line[i]; //если это не пробел
        i++;
    }
    buf[j] = '\0'; //метка конца, т.к. собирали строку вручную

    if (buf[0] == '\0') return 0; //пустая строка

    int pos = -1;
    for (int k = 1; buf[k]; k++) { //пока символ не '\0', т.е не 0, т.е. не ложь
        if (strchr("+-*/^", buf[k])) { pos = k; break; }
    }
    if (pos == -1) return 0;

    *op = buf[pos];
    buf[pos] = '\0';

    char* end = NULL;
    *a = strtod(buf, &end); //записываем адрес символа, где остановился после перевода из строки числа.
    if (end == buf) return 0;

    *b = strtod(&buf[pos + 1], &end);
    if (end == &buf[pos + 1]) return 0;

    return 1;
}
