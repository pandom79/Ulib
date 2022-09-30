/*
(C) 2021 by Domenico Panella <pandom79@gmail.com>

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License version 3.
See http://www.gnu.org/licenses/gpl-3.0.html for full license text.
*/

#include "wrapper.h"

int
msleep(long msec)
{
    struct timespec ts;
    int res;

    if (msec < 0) {
        errno = EINVAL;
        return -1;
    }
    ts.tv_sec = msec / 1000;
    ts.tv_nsec = (msec % 1000) * 1000000;
    do {
        res = nanosleep(&ts, &ts);
    } while (res && errno == EINTR);

    return res;
}

Time*
timeNew(Time *timeFrom)
{
    Time *time = calloc(1, sizeof(Time));
    assert(time);

    //Sec
    long *sec = calloc(1, sizeof(long));
    assert(sec);

    //Millisec
    long *milliSec = calloc(1, sizeof(long));
    assert(milliSec);

    //Duration sec
    long *durationSec = calloc(1, sizeof(long));
    assert(durationSec);

    //Duration milli sec
    long *durationMillisec = calloc(1, sizeof(long));
    assert(durationMillisec);

    if (!timeFrom) {
        /* Get the second with CLOCK_REALTIME */
        struct timespec timeSpec = {0};
        clock_gettime(CLOCK_REALTIME, &timeSpec);
        *sec = timeSpec.tv_sec;
        *milliSec = round(timeSpec.tv_nsec / 1.0e6);

        //Duration
        struct timespec durationSpec = {0};
        /* We use CLOCK_MONOTONIC because the duration must not be affected by system time changing */
        clock_gettime(CLOCK_MONOTONIC, &durationSpec);
        *durationSec = durationSpec.tv_sec;
        *durationMillisec = round(durationSpec.tv_nsec / 1.0e6); // Convert nanoseconds to milliseconds
        if (*durationMillisec > 999) {
            (*durationSec)++;
            *durationMillisec = 0;
        }
    }
    else {
        *sec = *timeFrom->sec;
        *milliSec = *timeFrom->milliSec;
        /* Duration */
        *durationSec = *timeFrom->durationSec;
        *durationMillisec = *timeFrom->durationMillisec;
    }

    time->sec = sec;
    time->milliSec = milliSec;
    time->durationSec = durationSec;
    time->durationMillisec = durationMillisec;

    return time;
}

void
timeSet(Time **timeA, const Time *timeB)
{
    if (timeB) {
        if (*timeA)
            timeRelease(timeA);
        *timeA = timeNew((Time *)timeB);
    }
}

void
timeRelease(Time **time)
{
    Time *timeTemp = *time;
    if (timeTemp) {
        objectRelease(&timeTemp->sec);
        objectRelease(&timeTemp->milliSec);
        objectRelease(&timeTemp->durationSec);
        objectRelease(&timeTemp->durationMillisec);
        objectRelease(time);
    }
}

char*
stringGetTimeStamp(Time *time, bool hasMillisec, const char *format)
{
    char dateTimeStr[50] = {0};

    struct timespec tv;
    clock_gettime(CLOCK_REALTIME, &tv);

    if (time) {
        tv.tv_sec = *time->sec;
        tv.tv_nsec = round(*time->milliSec * 1.0e6);
    }

    struct tm *timeInfo = localtime(&tv.tv_sec);
    strftime(dateTimeStr, 50, format ? format : "%d %B %Y %H:%M:%S", timeInfo);
    if (hasMillisec) {
        strcat(dateTimeStr, ".");
        long milliSec = round(tv.tv_nsec / 1.0e6);
        char millisecStr[10] = {0};
        sprintf(millisecStr, "%lu", milliSec);
        strcat(dateTimeStr, millisecStr);
    }

    return stringNew(dateTimeStr);
}

char*
stringGetDiffTime(Time *timeEnd, Time *timeStart)
{
    char timeStr[50] = {0};
    int day, hour, min, sec;
    double diffTime = 0;
    long *millisecStart, *millisecEnd;

    day = hour = min = sec = -1;
    millisecStart = millisecEnd = NULL;

    assert(timeEnd);
    assert(timeStart);

    diffTime = difftime(*timeEnd->durationSec, *timeStart->durationSec);
    millisecStart = timeStart->durationMillisec;
    millisecEnd = timeEnd->durationMillisec;

    if (diffTime > 0) {
        long diffMillisec = (1000 - *millisecStart + *millisecEnd);
        if (diffMillisec < 1000)
            diffTime--;
        else
            diffMillisec = diffMillisec - 1000;

        sec = diffTime;
        if (sec >= 60) {
            min = diffTime / 60;
            if (min > 0) {
                sec -= min * 60;
            }
        }
        if (min >= 60) {
            hour = min / 60;
            min -= hour * 60;
        }
        if (hour >= 24) {
            day = hour / 24;
            hour -= day * 24;
        }

        if (day != -1 && day > 0) {
            char dayStr[10] = {0};
            sprintf(dayStr, "%dd ", day);
            strcat(timeStr, dayStr);
        }
        if (hour != -1 && hour > 0) {
            char hourStr[20] = {0};
            sprintf(hourStr, "%dh ", hour);
            strcat(timeStr, hourStr);
        }
        if (min != -1 && min > 0) {
            char minStr[20] = {0};
            sprintf(minStr, "%dm ", min);
            strcat(timeStr, minStr);
        }
        if (sec != -1) {
            char secStr[40] = {0};
            sprintf(secStr, "%d.%lds ", sec, diffMillisec);
            strcat(timeStr, secStr);
        }

    }
    else {
        long diffMillisec = *millisecEnd - *millisecStart;
        sprintf(timeStr, "0.%lds", diffMillisec);
    }
    return stringNew(timeStr);
}
