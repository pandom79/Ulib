#include "../ulib.h"

int main()
{
    int rv = 0;
    char *test = stringNew("Test");
    if (!stringEquals(test, "Test"))
        rv = 1;

    if (!stringEqualsIgnCase(test, "tEsT"))
        rv = 1;

    if (!stringEqualsN(test, "Test", 4))
        rv = 1;

    if (!stringEqualsIgnCaseN(test, "tEsT", 4))
        rv = 1;

    objectRelease(&test);
    return rv;
}
