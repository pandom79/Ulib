#include "../ulib.h"

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
    int capacity = 39;
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
    for (int i = 0; i < 1500; i++) {
        char key[50] = {0};
        char value[50] = {0};
        sprintf(key, "Domenico%d", i);
        sprintf(value, "Panella%d", i);
        htAdd(&ht, key, stringNew(value));
    }

    // test set
//    htSet(&ht, "Domenico9", stringNew("PanellaReplaced"));
//    htSet(&ht, "Domenico9", NULL);
//    htSet(&ht, "Domenico9", NULL);

    // test get
    HtItem *htItem = htGet(ht, "Domenico608");
    if (htItem)
        printf("Domenico608 key is present! Value = %s\n", (char *)htItem->value);
    htItem = htGet(ht, "Ciccio");
    if (!htItem)
        printf("Ciccio key is not present!\n");

//    // test remove and resize
    for (int i = 0; i < 1485; i++) {
        char key[50] = {0};
        sprintf(key, "Domenico%d", i);
        if (htRemove(&ht, key)) {
             printf("%s removed!\n", key);
        }
    }

//    if (htRemove(&ht, "Luigi"))
//        printf("Luigi removed!\n");
//    if (htRemove(&ht, "Domenico"))
//        printf("Domenico removed!\n");
//    if (htRemove(&ht, "Domenico1"))
//        printf("Domenico1 removed!\n");
//    if (htRemove(&ht, "Domenico2"))
//        printf("Domenico2 removed!\n");
//    if (htRemove(&ht, "Francesco"))
//        printf("Francesco removed!\n");
//    if (htRemove(&ht, "Marianeve"))
//        printf("Marianeve removed!\n");
//    if (htRemove(&ht, "Michele"))
//        printf("Michele removed!\n");
//    if (htRemove(&ht, "Arturo"))
//        printf("Arturo removed!\n");
//    if (htRemove(&ht, "Antonio"))
//        printf("Antonio removed!\n");
//    if (htRemove(&ht, "Ciccio"))
//        printf("Ciccio removed!\n");
//    else
//        printf("Ciccio not removed!\n");

    htEntries = ht->htEntries;
    int totCollisions = 0;
    int maxCollisionsForItem = 0;
    for (int i = 0; i < htEntries->size; i++) {
        printf("After Hash %d\n", i);
        HtEntry *htEntry = arrayGet(htEntries, i);
        if (htEntry) {
            Array *htItems = htEntry->htItems;
            int lenHtItems = htItems->size;
            if (lenHtItems > 0) {
                totCollisions += lenHtItems -1;
                if (lenHtItems - 1 > maxCollisionsForItem)
                    maxCollisionsForItem = lenHtItems - 1;
            }
            for (int j = 0; j < lenHtItems; j++) {
                HtItem *htItem = arrayGet(htItems, j);
                printf("    Key = %s, Value = %s\n", htItem->key, (char *)htItem->value);
            }
        }
    }

    printf("\nSUMMARY\n");
    printf("Capacity = %d\n", ht->capacity);
    printf("Elements = %d\n", ht->numOfItems);
    printf("Max collisions for item = %d\n", maxCollisionsForItem);
    printf("Total collisions = %d\n", totCollisions);

    htRelease(&ht);
}
