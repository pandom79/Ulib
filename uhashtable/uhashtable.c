/*
(C) 2021 by Domenico Panella <pandom79@gmail.com>

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License version 3.
See http://www.gnu.org/licenses/gpl-3.0.html for full license text.
*/

#include "uhashtable.h"

static int
hash(int capacity, const char* key)
{
    assert(capacity > 0);
    assert(key && !stringEquals(key, ""));
    int bucketIdx = 0, factor = 31;
    int len = strlen(key);
    for (int i = 0; i < len; i++) {
        bucketIdx = ((bucketIdx % capacity) + (((int)key[i]) * factor) % capacity) % capacity;
        factor = ((factor % __INT16_MAX__) * (31 % __INT16_MAX__)) % __INT16_MAX__;
    }
    return bucketIdx;
}

static HtItem*
htItemNew(Ht *ht, const char *key, void *value)
{
    assert(key && !stringEquals(key, ""));
    assert(ht);
    HtItem *htItem = calloc(1, sizeof(HtItem));
    assert(htItem);
    htItem->key = stringNew(key);
    htItem->value = value;
    htItem->releaseFn = ht->releaseFn;
    return htItem;
}

static void
htItemRelease(HtItem **htItem)
{
    if (*htItem) {
        objectRelease(&(*htItem)->key);
        void (*releaseFn)(void **) = (*htItem)->releaseFn;
        if (releaseFn)
            (*releaseFn)(&(*htItem)->value);
        objectRelease(htItem);
    }
}

static HtEntry*
htEntryNew()
{
    HtEntry *htEntry = calloc(1, sizeof(htEntry));
    assert(htEntry);
    htEntry->htItems = arrayNew(htItemRelease);
    return htEntry;
}

static void
htEntryRelease(HtEntry **htEntry)
{
    if (*htEntry) {
        arrayRelease(&(*htEntry)->htItems);
        objectRelease(htEntry);
    }
}

Ht*
htNew(int initialCapacity, void (*releaseFn)(void **))
{
    assert(initialCapacity > 0);
    Ht *ht = calloc(1, sizeof(Ht));
    assert(ht);
    ht->numOfItems = 0;
    ht->initialCapacity = initialCapacity;
    ht->capacity = initialCapacity;
    ht->releaseFn = releaseFn;
    ht->htEntries = arrayNewWithAmount(initialCapacity, htEntryRelease);
    return ht;
}

void
htRelease(Ht **ht)
{
    if (*ht) {
        arrayRelease(&(*ht)->htEntries);
        objectRelease(ht);
    }
}

static void
htResize(Ht **ht, int capacity, void (*releaseFn)(void **))
{
    assert(*ht);
    assert(capacity > 0);
    Ht *newHt = htNew(capacity, releaseFn);
    newHt->initialCapacity = (*ht)->initialCapacity;
    Array *htEntries = (*ht)->htEntries;
    int lenHtEntries = htEntries->size;
    for (int i = 0; i < lenHtEntries; i++) {
        HtEntry *htEntry = arrayGet(htEntries, i);
        if (htEntry) {
            Array *htItems = htEntry->htItems;
            int lenHtItems = htItems->size;
            Array *newHtEntries = newHt->htEntries;
            for (int i = 0; i < lenHtItems; i++) {
                HtItem *htItem = arrayGet(htItems, i);
                /* Key's rehashing according the new capacity. */
                int idx = hash(capacity, htItem->key);
                HtEntry *newHtEntry = arrayGet(newHtEntries, idx);
                if (!newHtEntry) {
                    newHtEntry = htEntryNew();
                    arraySet(newHtEntries, newHtEntry, idx);
                }
                arrayAdd(newHtEntry->htItems, htItem);
                newHt->numOfItems++;
            }
            /* We cannot use arrayRemove() function because it decreases
             * the size of the array losing some hash indexes.
             * Moreover, if a release function pointer is set we lose the items inside
             * which must be added to the new hashtable now.
            */
            objectRelease(&htEntry->htItems->arr);
            objectRelease(&htEntry->htItems);
            objectRelease(&htEntry);
        }
    }
    /* We cannot use htRelease() function for the said above reasons. */
    objectRelease(&(*ht)->htEntries->arr);
    objectRelease(&(*ht)->htEntries);
    objectRelease(&(*ht));
    *ht = newHt;
}

