#include "storage.h"
#include "parser.h"
#include "operations.h"
#include <stdio.h>
#include <string.h>

static void saveHistory(const char* historyPut, const char* line, double result) {
    FILE* f = fopen(historyPut, "a"); //дозапись в конец
    if (!f) return;
    fprintf(f, "%s = %.10g\n", line, result);
    fclose(f);
}

static void showHistory(const char* historyPut) {
    FILE* f = fopen(historyPut, "r");
    if (!f) { printf("(pusto)\n"); return; }
    char buf[256];
    while (fgets(buf, sizeof(buf), f)) printf("%s", buf);
    fclose(f);
}

void runCalculator(const char* historyPut) {
    char line[256];
    while (1) {
        printf("\nVvedite virazenie (naprimer, 12 + 3), istoriya - \"h\", vihod - \"q\":\n> ");
        if (!fgets(line, sizeof(line), stdin))
            break;
        line[strcspn(line, "\n")] = '\0'; //убрать невидимый символ; strcspn - находит

        if (strcmp(line, "q") == 0) //strcmp - сравнивает
            break;
        if (strcmp(line, "h") == 0) { showHistory(historyPut); continue; }

        double a, b;
        char op;
        if (!readExpression(line, &a, &b, &op)) { //вход в parser
            printf("Oshibka\n");
            continue;
        }

        int ok;
        double r = calculate(a, b, op, &ok); //вход в operations
        if (!ok) { printf("Math oshibka (delenie ili nevernaya stepen)\n"); continue; }

        printf("= %.10g\n", r);
        saveHistory(historyPut, line, r);
    }
}
