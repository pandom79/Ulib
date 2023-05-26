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
