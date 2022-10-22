#include "wrapper.h"

//#define LOG_A    0x1
//#define LOG_B    0x10
//#define LOG_C    0x100
//#define LOG_D    0x1000
//#define LOG_E    0x10000
//#define LOG_F    0x100000
//#define LOG_ALL  0x111111

// Hex
#define LOG_A    0x1
#define LOG_B    0x2
#define LOG_C    0x4
#define LOG_D    0x8
#define LOG_E    0x10
#define LOG_F    0x20
#define LOG_ALL  0x3F

int main()
{
//    time_t now = time(NULL);
//    struct tm *localTime = localtime(&now);
//    printf("localTime->tm_sec = %d\n", localTime->tm_sec);
//    printf("localTime->tm_min = %d\n", localTime->tm_min);

////    localTime->tm_mday -= 1;
////    localTime->tm_hour -= 2;
//    localTime->tm_sec -= 1;
////    localTime->tm_min -= 1;

//    printf("localTime->tm_sec = %d\n", localTime->tm_sec);
//    printf("localTime->tm_min = %d\n", localTime->tm_min);

//    time_t start = mktime(localTime);

//    time_t now2 = time(NULL);

//    double diffTime = difftime(now2, start);
//    printf("diffTime = %0.0f\n", diffTime);

//    printDiffTime(diffTime);

//Example 2
//    time_t now = time(NULL);

//    msleep(500);

//    time_t after = time(NULL);

//    printDiffTime(difftime(after, now));

//TIME 1

    time_t now = time(NULL);
    struct tm *localTime = localtime(&now);
//    localTime->tm_mday -= 4;
//    localTime->tm_mon -= 3;
    localTime->tm_hour -= 48;
//    localTime->tm_min -= 43;
//    localTime->tm_sec -= 23000;

    Time *dateTime = timeNew(NULL);
    *dateTime->sec = mktime(localTime);

//    dateTimeSet(&dateTime);


    char *date = NULL;
//    stringSetTimeStamp(&date, dateTime);
    printf("Date = %s\n", date);

    msleep(540);


//TIME 2
    Time *dateTime2 = timeNew(NULL);
//    stringSetTimeStamp(&date, dateTime2);

    printf("Date2 = %s\n", date);

//TIME DIFF

//    long diffTimeLong = difftime(*dateTime2->sec, *dateTime->sec);
    char *diffTimeStr = NULL;
//    stringSetDiffTime(&diffTimeStr, dateTime2, dateTime);
    printf("diffTimeStr = %s\n", diffTimeStr);
    objectRelease(&diffTimeStr);

    timeRelease(&dateTime2);
    timeRelease(&dateTime);
    objectRelease(&date);


    //TIME 3
    msleep(540);
    char *date3 = NULL;
//    stringSetTimeStamp(&date3, NULL);
    printf("Date3 = %s\n", date3);

//    stringSetTimeStamp(&date3, NULL);
    printf("Date3 without millisec = %s\n", date3);

    objectRelease(&date3);


//    char *command = stringNew("Run = /usr/sbin/plymouthd --mode=boot --pid-file=/run/plymouth/pid --attach-to-session");
    char *command = stringNew("Run =");
    Array *values = stringSplitFirst(command, "=");

    int len = values ? values->size : 0;
    for (int i = 0; i < len; i++) {
        printf("Valore %i = %s\n", i, (char *)arrayGet(values, i));
    }

    objectRelease(&command);
    arrayRelease(&values);


//    Time *current = timeNew(NULL);
//    char *currentTimeStamp = stringGetTimeStamp(current, false);

//    printf("currentTimeStamp = %s\n", currentTimeStamp);

//    timeRelease(&current);
//    objectRelease(&currentTimeStamp);
    Time *timeA = timeNew(NULL);
    char *timeStampA = stringGetTimeStamp(timeA, true, NULL);
    printf("timestampA = %s\n", timeStampA);
    msleep(1000);

    char *timeStampB = stringGetTimeStamp(NULL, true, NULL);
    printf("timestampB prima volta = %s\n", timeStampB);
    objectRelease(&timeStampB);

    Time *timeB = timeNew(NULL);
    timeStampB = stringGetTimeStamp(timeB, false, "%d-%m-%Y %H:%M:%S");
//    timeStampB = stringGetTimeStamp(timeB, false, NULL);
    printf("timestampB = %s\n", timeStampB);
    objectRelease(&timeStampB);

//    char *diffTime = stringGetDiffTime(timeB, timeA);

//    char *prova = stringNew("Ciao");
//    printf("diffTime = %s\n", diffTime);
//    printf("prova = %s\n", prova);
//    stringSet(&prova, diffTime);
//    printf("prova = %s\n", prova);

    timeRelease(&timeA);
    timeRelease(&timeB);
//    objectRelease(&diffTime);
//    objectRelease(&prova);
    objectRelease(&timeStampA);
    objectRelease(&timeStampB);
//    int res = (LOG_A | LOG_B | LOG_C);
//    printf("LOG_A = %d\n", LOG_A);
//    printf("LOG_B = %d\n", LOG_B);
//    printf("LOG_C = %d\n", LOG_C);
//    printf("LOG_D = %d\n", LOG_D);
//    printf("LOG_ALL = %d\n", LOG_ALL);

////    int res = (LOG_A | LOG_E | LOG_C | LOG_D | LOG_F);
//    int res = (LOG_ALL);
//    bool res_LOG_A = res & LOG_A;
//    bool res_LOG_B = res & LOG_B;
//    bool res_LOG_C = res & LOG_C;
//    bool res_LOG_D = res & LOG_D;
//    bool res_LOG_E = res & LOG_E;
//    bool res_LOG_F = res & LOG_F;
//    bool res_LOG_ALL = res & LOG_ALL;
    const char *test = "ciao..mimmo";
    Array *entries = stringSplitFirst((char *)test, "..");
    if (entries)
    for (int i = 0; i < entries->size; i++) {
        printf("Entry of %d = %s\n", i , (char *)arrayGet(entries, i));
    }
    arrayRelease(&entries);

}
