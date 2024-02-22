#include "../ulib.h"

int main()
{
    int rv = 1;
    const char *test = "HelloWorld";
    int idx = stringIndexOfChr(test, 'W');
    if (idx == 5)
        rv = 0;

    return rv;
}
