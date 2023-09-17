#include "../ulib.h"

int main()
{
    int rv = 1;
    const char *test = "HelloWorldHelloWorldHelloWorld";
    int idx = stringLastIndexOfStr(test, "Hello");
    if (idx == 20)
        rv = 0;
    return rv;
}
