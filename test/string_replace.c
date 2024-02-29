#include "../ulib.h"

int main()
{
    int rv = 0;

    printf("Test replace chr\n");
    char *test = stringNew("Test");
    stringReplaceChr(&test, 'e', 'E');
    printf("Test = %s\n", test);
    objectRelease(&test);

    printf("Test replace all chr\n");
    test = stringNew("Teste");
    stringReplaceAllChr(&test, 'e', 'E');
    printf("Test = %s\n", test);
    objectRelease(&test);

    printf("Test replace str\n");
    test = stringNew("CiaoComeStai");
    stringReplaceStr(&test, "Ciao", "Hello");
    printf("Test = %s\n", test);
    objectRelease(&test);

    printf("Test replace All str\n");
    test = stringNew("CiaoCiaoStai");
    stringReplaceAllStr(&test, "Ciao", "Hello");
    printf("Test = %s\n", test);
    objectRelease(&test);

    return rv;
}
