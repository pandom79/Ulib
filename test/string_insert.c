#include "../ulib.h"

int main()
{
    int rv = 0;

    printf("Test insert chr\n");
    char *test = stringNew("Test");
    stringInsertChrAt(&test, 'A', 2);
    printf("Test = %s\n", test);
    objectRelease(&test);

    printf("Test insert str\n");
    test = stringNew("Test");
    stringInsertStrAt(&test, "AAA", 2);
    printf("Test = %s\n", test);
    objectRelease(&test);

    return rv;
}
