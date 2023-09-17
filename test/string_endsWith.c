#include "../ulib.h"

int main()
{
    int rv = 1;
    const char *test = "HelloWorld";
    if (stringEndsWithStr(test, "World"))
        rv = 0;
    return rv;
}
