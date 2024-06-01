/*
(C) 2021 by Domenico Panella <pandom79@gmail.com>

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License version 3.
See http://www.gnu.org/licenses/gpl-3.0.html for full license text.
*/

#include "../ulib.h"

static const char *SIZES[] = { "EB", "PB", "TB", "GB", "MB", "KB", "B" };
static const off_t EXBIBYTES = 1024ULL * 1024ULL * 1024ULL * 1024ULL * 1024ULL * 1024ULL;

char *stringNew(const char *str)
{
    char *ret = NULL;

    if (str) {
        ret = calloc(strlen(str) + 1, sizeof(char));
        assert(ret);
        assert(stringCopy(ret, str));
    }

    return ret;
}

bool stringSet(char **str, const char *value)
{
    if (value) {
        if (*str)
            objectRelease(str);
        *str = stringNew(value);
        return true;
    }

    return false;
}

bool stringCopy(char *s, const char *src)
{
    if (s && src) {
        int lenSrc = strlen(src);
        for (int i = 0; i < lenSrc; i++)
            s[i] = src[i];
        s[lenSrc] = '\0';
        return true;
    }

    return false;
}

const char *stringGet(char *str)
{
    return (const char *)str;
}

bool stringStartsWithChr(const char *str, const char c)
{
    if (str && *str == c)
        return true;

    return false;
}

bool stringStartsWithStr(const char *str, const char *searchStr)
{
    if (str && searchStr && strncmp(str, searchStr, strlen(searchStr)) == 0)
        return true;

    return false;
}

bool stringEndsWithChr(const char *str, const char c)
{
    if (str && *(str + (strlen(str) - 1)) == c)
        return true;

    return false;
}

bool stringEndsWithStr(const char *str, const char *searchStr)
{
    int lenStr = str ? strlen(str) : 0;
    int lenSearchStr = searchStr ? strlen(searchStr) : 0;
    if (lenStr > 0 && lenSearchStr > 0 && lenSearchStr <= lenStr) {
        if (strcmp(str + (lenStr - lenSearchStr), searchStr) == 0)
            return true;
    }

    return false;
}

bool stringContainsChr(const char *str, const char c)
{
    if (str && c && strchr(str, c))
        return true;

    return false;
}

bool stringContainsStr(const char *str, const char *searchStr)
{
    if (str && searchStr && strstr(str, searchStr))
        return true;

    return false;
}

void stringToupper(char *str)
{
    while (*str) {
        *str = toupper((unsigned char)*str);
        str++;
    }
}

void stringTolower(char *str)
{
    while (*str) {
        *str = tolower((unsigned char)*str);
        str++;
    }
}

bool stringAppendChr(char **a, const char b)
{
    if (*a && b) {
        char temp[] = { b, '\0' };
        return stringAppendStr(a, temp);
    }

    return false;
}

bool stringAppendStr(char **a, const char *b)
{
    if (*a && b) {
        int lenA = strlen(*a), lenB = strlen(b);
        *a = realloc(*a, (lenA + lenB + 1) * sizeof(char));
        assert(*a);
        memmove(*a + lenA, b, lenB);
        *(*a + lenA + lenB) = '\0';
        return true;
    }

    return false;
}

bool stringPrependChr(char **a, const char b)
{
    if (*a && b) {
        char temp[] = { b, '\0' };
        return stringPrependStr(a, temp);
    }

    return false;
}

bool stringPrependStr(char **a, const char *b)
{
    if (*a && b) {
        int lenA = strlen(*a), lenB = strlen(b);
        *a = realloc(*a, (lenA + lenB + 1) * sizeof(char));
        assert(*a);
        memmove(*a + lenB, *a, lenA);
        memmove(*a, b, lenB);
        *(*a + lenA + lenB) = '\0';
        return true;
    }

    return false;
}

bool stringInsertChrAt(char **a, const char b, int pos)
{
    if (*a && b) {
        char temp[] = { b, '\0' };
        return stringInsertStrAt(a, temp, pos);
    }

    return false;
}

bool stringInsertStrAt(char **a, const char *b, int pos)
{
    if (*a && b) {
        int lenA = strlen(*a), lenB = strlen(b);
        if (pos >= 0 && pos <= lenA) {
            *a = realloc(*a, (lenA + lenB + 1) * sizeof(char));
            assert(*a);
            memmove(*a + pos + lenB, *a + pos, lenA - pos);
            memmove(*a + pos, b, lenB);
            *(*a + lenA + lenB) = '\0';
            return true;
        }
    }

    return false;
}

char *stringLtrim(char *str, const char *seps)
{
    size_t totrim;

    if (seps == NULL) {
        seps = "\t\n\v\f\r ";
    }
    totrim = strspn(str, seps);
    if (totrim > 0) {
        size_t len = strlen(str);
        if (totrim == len) {
            str[0] = '\0';
        } else {
            memmove(str, str + totrim, len + 1 - totrim);
        }
    }

    return str;
}

char *stringRtrim(char *str, const char *seps)
{
    int i;

    if (seps == NULL) {
        seps = "\t\n\v\f\r ";
    }
    i = strlen(str) - 1;
    while (i >= 0 && strchr(seps, str[i]) != NULL) {
        str[i] = '\0';
        i--;
    }

    return str;
}

char *stringTrim(char *str, const char *seps)
{
    return stringLtrim(stringRtrim(str, seps), seps);
}

