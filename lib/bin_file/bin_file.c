#include "bin_file.h"
#include "sort.h"

#include <stdlib.h>
#include <string.h>

static SortDirection direction;
static CompareFunc compare;

int compareWithDirection(const void *a, const void *b);

bool createFile(const char *filename) {
    FILE *f = fopen(filename, "wb");

    if (!f) {
        return false;
    }

    fclose(f);
    return true;
}

bool appendRecord(const char *filename, const void *record, const size_t elementSize) {
    FILE *f = fopen(filename, "ab");

    if (!f) {
        return false;
    }

    fwrite(record, elementSize, 1, f);
    fclose(f);
    return true;
}

size_t getCount(const char *filename, const size_t elementSize) {
    FILE *f = fopen(filename, "rb");
    if (!f) {
        return 0;
    }

    const long currentPosition = ftell(f);

    if (fseek(f, 0, SEEK_END)) {
        return 0;
    }

    const long fileSize = ftell(f);

    fseek(f, currentPosition, SEEK_SET);

    return fileSize / elementSize;
}

/**
 * Get first `requestedCount` of elements.
 * If 0 is set as `requestedCount` then return all elements.
 */
void *get(const char *filename, size_t *returnCount, const size_t requestedCount, const size_t recordSize) {
    FILE *f = fopen(filename, "rb");
    if (!f) {
        return NULL;
    }

    const long currentPosition = ftell(f);
    fseek(f, 0, SEEK_END);
    const long endPosition = ftell(f);
    fseek(f, currentPosition, SEEK_SET); // Return to where we were initially

    const size_t bytesRemaining = (size_t) (endPosition - currentPosition);
    const size_t maxElements = bytesRemaining / recordSize;

    // get all elements if requested is 0 of more than we actually have
    const size_t toRead = (requestedCount == 0 || requestedCount > maxElements) ? maxElements : requestedCount;

    if (toRead == 0) {
        *returnCount = 0;
        return NULL;
    }

    void *buffer = malloc(toRead * recordSize);
    if (!buffer) return NULL;

    const size_t actualRead = fread(buffer, recordSize, toRead, f);
    *returnCount = actualRead;

    if (actualRead == 0) {
        free(buffer);
        return NULL;
    }

    return buffer;
}

bool modifyRecord(const char *filename, const size_t size, const int index, const void *newData) {
    FILE *f = fopen(filename, "r+b");
    if (!f) return false;

    fseek(f, (long) (index * size), SEEK_SET);
    fwrite(newData, size, 1, f);
    fclose(f);
    return true;
}

void *searchRecords(const char *filename, const size_t elementSize, const void *search, const SearchFunc compare,
                    size_t *returnCount) {
    FILE *f = fopen(filename, "rb");
    if (!f) {
        printf("HERE FAILS");
        *returnCount = 0;
        return NULL;
    }

    void *results = NULL;
    size_t matchCount = 0;
    void *tempRecord = malloc(elementSize);

    while (fread(tempRecord, elementSize, 1, f) == 1) {
        if (compare(tempRecord, search)) {
            matchCount++;

            void *newResults = realloc(results, matchCount * elementSize);
            if (!newResults) {
                free(results);
                free(tempRecord);
                fclose(f);
                return NULL;
            }
            results = newResults;

            char *dest = (char *) results + ((matchCount - 1) * elementSize);
            memcpy(dest, tempRecord, elementSize);
        }
    }

    free(tempRecord);
    fclose(f);
    *returnCount = matchCount;
    return results;
}

// wrapper around compare function.
// qsort doesn't offer a direction parameter and modifying compare functions to have one inline is not an option for me.
int compareWithDirection(const void *a, const void *b) {
    return compare(a, b) * direction;
}

bool sortFile(const char *filename, const size_t elementSize, const CompareFunc cmp, SortDirection dir) {
    FILE *f = fopen(filename, "rb");
    if (!f) {
        return false;
    };

    fseek(f, 0, SEEK_END);
    const long count = (long) (ftell(f) / elementSize);
    rewind(f);

    void *data = malloc(count * elementSize);
    fread(data, elementSize, count, f);
    fclose(f);

    direction = dir;
    compare = cmp;

    qsort(data, count, elementSize, compareWithDirection);

    f = fopen(filename, "wb");
    fwrite(data, elementSize, count, f);
    fclose(f);
    free(data);

    return true;
}

bool deleteRecord(const char *filename, const size_t size, const int index) {
    FILE *f = fopen(filename, "rb");
    if (!f) {
        return false;
    }

    FILE *temp = fopen("temp.bin", "wb");
    void *buffer = malloc(size);

    int current = 0;

    while (fread(buffer, size, 1, f)) {
        if (current != index) fwrite(buffer, size, 1, temp);
        current++;
    }

    fclose(f);
    fclose(temp);

    free(buffer);

    remove(filename);
    rename("temp.bin", filename);
    return true;
}

bool deleteFile(const char *filename) {
    return remove(filename) == 0;
}
