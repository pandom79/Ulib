#include "../ulib.h"

int main()
{
    int rv = 0;
    char *test = stringNew("Test");

    if (stringCopy(test, "TEST"))
        printf("Copied!\n");

    if (stringCopy(test, "A"))
        printf("Copied!\n");


    char value[15] = {0};
    if (stringCopy(value, "VALUE"))
        printf("Copied! Value = %s", value);

    printf("Value = %s\n", test);
    objectRelease(&test);
    return rv;
}
