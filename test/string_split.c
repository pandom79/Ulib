#include "../ulib.h"

int main()
{
    printf("Function stringSplitFirst\n");
    char *test = stringNew("Hello|World!|How|Are|You");
    printf("Word = %s\n", test);
    Array *values = stringSplitFirst(test, "|");
    for (int i = 0; i < values->size; i++) {
        printf("Token = %s\n", (char *)arrayGet(values, i));
    }
    arrayRelease(&values);

    printf("\nFunction stringSplit\n");
    printf("Word = %s\n", test);
    values = stringSplit(test, "|", true);
    for (int i = 0; i < values->size; i++) {
        printf("Token = %s\n", (char *)arrayGet(values, i));
    }
    arrayRelease(&values);
    objectRelease(&test);

    return 0;
}
