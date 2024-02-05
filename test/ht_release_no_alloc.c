#include "../uhashtable/uhashtable.h"

int main()
{
    int capacity = 11;
    Ht *ht = htNew(capacity, NULL);
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
    htAdd(&ht, "Domenico", "Panella");
    htAdd(&ht, "Domenico1", "Panella1");
    htAdd(&ht, "Domenico2", "Panella2");
    htAdd(&ht, "Antonio", "Esposito");
    htAdd(&ht, "Francesco", "Riccio");
    htAdd(&ht, "Domenico", "Panella");
    htAdd(&ht, "Luigi", "Gallo");
    htAdd(&ht, "Marianeve", "Maresca");
    htAdd(&ht, "Michele", "Oliva");
    htAdd(&ht, "Arturo", "Cirillo");

    // test set
//    htSet(&ht, "Domenico", stringNew("Panella2"));

    // test get
//    HtItem *htItem = htGet(ht, "Domenico");
//    if (htItem)
//        printf("Domenico key is present! Value = %s\n", (char *)htItem->value);
//    htItem = htGet(ht, "Ciccio");
//    if (!htItem)
//        printf("Ciccio key is not present!\n");

    // test remove and resize
    if (htRemove(&ht, "Luigi"))
        printf("Luigi removed!\n");
    if (htRemove(&ht, "Domenico"))
        printf("Domenico removed!\n");
    if (htRemove(&ht, "Domenico1"))
        printf("Domenico1 removed!\n");
    if (htRemove(&ht, "Domenico2"))
        printf("Domenico2 removed!\n");
    if (htRemove(&ht, "Francesco"))
        printf("Francesco removed!\n");
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

    /* Set debug data */
    htSetDebugData(ht);

    htEntries = ht->htEntries;
    for (int i = 0; i < htEntries->size; i++) {
        printf("After Hash %d\n", i);
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

    printf("\nSUMMARY\n");
    printf("Capacity = %d\n", ht->capacity);
    printf("Elements = %d\n", ht->numOfItems);
    printf("Max collisions for entry = %d\n", ht->maxCollisionsForEntry);
    printf("Total collisions = %d\n", ht->totCollisions);

    htRelease(&ht);
}
