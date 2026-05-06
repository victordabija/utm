#ifndef UTM_TXT_FILE_H
#define UTM_TXT_FILE_H

#include <stdbool.h>
#include <stdio.h>
#include "sort.h"

// toString writes the struct's text representation into the provided buffer
typedef void (*ToStringFunc)(const void *record, char *buffer);

// fromString parses the text string and populates the struct
typedef void (*FromStringFunc)(const char *string, void *record);

typedef int (*CompareFunc)(const void *, const void *);

typedef bool (*SearchFunc)(const void *, const void *);

bool createFile(const char *filename);

bool appendRecord(const char *filename, const void *record, ToStringFunc toString);

size_t getCount(const char *filename);

void *get(const char *filename, size_t *returnCount, size_t requestedCount, size_t elementSize,
          FromStringFunc fromString);

bool modifyRecord(const char *filename, int index, const void *newData, ToStringFunc toString);

void *searchRecords(const char *filename, size_t elementSize, const void *search, SearchFunc cmp,
                    FromStringFunc fromString, size_t *returnCount);

bool sortFile(const char *filename, size_t elementSize, CompareFunc compare, SortDirection direction,
              FromStringFunc fromString, ToStringFunc toString);

bool deleteRecord(const char *filename, int index);

bool deleteFile(const char *filename);
#endif //UTM_TXT_FILE_H
