#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdnoreturn.h>

#include "application.h"

void clear() {
    // \033[H moves cursor to home, \033[2J clears the entire screen
    printf("\033[H\033[2J");

    // Fallback for older Windows Command Prompt or specific environments
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

int readInt(const char *prompt, const int min, const int max) {
    int value;
    while (1) {
        printf("%s", prompt);
        if (min != INT_MIN && max != INT_MAX) printf(" [%d to %d]", min, max);
        else if (min != INT_MIN) printf(" [min %d]", min);
        else if (max != INT_MAX) printf(" [max %d]", max);
        printf(": ");

        if (scanf("%d", &value) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n');
            continue;
        }

        if (value < min || value > max) {
            printf("Value out of range.\n");
            continue;
        }
        return value;
    }
}

double readDouble(const char *prompt, const double min, const double max) {
    double value;
    while (1) {
        printf("%s", prompt);
        if (min != -INFINITY && max != INFINITY) printf(" [%.2f to %.2f]", min, max);
        else if (min != -INFINITY) printf(" [min %.2f]", min);
        else if (max != INFINITY) printf(" [max %.2f]", max);
        printf(": ");

        if (scanf("%lf", &value) != 1) {
            printf("Invalid decimal.\n");
            while (getchar() != '\n');
            continue;
        }

        if (value < min || value > max) {
            printf("Value out of range.\n");
            continue;
        }
        return value;
    }
}

noreturn void throw(const char *text, const int code) {
    printf("%s \n", text);
    exit(code);
}
