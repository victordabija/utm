#ifndef UTM_BIN_FILE_H
#define UTM_BIN_FILE_H

#include <stdbool.h>
#include <stdio.h>

typedef int (*CompareFunc)(const void *, const void *);
typedef bool (*SearchFunc)(const void *, const void *);

bool createFile(const char *filename);

bool appendRecord(const char *filename, const void *record, size_t elementSize);

size_t getCount(const char *filename, size_t elementSize);

void *get(const char *filename, size_t *returnCount, size_t requestedCount, size_t recordSize);

bool modifyRecord(const char *filename, size_t size, int index, const void *newData);

void *searchRecords(const char *filename, size_t elementSize, const void *search, SearchFunc compare, size_t *returnCount);

/**
 * @fixme
 */
void sortFile(const char *filename, size_t size, CompareFunc cmp);

void deleteRecord(const char *filename, size_t size, int index);

void deleteFile(const char *filename);

#endif //UTM_BIN_FILE_H
