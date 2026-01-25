#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdnoreturn.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>

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

void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
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

        clearBuffer();

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

        clearBuffer();

        if (value < min || value > max) {
            printf("Value out of range.\n");
            continue;
        }
        return value;
    }
}

void readString(const char *prompt, char *dest, const int min, const int max) {
    char temp[1024];

    while (1) {
        printf("%s (%d-%d chars): ", prompt, min, max);

        if (fgets(temp, sizeof(temp), stdin) == NULL) continue;

        // Remove the trailing newline character added by fgets
        temp[strcspn(temp, "\n")] = '\0';

        const size_t len = strlen(temp);

        if (len < (size_t) min) {
            printf("Error: Input too short. Minimum is %d.\n", min);
            continue;
        }

        if (len > (size_t) max) {
            printf("Error: Input too long. Maximum is %d.\n", max);
            continue;
        }

        strcpy(dest, temp);

        break;
    }
}

bool isValidDate(const char *dateStr) {
    if (strlen(dateStr) != 10) return false;

    // Format Check (Dashes at index 4 and 7)
    for (int i = 0; i < 10; i++) {
        if (i == 4 || i == 7) {
            if (dateStr[i] != '-') return false;
        } else {
            if (!isdigit(dateStr[i])) return false;
        }
    }

    int y, m, d;
    if (sscanf(dateStr, "%d-%d-%d", &y, &m, &d) != 3) return false;

    if (m < 1 || m > 12) return false;
    if (d < 1 || d > 31) return false;

    if ((m == 4 || m == 6 || m == 9 || m == 11) && d > 30) return false;

    if (m == 2) {
        const bool isLeap = y % 4 == 0;
        if (d > (isLeap ? 29 : 28)) return false;
    }

    return true;
}

void readDate(const char *prompt, char *dest, const char *minDate, const char *maxDate) {
    while (1) {
        readString(prompt, dest, 10, 10);

        if (!isValidDate(dest)) {
            printf("Error: Invalid date logic. Please use YYYY-MM-DD.\n");
            continue;
        }

        // strcmp(a, b) > 0 means a is later than b
        // strcmp(a, b) < 0 means a is earlier than b
        if (strcmp(dest, minDate) < 0) {
            printf("Error: Date is too early. Minimum allowed is %s.\n", minDate);
            continue;
        }

        if (strcmp(dest, maxDate) > 0) {
            printf("Error: Date is too late. Maximum allowed is %s.\n", maxDate);
            continue;
        }

        break;
    }
}

void getCurrentDate(char *today) {
    const time_t t = time(NULL);
    const struct tm *tm_info = localtime(&t);

    // strftime formats the time into our YYYY-MM-DD string
    // %Y = Year, %m = Month, %d = Day
    strftime(today, 11, "%Y-%m-%d", tm_info);
}

noreturn void throw(const char *text, const int code) {
    printf("%s \n", text);
    exit(code);
}
