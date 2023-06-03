#include "../uhashtable/uhashtable.h"

bool isPowerOfTwo(int x)
{
    /* First x in the below expression is for the case when x is 0 */
    return x && (!(x & (x - 1)));
}

bool prime(int n)
{
    int i;
    for (i = 2; i <= n/2; i++)
    {
        if (n % i != 0)
            continue;
        else
            return false;
    }
    return true;
}

int main()
{
    int capacity = 4;
    printf("Is %d a power of 2 = %s\n", capacity, isPowerOfTwo(capacity) ? "True" : "False");
    printf("Is %d a prime number = %s\n", capacity, prime(capacity) ? "True" : "False");

    Ht *ht = htNew(capacity, objectRelease);
    printf("Initial capacity = %d\n", capacity);

    Array *htEntries = ht->htEntries;
    for (int i = 0; i < htEntries->size; i++) {
        printf("Before Hash %d\n", i);
        HtEntry *htEntry = arrayGet(htEntries, i);
        if (htEntry) {
            Array *htItems = htEntry->htItems;
            int lenHtItems = htItems->size;
            for (int j = 0; j < lenHtItems; j++) {
                HtItem *htItem = arrayGet(htItems, j);
                printf("    Key = %s, Value = %s\n", htItem->key, (char *)htItem->value);
            }
        }
    }

    // test add and resize
    for (int i = 0; i < 256; i++) {
        char key[50] = {0};
        char value[50] = {0};
        sprintf(key, "Domenico%d", i);
        sprintf(value, "Panella%d", i);
        htAdd(&ht, key, stringNew(value));
    }

    htEntries = ht->htEntries;
    int totCollisions = 0;
    int maxCollisionsForEntry = 0;
    for (int i = 0; i < htEntries->size; i++) {
        printf("After Hash %d\n", i);
        HtEntry *htEntry = arrayGet(htEntries, i);
        if (htEntry) {
            Array *htItems = htEntry->htItems;
            int lenHtItems = htItems->size;
            if (lenHtItems > 0) {
                totCollisions += lenHtItems -1;
                if (lenHtItems - 1 > maxCollisionsForEntry)
                    maxCollisionsForEntry = lenHtItems - 1;
            }
            for (int j = 0; j < lenHtItems; j++) {
                HtItem *htItem = arrayGet(htItems, j);
                printf("    Key = %s, Value = %s\n", htItem->key, (char *)htItem->value);
            }
        }
    }

    printf("\n\nIterator\n");
    HtIterator *htIter = htGetIterator(ht);
    if (htIter) {
        char *value = NULL;
        while ((value = htGetNext(htIter))) {
            printf("Hash idx = %d\n", htIter->hashIdx);
            printf("    Hash item idx = %d, value = %s\n", htIter->hashItemIdx, value);
        }
    }

//    printf("\n\nTest reset");
//    htIteratorReset(ht, htIter);
//    printf("\n\nIterator\n");
//    if (htIter) {
//        char *value = NULL;
//        while ((value = htGetNextIter(htIter))) {
//            printf("Hash idx = %d\n", htIter->hashIdx);
//            printf("    Hash item idx = %d, value = %s\n", htIter->hashItemIdx, value);
//        }
//    }

    objectRelease(&htIter);


    printf("\nSUMMARY\n");
    printf("Capacity = %d\n", ht->capacity);
    printf("Elements = %d\n", ht->numOfItems);
    printf("Max collisions for entry = %d\n", maxCollisionsForEntry);
    printf("Total collisions = %d\n", totCollisions);

    htRelease(&ht);
}
