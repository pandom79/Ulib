#include "../ulib.h"

int main()
{
    int rv = 0;
    char *size = stringGetFileSize(23423422299);
    printf("Size = %s\n", size);

    objectRelease(&size);
    return rv;
}
