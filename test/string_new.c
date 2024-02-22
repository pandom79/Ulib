#include "../ulib.h"

int main()
{
    int rv = 0;
    char *test = stringNew("Test");
    if (strlen(test) != 4 || !stringEquals(test, "Test"))
        rv = 1;
    printf("Value = %s\n", test);

    objectRelease(&test);
    return rv;
}
