#include "../ulib.h"

int main()
{
    int rv = 0;
    char *test = stringNew("TestString1");
    char *sub = stringSub(test, 0, 5);

    printf("Value = %s\n", test);
    printf("Sub = %s\n", sub);

    objectRelease(&test);
    objectRelease(&sub);
    return rv;
}
