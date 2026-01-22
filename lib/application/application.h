#ifndef UTM_APPLICATION_H
#define UTM_APPLICATION_H

#include <stdnoreturn.h>

void clear();

int readInt(const char *prompt, int min, int max);

double readDouble(const char *prompt, double min, double max);

noreturn void throw(const char *text, int code);

#endif //UTM_APPLICATION_H
