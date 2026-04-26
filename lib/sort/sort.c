#include "sort.h"

#include <ctype.h>
#include <string.h>

char *getLabelByDirection(const SortDirection direction, bool capitalize) {
    static char label[10];
    strcpy(label, direction == ASCENDING ? "ascending" : "descending");

    if (capitalize) {
        label[0] = (char) toupper(label[0]);
    }

    return label;
}
