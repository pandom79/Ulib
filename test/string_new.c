#include "../ulib.h"

int main()
{
    int rv = 0;
    char *test = stringNew("Test");
    if (strlen(test) != 4)
        rv = 1;
    objectRelease(&test);
    return rv;
}
