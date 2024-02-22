/*
(C) 2021 by Domenico Panella <pandom79@gmail.com>

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License version 3.
See http://www.gnu.org/licenses/gpl-3.0.html for full license text.
*/

#include "../ulib.h"

Array *arrayNew(void (*releaseFn)(void **))
{
    Array *array = calloc(1, sizeof(Array));
    assert(array);
    array->size = 0;
    array->arr = calloc(1, sizeof(void *));
    assert(array->arr);
    if (releaseFn)
        array->releaseFn = releaseFn;

    return array;
}

Array *arrayNewWithAmount(int amount, void (*releaseFn)(void **))
{
    if (amount > 0) {
        Array *array = calloc(1, sizeof(Array));
        assert(array);
        array->size = amount;
        array->arr = calloc(amount, sizeof(void *));
        assert(array->arr);
        if (releaseFn)
            array->releaseFn = releaseFn;
        return array;
    }

    return NULL;
}

bool arrayAdd(Array *array, void *element)
{
    if (array) {
        int size = array->size++;
        void ***arr = &array->arr;
        if (size > 0) {
            *arr = realloc(*arr, (size + 1) * sizeof(void *));
            assert(*arr);
        }
        (*arr)[size] = element;
        return true;
    }

    return false;
}

bool arrayInsertAt(Array *array, int idx, void *element)
{
    if (array && idx >= 0) {
        int *size = &array->size;
        if (idx == *size)
            return arrayAdd(array, element);
        if (idx < *size) {
            (*size)++;
            void ***arr = &array->arr;
            *arr = realloc(*arr, (*size) * sizeof(void *));
            assert(*arr);
            for (int i = (*size - 1); i > idx; i--)
                (*arr)[i] = (*arr)[i - 1];
            (*arr)[idx] = element;
            return true;
        }
    }

    return false;
}

bool arrayRemoveAt(Array *array, int idx)
{
    if (array) {
        void **arr = array->arr;
        int *size = &array->size;
        void (*releaseFn)(void **) = array->releaseFn;
        if (arr && idx >= 0 && idx < *size) {
            if (releaseFn)
                (*releaseFn)(&(arr[idx]));
            if (idx < (*size - 1))
                memmove(arr + idx, arr + idx + 1, (*size - (idx + 1)) * sizeof(void *));
            (*size)--;
            return true;
        }
    }

    return false;
}

bool arrayRemove(Array *array, void *element)
{
    if (array) {
        void **arr = array->arr;
        int *size = &array->size;
        void (*releaseFn)(void **) = array->releaseFn;
        for (int i = 0; i < *size; i++) {
            if (arr[i] == element) {
                /* Clean the item */
                if (releaseFn)
                    (*releaseFn)(&element);
                if (i < (*size - 1))
                    memmove(arr + i, arr + i + 1, (*size - (i + 1)) * sizeof(void *));
                (*size)--;
                return true;
            }
        }
    }

    return false;
}

void arrayRelease(Array **array)
{
    if (*array) {
        void **arr = (*array)->arr;
        void (*releaseFn)(void **) = (*array)->releaseFn;
        if (releaseFn) {
            int *size = &(*array)->size;
            for (int i = 0; i < *size;)
                arrayRemoveAt((*array), i);
        }
        objectRelease(&arr);
        objectRelease(array);
    }
}

bool arraySet(Array *array, void *element, int idx)
{
    if (array && idx < array->size) {
        void **arr = array->arr;
        void (*releaseFn)(void **) = array->releaseFn;
        if (releaseFn)
            releaseFn(&(arr[idx]));
        arr[idx] = element;
        return true;
    }

    return false;
}

bool arrayContainsStr(Array *array, const char *str)
{
    int len = (array ? array->size : 0);
    for (int i = 0; i < len; i++) {
        if (stringEquals(str, arrayGet(array, i)))
            return true;
    }

    return false;
}

Array *arrayStrCopy(Array *strArr)
{
    Array *ret = NULL;
    if (strArr) {
        int len = strArr->size;
        if (len > 0) {
            ret = arrayNew(objectRelease);
            for (int i = 0; i < len; i++)
                arrayAdd(ret, stringNew(arrayGet(strArr, i)));
        }
    }

    return ret;
}

void *arrayGet(Array *array, int idx)
{
    if (array && idx < array->size)
        return array->arr[idx];

    return NULL;
}

int arrayGetIdx(Array *array, void *element)
{
    if (array) {
        void **arr = array->arr;
        int size = array->size;
        for (int i = 0; i < size; i++) {
            if (arr[i] == element)
                return i;
        }
    }

    return -1;
}
