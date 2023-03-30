#include "../ulib.h"

int main()
{
    Array *arr = arrayNewWithAmount(3, objectRelease);
    arraySet(arr, stringNew("Elem1"), 0);
    arraySet(arr, stringNew("Elem2"), 1);
    arraySet(arr, stringNew("Elem3"), 2);

    for (int i = 0; i < arr->size; i++) {
        printf("Elem = %s\n", (char *)arrayGet(arr, i));
    }

    Array *copy = arrayStrCopy(arr);
    for (int i = 0; i < arr->size; i++) {
        printf("Copied elem = %s\n", (char *)arrayGet(arr, i));
    }

    arrayRelease(&arr);
    arrayRelease(&copy);
    return 0;
}
