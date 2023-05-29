#include "../ulib.h"

int main()
{
    char str1[10] = {0};
    if (stringCopy(str1, "Ciao"))
        printf("Str1 copied! Value = %s\n", str1);
    else
        printf("Str1 not copied!\n");


    char *alloc = calloc(5, sizeof(char));
    assert(alloc);
    if (stringCopy(alloc, "TEST"))
        printf("Alloc copied! Value = %s\n", alloc);
    else
        printf("Alloc not copied!\n");

    objectRelease(&alloc);
    return 0;
}
