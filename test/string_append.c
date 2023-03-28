#include "../ulib.h"

int main()
{
    int rv = 0;
    char *test = stringNew("Test");
    stringAppendStr(&test, "Append");
    if (strlen(test) != 10)
        rv = 1;
    objectRelease(&test);
    return rv;
}
