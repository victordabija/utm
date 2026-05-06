#include "txt_file.h"
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LEN 1024

static SortDirection direction;
static CompareFunc compare;

int compareWithDirection(const void *a, const void *b) {
    return compare(a, b) * direction;
}

bool createFile(const char *filename) {
    FILE *f = fopen(filename, "w");
    if (!f) {
        return false;
    }

    fclose(f);
    return true;
}

bool appendRecord(const char *filename, const void *record, const ToStringFunc toString) {
    FILE *f = fopen(filename, "a");
    if (!f) {
        return false;
    }

    char buffer[MAX_LINE_LEN];
    toString(record, buffer);
    fprintf(f, "%s\n", buffer);

    fclose(f);
    return true;
}

size_t getCount(const char *filename) {
    FILE *f = fopen(filename, "r");
    if (!f) {
        return 0;
    }

    size_t count = 0;
    int ch;
    while ((ch = fgetc(f)) != EOF) {
        if (ch == '\n') count++;
    }

    fclose(f);
    return count;
}

void *get(const char *filename, size_t *returnCount, const size_t requestedCount, const size_t elementSize,
          const FromStringFunc fromString) {
    FILE *f = fopen(filename, "r");
    if (!f) {
        *returnCount = 0;
        return NULL;
    }

    const size_t totalRecords = getCount(filename);
    const size_t toRead = (requestedCount == 0 || requestedCount > totalRecords) ? totalRecords : requestedCount;

    if (toRead == 0) {
        *returnCount = 0;
        fclose(f);
        return NULL;
    }

    void *dataArray = malloc(toRead * elementSize);
    if (!dataArray) {
        *returnCount = 0;
        fclose(f);
        return NULL;
    }

    char lineBuffer[MAX_LINE_LEN];
    size_t actualRead = 0;

    while (actualRead < toRead && fgets(lineBuffer, MAX_LINE_LEN, f)) {
        lineBuffer[strcspn(lineBuffer, "\r\n")] = 0; // strip newline

        void *targetSlot = (char *) dataArray + (actualRead * elementSize);
        fromString(lineBuffer, targetSlot);

        actualRead++;
    }

    fclose(f);
    *returnCount = actualRead;
    return dataArray;
}

bool modifyRecord(const char *filename, const int index, const void *newData, const ToStringFunc toString) {
    FILE *f = fopen(filename, "r");
    if (!f) return false;

    FILE *temp = fopen("temp.txt", "w");
    if (!temp) {
        fclose(f);
        return false;
    }

    char newString[MAX_LINE_LEN];
    toString(newData, newString);

    char lineBuffer[MAX_LINE_LEN];
    int current = 0;
    bool modified = false;

    while (fgets(lineBuffer, MAX_LINE_LEN, f)) {
        if (current == index) {
            fprintf(temp, "%s\n", newString);
            modified = true;
        } else {
            fputs(lineBuffer, temp);
        }
        current++;
    }

    fclose(f);
    fclose(temp);

    if (modified) {
        remove(filename);
        rename("temp.txt", filename);
        return true;
    }

    remove("temp.txt");
    return false;
}

void *searchRecords(const char *filename, const size_t elementSize, const void *search, const SearchFunc cmp,
                    const FromStringFunc fromString, size_t *returnCount) {
    FILE *f = fopen(filename, "r");
    if (!f) {
        *returnCount = 0;
        return NULL;
    }

    void *results = NULL;
    size_t matchCount = 0;
    void *tempRecord = malloc(elementSize);
    char lineBuffer[MAX_LINE_LEN];

    while (fgets(lineBuffer, MAX_LINE_LEN, f)) {
        lineBuffer[strcspn(lineBuffer, "\r\n")] = 0;
        fromString(lineBuffer, tempRecord);

        if (cmp(tempRecord, search)) {
            matchCount++;
            void *newResults = realloc(results, matchCount * elementSize);
            if (!newResults) {
                free(results);
                free(tempRecord);
                fclose(f);
                return NULL;
            }
            results = newResults;
            memcpy((char *) results + ((matchCount - 1) * elementSize), tempRecord, elementSize);
        }
    }

    free(tempRecord);
    fclose(f);
    *returnCount = matchCount;
    return results;
}

bool sortFile(const char *filename, const size_t elementSize, const CompareFunc cmp, const SortDirection dir,
              const FromStringFunc fromString, const ToStringFunc toString) {
    size_t count;
    void *data = get(filename, &count, 0, elementSize, fromString);

    if (!data || count == 0) {
        free(data);
        return false;
    }

    direction = dir;
    compare = cmp;
    qsort(data, count, elementSize, compareWithDirection);

    FILE *f = fopen(filename, "w");
    char lineBuffer[MAX_LINE_LEN];

    for (size_t i = 0; i < count; i++) {
        toString((char *) data + (i * elementSize), lineBuffer);
        fprintf(f, "%s\n", lineBuffer);
    }

    free(data);
    fclose(f);
    return true;
}

bool deleteRecord(const char *filename, const int index) {
    FILE *f = fopen(filename, "r");
    if (!f) return false;

    FILE *temp = fopen("temp.txt", "w");
    if (!temp) {
        fclose(f);
        return false;
    }

    char lineBuffer[MAX_LINE_LEN];
    int current = 0;

    while (fgets(lineBuffer, MAX_LINE_LEN, f)) {
        if (current != index) {
            fputs(lineBuffer, temp);
        }
        current++;
    }

    fclose(f);
    fclose(temp);

    remove(filename);
    rename("temp.txt", filename);
    return true;
}

bool deleteFile(const char *filename) {
    return remove(filename) == 0;
}
