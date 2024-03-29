#include "../ulib.h"

int main()
{
    int rv = 0;

    printf("Test append chr\n");
    char *test = stringNew("Test");
    stringAppendChr(&test, 'A');
    printf("Test = %s\n", test);
    objectRelease(&test);

    printf("\nTest append str\n");
    test = stringNew("Test");
    stringAppendStr(&test, "AAAA");
    printf("Test = %s\n", test);
    objectRelease(&test);

    return rv;
}
