#ifndef UTM_SORT_H
#define UTM_SORT_H
#include <stdbool.h>

typedef enum {
    ASCENDING = 1,
    DESCENDING = -1,
} SortDirection;

char *getLabelByDirection(SortDirection direction, bool capitalize);

#endif //UTM_SORT_H
