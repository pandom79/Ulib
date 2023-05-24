#include "../ulib.h"

int main()
{
    int capacity = 30;
    Ht *ht = htNew(capacity, objectRelease);
    printf("Initial capacity = %d\n", capacity);

    // test add and resize
    for (int i = 0; i < 150; i++) {
        char key[50] = {0};
        char value[50] = {0};
        sprintf(key, "Domenico%d", i);
        sprintf(value, "Panella%d", i);
        htAdd(&ht, key, stringNew(value));
    }

    Array *items = htGetAll(ht);
    int len = items->size;
    printf("%d Items found!\n", len);
    for (int i = 0; i < len; i++) {
        HtItem *item = arrayGet(items, i);
        printf("Key = %s, Value = %s\n", item->key, (char *)item->value);
    }
    arrayRelease(&items);

    htRelease(&ht);
}
