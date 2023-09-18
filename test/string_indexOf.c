#include "../ulib.h"

int main()
{
    int rv = 1;
    const char *test = "HelloWorld";
    int idx = stringIndexOfChr(test, 'W');
    if (idx == 5)
        rv = 0;
    idx = stringIndexOfStr(test, "rld");
    if (idx == 7)
        rv = 0;
    else
        rv = 1;
    return rv;
}
