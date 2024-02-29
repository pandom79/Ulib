#include "../ulib.h"

int main()
{
    int rv = 0;

    printf("\nTest prepend chr\n");
    char *test = stringNew("Test");
    stringPrependChr(&test, 'A');
    printf("Test = %s\n", test);
    objectRelease(&test);

    printf("\nTest prepend str\n");
    test = stringNew("Test");
    stringPrependStr(&test, "AAA");
    printf("Test = %s\n", test);
    objectRelease(&test);

    return rv;
}
