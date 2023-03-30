#include "../ulib.h"

int main()
{
    int rv = 0;

    Array *arr = arrayNewWithAmount(3, objectRelease);
    arraySet(arr, stringNew("Elem1"), 0);
    arraySet(arr, stringNew("Elem2"), 1);
    arraySet(arr, stringNew("Elem3"), 2);

    for (int i = 0; i < arr->size; i++) {
        printf("Elem = %s\n", (char *)arrayGet(arr, i));
    }

    if (!arrayContainsStr(arr, "Elem1"))
        rv = 1;

    if (arrayContainsStr(arr, "Elem4"))
        rv = 1;

    arrayRelease(&arr);
    return rv;
}
