#ifndef UTM_LIBCAR_H
#define UTM_LIBCAR_H

#include <stdbool.h>
#include "sort.h"

#define FIRST_CAR_MADE_DATE "1885-01-01"
#define SEARCH_STRING_LIMIT 50

typedef struct {
    char model[50];
    char country[30];
    char manufacturingDate[11];
    int enginePower;
    double cost;
} Car;

/* READ/WRITE */
void displayCar(Car car, int index);

void displayHeader();

Car *readCar();

typedef int (*CompareFunction)(const Car *, const Car *);

typedef bool (*SearchFunction)(const Car *, const void *search);

typedef enum {
    BY_MODEL,
    BY_COUNTRY,
    BY_DATE,
    BY_POWER,
    BY_COST,
} CompareType;

typedef struct {
    CompareType type;
    CompareFunction function;
} CompareMethod;

typedef struct {
    CompareType type;
    SearchFunction function;
} SearchMethod;

typedef struct {
    char search[SEARCH_STRING_LIMIT];
    SearchFunction function;
    CompareType type;
} SearchQuery;

typedef struct {
    CompareFunction function;
    CompareType type;
    SortDirection direction;
} SortQuery;

int compareByModel(const Car *a, const Car *b);

int compareByCountry(const Car *a, const Car *b);

int compareByDate(const Car *a, const Car *b);

int compareByPower(const Car *a, const Car *b);

int compareByCost(const Car *a, const Car *b);

bool matchByModel(const Car *record, const void *search);

bool matchByCountry(const Car *record, const void *search);

SearchQuery getSearchQuery();

SortQuery getSortQuery();

char *getLabelByCompareType(CompareType type, bool capitalize);

void carToString(const void *record, char *buffer);

void carFromString(const char *string, void *record);

/**
 * void pointer, cause it may be a callback to various functions
 */
void freeCar(void *record);

#endif //UTM_LIBCAR_H
