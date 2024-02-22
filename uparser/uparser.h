/*
(C) 2021 by Domenico Panella <pandom79@gmail.com>

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License version 3.
See http://www.gnu.org/licenses/gpl-3.0.html for full license text.
*/

#ifndef UPARSER_H
#define UPARSER_H

#include "../ulib.h"

#define NO_SECTION -1

/* Generic Errors */
typedef enum {
    FIRST_CHARACTER_ERR = 0,
    UNRECOGNIZED_ERR = 1,
    OCCURRENCES_ERR = 2,
    PROPERTY_SECTION_ERR = 3,
    ACCEPTED_VALUE_ERR = 4,
    DUPLICATE_VALUE_ERR = 5,
    REQUIRED_VALUE_ERR = 6,
    NUMERIC_ERR = 7,
    EMPTY_VALUE_ERR = 8
} ErrorsEnum;

typedef struct {
    ErrorsEnum errorEnum;
    const char *desc;
} ErrorsData;

/* Functions */
char *checkKeyVal(char *key, char *value, int numLine, SectionData **, PropertyData **);

#endif // UPARSER_H