void*
htGet(Ht *ht, const char *key)
{
    if (ht && key && !stringEquals(key, "")) {
        int idx = hash(ht->capacity, key);
        HtEntry *htEntry = arrayGet(ht->htEntries, idx);
        if (htEntry) {
            Array *htItems = htEntry->htItems;
            int lenHtItems = htItems->size;
            for (int i = 0; i < lenHtItems; i++) {
                HtItem *htItem = arrayGet(htItems, i);
                if (stringEquals(htItem->key, key))
                    return htItem->value;
            }
        }
    }
    return NULL;
}

bool
htAdd(Ht **ht, const char *key, void *value)
{
    if (*ht && key && !stringEquals(key, "")) {
        int *capacity = &(*ht)->capacity;
        int idx = hash(*capacity, key);
        HtEntry *htEntry = arrayGet((*ht)->htEntries, idx);
        if (htEntry) {
            Array *htItems = htEntry->htItems;
            int lenHtItems = htItems->size;
            for (int i = 0; i < lenHtItems; i++) {
                HtItem *htItem = arrayGet(htItems, i);
                if (stringEquals(htItem->key, key))
                    return false;
            }
        }
        if (!htEntry) {
            htEntry = htEntryNew();
            arraySet((*ht)->htEntries, htEntry, idx);
        }
        arrayAdd(htEntry->htItems, htItemNew(*ht, key, value));
        (*ht)->numOfItems++;
        /* Check threshold */
        int threshold = *capacity * 3 / 4;
        if ((*ht)->numOfItems >= threshold)
            htResize(ht, *capacity * 2, (*ht)->releaseFn);
        return true;
    }
    return false;
}

bool
htRemove(Ht **ht, const char *key)
{
    if (*ht && key && !stringEquals(key, "")) {
        int *capacity = &(*ht)->capacity;
        int idx = hash(*capacity, key);
        Array *htEntries = (*ht)->htEntries;
        HtEntry *htEntry = arrayGet(htEntries, idx);
        if (htEntry) {
            Array **htItems = &htEntry->htItems;
            int lenHtItems = (*htItems)->size;
            for (int i = 0; i < lenHtItems; i++) {
                HtItem *htItem = arrayGet(*htItems, i);
                if (stringEquals(htItem->key, key)) {
                    if (lenHtItems == 1)
                        arraySet(htEntries, NULL, idx);
                    else
                        arrayRemove(*htItems, htItem);
                    (*ht)->numOfItems--;
                    /* check threshold */
                    if (*capacity > (*ht)->initialCapacity) {
                        int threshold = *capacity / 4;
                        if ((*ht)->numOfItems <= threshold)
                            htResize(ht, *capacity / 2, (*ht)->releaseFn);
                    }
                    return true;
                }
            }
        }
    }
    return false;
}

bool
htSet(Ht **ht, const char *key, void *value)
{
    if (*ht && key && !stringEquals(key, "")) {
        int idx = hash((*ht)->capacity, key);
        HtEntry *htEntry = (HtEntry *)arrayGet((*ht)->htEntries, idx);
        if (htEntry) {
            Array **htItems = &htEntry->htItems;
            int lenHtItems = (*htItems)->size;
            for (int i = 0; i < lenHtItems; i++) {
                HtItem *htItem = arrayGet(*htItems, i);
                if (stringEquals(htItem->key, key)) {
                    void (*releaseFn)(void **) = htItem->releaseFn;
                    if (releaseFn)
                        (*releaseFn)(&htItem->value);
                    htItem->value = value;
                    return true;
                }
            }
        }
    }
    return false;
}

HtIterator*
htGetIterator(Ht *ht)
{
    if (ht) {
        HtIterator *htIter = calloc(1, sizeof(HtIterator));
        assert(htIter);
        htIter->ht = ht;
        htIter->hashIdx = 0;
        htIter->hashItemIdx = -1;
        return htIter;
    }
    return NULL;
}

void*
htGetNext(HtIterator *htIterator)
{
    if (htIterator) {
        Ht *ht = htIterator->ht;
        int capacity = ht->capacity;
        int *hashIdx = &htIterator->hashIdx;
        for (; *hashIdx < capacity; (*hashIdx)++) {
            HtEntry *htEntry = arrayGet(ht->htEntries, *hashIdx);
            if (htEntry) {
                Array *htItems = htEntry->htItems;
                int *hashItemIdx = &htIterator->hashItemIdx;
                if (++(*hashItemIdx) < htItems->size)
                    return ((HtItem *)arrayGet(htItems, *hashItemIdx))->value;
                else
                    *hashItemIdx = -1;
            }
        }
    }
    return NULL;
}

void
htIteratorReset(Ht *ht, HtIterator *htIterator)
{
    if (htIterator && ht) {
        htIterator->ht = ht;
        htIterator->hashIdx = 0;
        htIterator->hashItemIdx = -1;
    }
}