int stringIndexOfChr(const char *str, const char c)
{
    if (str && !stringEquals(str, "") && c) {
        int len = strlen(str);
        for (int i = 0; i < len; i++) {
            if (str[i] == c)
                return i;
        }
    }

    return -1;
}

int stringIndexOfStr(const char *str, const char *c)
{
    if (str && !stringEquals(str, "") && c && !stringEquals(c, "")) {
        int idx = 0, lenC = strlen(c);
        while (*str) {
            if (strncmp(str, c, lenC) == 0)
                return idx;
            str++;
            idx++;
        }
    }

    return -1;
}

int stringLastIndexOfChr(const char *str, const char c)
{
    if (str && !stringEquals(str, "") && c) {
        int index = strlen(str) - 1;
        for (; index >= 0; index--) {
            if (str[index] == c)
                return index;
        }
    }

    return -1;
}

int stringLastIndexOfStr(const char *str, const char *c)
{
    if (str && !stringEquals(str, "") && c && !stringEquals(c, "")) {
        int lenC = strlen(c), lenStr = strlen(str), idx = lenStr - 1;
        str += lenStr;
        while (*(--str)) {
            if (strncmp(str, c, lenC) == 0)
                return idx;
            else {
                idx--;
                if (idx == -1)
                    goto out;
            }
        }
    }
out:
    return -1;
}

char *stringSub(const char *str, int startIdx, int endIdx)
{
    char *ret = NULL;
    int len = str ? strlen(str) : 0;

    if (len > 0 && startIdx >= 0 && endIdx >= 0 && endIdx < len) {
        int numElements = (endIdx - startIdx) + 1;
        if (numElements > 0) {
            ret = calloc(numElements + 1, sizeof(char));
            assert(ret);
            memmove(ret, str + startIdx, numElements);
        }
    }

    return ret;
}

void stringReplaceChr(char **str, const char a, const char b)
{
    if (*str) {
        char *temp = strchr(*str, a);
        if (temp)
            *temp = b;
    }
}

void stringReplaceAllChr(char **str, const char a, const char b)
{
    if (*str) {
        char *temp = NULL;
        while ((temp = strchr(*str, a)))
            *temp = b;
    }
}

bool stringReplaceStr(char **source, const char *search, const char *replace)
{
    int idx = -1;

    if (*source && replace && (idx = stringIndexOfStr(*source, search)) != -1) {
        int lenSource = strlen(*source), lenSearch = strlen(search), lenReplace = strlen(replace);
        char *ret = calloc(lenSource + lenReplace, sizeof(char));
        assert(ret);
        memmove(ret, *source, idx);
        memmove(ret + idx, replace, lenReplace);
        memmove(ret + idx + lenReplace, *source + idx + lenSearch, lenSource - (idx + lenSearch));
        objectRelease(source);
        *source = ret;
        return true;
    }

    return false;
}

bool stringReplaceAllStr(char **origin, const char *search, const char *replace)
{
    bool ret = false;

    while (true) {
        if (stringReplaceStr(origin, search, replace))
            ret = true;
        else
            break;
    }

    return ret;
}

bool stringEquals(const char *s1, const char *s2)
{
    return strcmp(s1, s2) == 0 ? true : false;
}

bool stringEqualsN(const char *s1, const char *s2, size_t n)
{
    return strncmp(s1, s2, n) == 0 ? true : false;
}

bool stringEqualsIgnCase(const char *s1, const char *s2)
{
    return strcasecmp(s1, s2) == 0 ? true : false;
}

bool stringEqualsIgnCaseN(const char *s1, const char *s2, size_t n)
{
    return strncasecmp(s1, s2, n) == 0 ? true : false;
}

void objectRelease(void **element)
{
    if (*element) {
        free(*element);
        *element = NULL;
    }
}

Array *stringSplit(char *str, const char *sep, bool allocElements)
{
    if (str && sep && strstr(str, sep)) {
        Array *array = allocElements ? arrayNew(objectRelease) : arrayNew(NULL);
        char *element = NULL;
        do {
            if (!element)
                element = strtok(str, sep);
            if (allocElements)
                arrayAdd(array, stringNew(element));
            else
                arrayAdd(array, element);
        } while ((element = strtok(NULL, sep)));
        return array;
    }

    return NULL;
}

Array *stringSplitOnce(char *str, const char *sep)
{
    if (str && sep) {
        char *value = NULL;
        if ((value = strstr(str, sep))) {
            int lenSep = strlen(sep);
            value = stringNew(value + lenSep);
            int size = strlen(str) - strlen(value) - lenSep + 1;
            char *key = calloc(size, sizeof(char));
            assert(key);
            memmove(key, str, size - 1);
            Array *array = arrayNew(objectRelease);
            arrayAdd(array, key);
            arrayAdd(array, value);
            return array;
        }
    }

    return NULL;
}

char *stringGetFileSize(off_t fileSize)
{
    if (fileSize > -1) {
        char *result = calloc(20, sizeof(char));
        assert(result);
        off_t multiplier = EXBIBYTES;
        int i;
        for (i = 0; i < 7; i++, multiplier /= 1024) {
            if (fileSize < multiplier)
                continue;
            if (fileSize % multiplier == 0)
                sprintf(result, "%" PRIu64 "%s", fileSize / multiplier, SIZES[i]);
            else
                sprintf(result, "%.1f%s", (float)fileSize / multiplier, SIZES[i]);
            stringReplaceChr(&result, '.', ',');
            return result;
        }
        assert(stringCopy(result, "0B"));
        return result;
    }

    return NULL;
}
