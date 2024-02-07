#include "../ulib.h"

int main()
{
    Array *arr = arrayNewWithAmount(3, objectRelease);
    arraySet(arr, stringNew("Elem1"), 0);
    arraySet(arr, stringNew("Elem2"), 1);
    arraySet(arr, stringNew("Elem3"), 2);

    arraySet(arr, stringNew("New element"), 1);

    for (int i = 0; i < arr->size; i++) {
        printf("Elem = %s\n", (char *)arrayGet(arr, i));
    }

    Array *copy = arrayStrCopy(arr);
    for (int i = 0; i < arr->size; i++) {
        printf("Copied elem = %s\n", (char *)arrayGet(arr, i));
    }

    printf("\n\nTest insertAt\n");
    char *element = stringNew("Ciccio");
    int idx = 3;
    Array *arr2 = arrayNew(objectRelease);
    arrayAdd(arr2, stringNew("Domenico"));
    arrayAdd(arr2, stringNew("Antonio"));
    arrayAdd(arr2, stringNew("Luigi"));
    arrayAdd(arr2, stringNew("Arturo"));
    if (arrayInsertAt(arr2, idx, element))
        printf("'%s' inserted at '%d' index!\n", element, idx);
    else {
        printf("'%s' not inserted at '%d' index!\n", element, idx);
        objectRelease(&element);
    }

    for (int i = 0; i < arr2->size; i++) {
        printf("Element = %s\n", (char *)arrayGet(arr2, i));
    }

    arrayRelease(&arr2);
    arrayRelease(&arr);
    arrayRelease(&copy);
    arrayRelease(&arr);
    arrayRelease(&copy);
    return 0;
}
