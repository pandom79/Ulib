/*
(C) 2021 by Domenico Panella <pandom79@gmail.com>

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License version 3.
See http://www.gnu.org/licenses/gpl-3.0.html for full license text.
*/

#ifndef UHASHTABLE_H
#define UHASHTABLE_H

#include "../ulib.h"

/** @struct HtEntry
 *  @brief This structure represents an hash entry which is an array of HtItem structure.
 *  @var HtEntry::htItems
 *  It represents the hash table items array.
 */
typedef struct {
    Array *htItems;
} HtEntry;

/** @struct HtItem
 *  @brief This structure represents an hash item.
 *  @var HtItem::key
 *  It represents the hash item key.
 *  @var HtItem::value
 *  It represents the hash item value.
 *  @var HtItem::releaseFn
 *  It represents a generic pointer to release function.
 */
typedef struct {
    char *key;
    void *value;
    void (*releaseFn)(void **);
} HtItem;

#endif // UHASHTABLE_H
