#ifndef UTM_APPLICATION_H
#define UTM_APPLICATION_H

#include <stdbool.h>
#include <stdnoreturn.h>

void clear();

void clearBuffer();

int readInt(const char *prompt, int min, int max);

double readDouble(const char *prompt, double min, double max);

void readString(const char *prompt, char *dest, int min, int max);

bool isValidDate(const char *date);

void readDate(const char *prompt, char *dest, const char *minDate, const char *maxDate);

void getCurrentDate(char *today);

noreturn void throw(const char *text, int code);

#endif //UTM_APPLICATION_H
