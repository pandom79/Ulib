#ifndef ULIB_H
#define ULIB_H

/**
 * @brief This library provides some functions to handle the following components:<br>
 * <ul>
 * <li>string</li>
 * <li>array</li>
 * <li>hash table</li>
 * <li>date and time</li>
 * </ul>
 *
 * @file ulib.h
 * @author Domenico Panella <pandom79@gmail.com>
 * @section License
 *
 * Copyright (C) 2021,<br>
 * This program is free software.<br>
 * You can redistribute it and/or modify it under the terms of the GNU General Public License version 3.<br>
 * See http://www.gnu.org/licenses/gpl-3.0.html for full license text.
 *
*/

#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <sys/time.h>
#include <stddef.h>
#include <errno.h>
#include <math.h>
#include <sys/types.h>
#include <inttypes.h>

/* TYPES */

/** @struct Array
 *  @brief This structure contains the data to handle an array of generic pointers.
 *  @var Array::arr
 *  It represents the real array of generic pointers.
 *  @var Array::size
 *  It represents the size of 'arr' members
 *  @var Array::releaseFn
 *  It represents a generic pointer to release function.
 */
typedef struct {
    void **arr;
    int size;
    void (*releaseFn)(void **);
} Array;

/** @struct Time
 *  @brief This structure represents a simple calendar time, or an elapsed time, with milliseconds resolution.
 *  @var Time::sec
 *  It represents the number of whole seconds elapsed since the epoch (calendar time).
 *  @var Time::milliSec
 *  It represents the number of milliseconds elapsed since the time given by the Time::sec member.
 *  @var Time::durationSec
 *  It represents the number of whole seconds elapsed since some other starting point (elapsed time).
 *  @var Time::durationMillisec
 *  It represents the number of milliseconds elapsed since the time given by the Time::durationSec member.
 */
typedef struct {
    long *sec;
    long *milliSec;
    long *durationSec;
    long *durationMillisec;
} Time;

/** @struct Ht
 *  @brief This structure represents a dynamic hash table with separate chaining.
 *  @brief <b>Key addition management</b>.<br>
 *  When the keys will achieve the 3/4 of the hash table capacity (<i>load factor 0.75</i>),<br>
 *  the latter will grow with the double of the previous capacity<br>
 *  to prevent the collisions as much as possible.<br><br>
 *  <b>Key remotion management</b>.<br>
 *  When the keys will achieve the 1/4 of the hash table capacity (<i>load factor 0.25</i>),<br>
 *  the latter will be the half of the previous size<br>
 *  to optimize memory usage.<br><br>
 *  For both, a key rehashing will be performed.<br>
 *  The current capacity will be never less than the initial capacity.
 *  @var Ht::initialCapacity
 *  It represents the initial hash table capacity.
 *  @var Ht::capacity
 *  It represents the hash table capacity.
 *  @var Ht::numOfItems
 *  It represents the number of the hash table items.
 *  @var Ht::htEntries
 *  It represents an array of HtEntry structure.
 *  @var Ht::releaseFn
 *  It represents a generic pointer to release function.
 */
typedef struct {
    int initialCapacity;
    int capacity;
    int numOfItems;
    Array *htEntries;
    void (*releaseFn)(void **);
} Ht;

/** @struct HtIterator
 *  @brief This structure represents a hash table iterator.
 *  @var HtIterator::ht
 *  It represents the associated hash table.
 *  @var HtIterator::hashIdx
 *  It represents the hash table key index.
 *  @var HtIterator::hashItemIdx
 *  It represents the hash table item index.
 */
typedef struct {
    Ht *ht;
    int hashIdx;
    int hashItemIdx;
} HtIterator;

// STRING

/**
 * Return a copy of 'src' string content.<br>
 * Return NULL if src is NULL.<br>
 * It must be freed by objectRelease() function.
 * @param[in] src
 * @return src copy
 */
char* stringNew(const char *src);

/**
 * Return true if a copy of 'src' string is set into 's' string, false otherwise.<br>
 * If 's' pointer was already allocated then it will be freed by objectRelease() before set the copy.
 * @param[in] s
 * @param[in] src
 * @return true/false
 */
bool stringSet(char **s, const char *src);

/**
 * Return true if 'src' string is copied into 's' string, false otherwise.<br>
 * This function assumes that 's' string has enough space to contain 'src' string.<br>
 * @param[in] s
 * @param[in] src
 * @return true/false
 */
bool stringCopy(char *s, const char *src);

/**
 * Return an immutable 'str' string.<br>
 * @param[in] str
 * @return const char *str
 */
const char* stringGet(char *str);

/**
 * Return true if 'src' string starts with 'c' character, false otherwise.
 * @param[in] src
 * @param[in] c
 * @return true/false
 */
bool stringStartsWithChr(const char *src, const char c);

/**
 * Return true if 'str1' string starts with 'str2' string, false otherwise.
 * @param[in] str1
 * @param[in] str2
 * @return true/false
 */
bool stringStartsWithStr(const char *str1, const char *str2);

/**
 * Return true if 'src' string ends with 'c' character, false otherwise.
 * @param[in] src
 * @param[in] c
 * @return true/false
 */
bool stringEndsWithChr(const char *src, const char c);

/**
 * Return true if 'str1' string ends with 'str2' string, false otherwise.
 * @param[in] str1
 * @param[in] str2
 * @return true/false
 */
bool stringEndsWithStr(const char *str1, const char *str2);

/**
 * Return true if 'str' string contains 'c' character, false otherwise.
 * @param[in] str
 * @param[in] c
 * @return true/false
 */
bool stringContainsChr(const char *str, const char c);

/**
 * Return true if 'str1' string contains 'str2' string, false otherwise.
 * @param[in] str1
 * @param[in] str2
 * @return true/false
 */
bool stringContainsStr(const char *str1, const char *str2);

/**
 * Converts in upper case the 'str' string content.
 * @param[in] str
 */
void stringToupper(char *str);

/**
 * Converts in lower case the 'str' string content.
 * @param[in] str
 */
void stringTolower(char *str);

/**
 * Return true if 'c' character is appended to 'str' string, false otherwise.
 * @param[in] str
 * @param[in] c
 * @return true/false
 */
bool stringAppendChr(char **str, const char c);

/**
 * Return true if 'str2' string is appended to 'str1' string, false otherwise.
 * @param[in] str1
 * @param[in] str2
 * @return true/false
 */
bool stringAppendStr(char **str1, const char *str2);

/**
 * Return true if 'c' character is prepended to 'str' string, false otherwise.
 * @param[in] str
 * @param[in] c
 * @return true/false
 */
bool stringPrependChr(char **str, const char c);

/**
 * Return true if 'str2' string is prepended to 'str1' string, false otherwise.
 * @param[in] str1
 * @param[in] str2
 * @return true/false
 */
bool stringPrependStr(char **str1, const char *str2);

/**
 * Return true if 'c' character is inserted into 'str' string at the position<br>
 * given by 'idx' parameter, false otherwise.
 * @param[in] str
 * @param[in] c
 * @param[in] idx
 * @return true/false
 */
bool stringInsertChrAt(char **str, const char c, int idx);

/**
 * Return true if 'str2' string is inserted into 'str1' parameter at the position <br>
 * given by 'idx', false otherwise.
 * @param[in] str1
 * @param[in] str2
 * @param[in] idx
 * @return true/false
 */
bool stringInsertStrAt(char **str1, const char *str2, int idx);

/**
 * Remove from 'str' string the characters defined in 'sep' string starting from left.<br>
 * If 'sep' is NULL then will be used all the following values:<br>
 * "\t": Horizontal Tab<br>
 * "\n": Newline<br>
 * "\v": Vertical Tab<br>
 * "\f": Formfeed Page Break<br>
 * "\r": Carriage Return<br>
 * " " : Blank<br>
 * @param[in] str
 * @param[in] sep
 * @return str
 */
char* stringLtrim(char *str, const char *sep);

/**
 * Remove from 'str' string the characters defined in 'sep' string starting from right.<br>
 * If 'sep' is NULL then will be used all the following values:<br>
 * "\t": Horizontal Tab<br>
 * "\n": Newline<br>
 * "\v": Vertical Tab<br>
 * "\f": Formfeed Page Break<br>
 * "\r": Carriage Return<br>
 * " " : Blank<br>
 * @param[in] str
 * @param[in] sep
 * @return str
 */
char* stringRtrim(char *str, const char *sep);

/**
 * Remove from 'str' string the characters defined in 'sep' string in both left and right.<br>
 * If 'sep' is NULL then will be used all the following values:<br>
 * "\t": Horizontal Tab<br>
 * "\n": Newline<br>
 * "\v": Vertical Tab<br>
 * "\f": Formfeed Page Break<br>
 * "\r": Carriage Return<br>
 * " " : Blank<br>
 * @param[in] str
 * @param[in] sep
 * @return str
 */
char* stringTrim(char *str, const char *sep);

/**
 * Return the index of 'c' character from 'str' string, -1 otherwise.
 * @param[in] str
 * @param[in] c
 * @return integer
 */
int stringIndexOfChr(const char *str, const char c);

/**
 * Return the index of the first occurrence of 'str2' string from 'str1' string, -1 otherwise.
 * @param[in] str1
 * @param[in] str2
 * @return integer
 */
int stringIndexOfStr(const char *str1, const char *str2);

/**
 * Return the last index of 'c' character from 'str' string, -1 otherwise.
 * @param[in] str
 * @param[in] c
 * @return integer
 */
int stringLastIndexOfChr(const char *str, const char c);

/**
 * Return the last index of 'str2' string from 'str1' string, -1 otherwise.
 * @param[in] str1
 * @param[in] str2
 * @return integer
 */
int stringLastIndexOfStr(const char *str1, const char *str2);

/**
 * Return a substring of the 'str' string starting <br>
 * from 'startIdx' parameter value to 'endIdx' parameter value.<br>
 * Return NULL if the indexes are not valid.<br>
 * It must be freed by objectRelease() function.
 * @param[in] str
 * @param[in] startIdx
 * @param[in] endIdx
 * @return substring of str
 */
char* stringSub(const char *str, int startIdx, int endIdx);

/**
 * Replace the first occurrence of the 'c1' character with 'c2' character into 'str' string.
 * @param[in] str
 * @param[in] c1
 * @param[in] c2
 */
void stringReplaceChr(char **str, const char c1, const char c2);

/**
 * Replace all the occurrences of the 'c1' character with 'c2' character into 'str' string.
 * @param[in] str
 * @param[in] c1
 * @param[in] c2
 */
void stringReplaceAllChr(char **str, const char c1, const char c2);

/**
 * Replace the first occurrence of the 'str2' string with 'str3' string into 'str1' string.
 * @param[in] str1
 * @param[in] str2
 * @param[in] str3
 */
void stringReplaceStr(char **str1, const char *str2, const char *str3);

/**
 * Replace all the occurrences of the 'str2' string with 'str3' string into 'str1' string.
 * @param[in] str1
 * @param[in] str2
 * @param[in] str3
 */
void stringReplaceAllStr(char **str1, const char *str2, const char *str3);

/**
 * Return true if 'str1' is equals to 'str2', false otherwise.<br>
 * The test is case sensitive.
 * @param[in] str1
 * @param[in] str2
 * @return true/false
 */
bool stringEquals(const char *str1, const char *str2);

/**
 * Return true if the first 'n' bytes of the 'str1' string and 'str2' string are equal.<br>
 * The test is case sensitive.
 * @param[in] str1
 * @param[in] str2
 * @param[in] n
 * @return true/false
 */
bool stringEqualsN(const char *str1, const char *str2, size_t n);

/**
 * Return true if 'str1' is equals to 'str2', false otherwise.<br>
 * The test is case insensitive.
 * @param[in] str1
 * @param[in] str2
 * @return true/false
 */
bool stringEqualsIgnCase(const char *str1, const char *str2);

/**
 * Return true if the first 'n' bytes of the 'str1' string and 'str2' string are equal.<br>
 * The test is case insensitive.
 * @param[in] str1
 * @param[in] str2
 * @param[in] n
 * @return true/false
 */
bool stringEqualsIgnCaseN(const char *str1, const char *str2, size_t n);

/**
 * Free a generic 'ptr' pointer.<br>
 * It will be assigned to NULL to handle an eventual double free error.
 * @param[in] ptr
 */
void objectRelease(void **ptr);

/**
 * Return an array of strings splitting 'str' string using 'token' string as a delimiter.<br>
 * Return NULL if the 'token' string is not found.<br>
 * The array elements will be allocate or not according 'alloc' parameter value.<br>
 * It must freed by arrayRelease() function which will also free eventual allocate elements inside.
 * @param[in] str
 * @param[in] token
 * @param[in] alloc
 * @return Array
 */
Array* stringSplit(char *str, const char *token, bool alloc);

/**
 * Return an array of two elements splitting once 'str' string using 'token' string as a delimiter.<br>
 * Return NULL if the 'token' string is not found.<br>
 * It must freed by arrayRelease() function.
 * @param[in] str
 * @param[in] token
 * @return Array
 */
Array* stringSplitFirst(char *str, const char *token);

/**
 * Return a string which represents the size of a resource.<br>
 * Return NULL if the 'size' parameter value is less than zero.<br>
 * It must freed by objectRelease() function.
 * @param[in] size
 * @return char*
 */
char* stringGetFileSize(off_t size);

// ARRAY

/**
 * Return an array.<br>
 * If the array contains elements of the same type then<br>
 * you can pass a function pointer which will be automatically called<br>
 * when we remove or set the element or when we release the whole array.<br>
 * It's optional thus can accept NULL value.<br>
 * It must freed by arrayRelease() function.<br>
 * @param[in] releaseFn
 * @return Array
 */
Array* arrayNew(void (*releaseFn)(void **));

/**
 * Return an array of a number of elements given by 'amount' parameter value.<br>
 * If the array contains elements of the same type then<br>
 * you can pass a function pointer which will be automatically called<br>
 * when we remove or set the element or when we release the whole array.<br>
 * It's optional thus can accept NULL value.<br>
 * It must freed by arrayRelease() function.<br>
 * @param[in] amount
 * @param[in] releaseFn
 * @return Array
 */
Array* arrayNewWithAmount(int amount, void (*releaseFn)(void **));

/**
 * Return true if a generic 'ptr' pointer is added to 'arr' array, false otherwise.
 * @param[in] arr
 * @param[in] ptr
 * @return true/false
 */
bool arrayAdd(Array *arr, void *ptr);

/**
 * Return true if a generic 'ptr' pointer is added as first element of 'arr' array, false otherwise.
 * @param[in] arr
 * @param[in] ptr
 * @return true/false
 */
bool arrayAddFirst(Array *arr, void *ptr);

/**
 * Return true if the element at the 'idx' position is removed from 'arr' array, false otherwise.
 * @param[in] arr
 * @param[in] idx
 * @return true/false
 */
bool arrayRemoveAt(Array *arr, int idx);

/**
 * Return true if a generic 'ptr' pointer is removed from 'arr' array, false otherwise.
 * @param[in] arr
 * @param[in] ptr
 * @return true/false
 */
bool arrayRemove(Array *arr, void *ptr);

/**
 * Free an Array structure.<br>
 * If the array contains a release function pointer then <br>
 * will be freed the elements inside as well.
 * @param[in] arr
 */
void arrayRelease(Array **arr);

/**
 * Return true if the 'element' is set into 'arr' array at the 'idx' position, false otherwise.<br>
 * @param[in] arr
 * @param[in] element
 * @param[in] idx
 * @return true/false
 */
bool arraySet(Array *arr, void *element, int idx);

/**
 * Return true if the 'arr' array contains 'str' string, false otherwise.<br>
 * @param[in] arr
 * @param[in] str
 * @return true/false
 */
bool arrayContainsStr(Array *arr, const char *str);

/**
 * Return a copy of the 'arr' array.<br>
 * It must be freed by arrayRelease() function.
 * @param[in] arr
 * @return Array
 */
Array* arrayStrCopy(Array *arr);

/**
 * Return a generic pointer to the array element at the 'idx' position, NULL otherwise.
 * @param[in] arr
 * @param[in] idx
 * @return generic pointer
 */
void* arrayGet(Array *arr, int idx);

/**
 * Return the element's index of the array, -1 otherwise.
 * @param[in] arr
 * @param[in] element
 * @return integer
 */
int arrayGetIdx(Array *arr, void *element);

/* DATE AND TIME  */

/**
 * Suspends the execution of the calling thread for 'ms' milliseconds.<br>
 * On successfully sleeping for the requested interval, returns 0,<br>
 * otherwise  it returns -1, with errno set to indicate the error.
 * @param[in] ms
 * @return integer
 */
int msleep(long ms);

/**
 * Return the current time if 'time' parameter is NULL, otherwise an its copy.<br>
 * It must be freed by timeRelease() function;
 * @param[in] time
 * @return Time
 */
Time* timeNew(Time *time);

/**
 * Set into 'time1' parameter a copy of the 'time2' parameter.<br>
 * If 'time1' was not NULL then will be freed by timeRelease() function before set the copy.<br>
 * @param[in] time1
 * @param[in] time2
 */
void timeSet(Time **time1, const Time *time2);

/**
 * Free a Time structure.
 * @param[in] time
 */
void timeRelease(Time **time);

/**
 * Return a string which represents the time given by 'time' in the format given by 'format' parameter value.<br>
 * If 'hasMillisec' parameter is true then will be added the milliseconds as well.<br>
 * The format string follows strftime() function specifics.
 * @param[in] time
 * @param[in] hasMillisec
 * @param[in] format
 * @return char*
 */
char* stringGetTimeStamp(Time *time, bool hasMillisec, const char *format);

/**
 * Return a string which represents the elapsed time between 'timeEnd' and 'timeStart'.
 * @param[in] timeEnd
 * @param[in] timeStart
 * @return char*
 */
char* stringGetDiffTime(Time *timeEnd, Time *timeStart);

// HASHTABLE

/**
 * Return an hashtable.<br>
 * If the hash table contains elements of the same type then<br>
 * you can pass a function pointer which will be automatically called<br>
 * when we remove or set the element or when we release the whole hash table.<br>
 * It's optional thus can accept NULL value.<br>
 * It must freed by htRelease() function.<br>
 * About the initial capacity, it is highly recommended set a number<br>
 * which must not represent a power of 2 to avoid the collisions as much as possible.<br>
 * A prime number is preferable.<br>
 * @param[in] initialCapacity
 * @param[in] releaseFn
 * @return Ht
 */
Ht* htNew(int initialCapacity, void (*releaseFn)(void **));

/**
 * Free an Ht structure.<br>
 * If the hash table contains a release function pointer then <br>
 * will be freed the items inside as well.<br>
 * @param[in] ht
 */
void htRelease(Ht **ht);

/**
 * Return the value of the key if the 'key' exists, NULL otherwise.<br>
 * @param[in] ht
 * @param[in] key
 * @return void*
 */
void* htGet(Ht *ht, const char *key);

/**
 * Return true if a generic 'value' pointer is added
 * to the 'ht' hash table with 'key' key, false otherwise.<br>
 * Null, empty or duplicate keys are not allowed.<br>
 * @param[in] ht
 * @param[in] key
 * @param[in] value
 * @return true/false
 */
bool htAdd(Ht **ht, const char *key, void *value);

/**
 * Return true if a 'key' key is removed from 'ht' hash table, false otherwise.<br>
 * @param[in] ht
 * @param[in] key
 * @return true/false
 */
bool htRemove(Ht **ht, const char *key);

/**
 * Return true if 'value' element is set into 'ht' hash table with 'key' key, false otherwise.<br>
 * @param[in] ht
 * @param[in] key
 * @param[in] value
 * @return true/false
 */
bool htSet(Ht **ht, const char *key, void *value);

/**
 * Return the hast table iterator if 'ht' hash table is not null, NULL otherwise.<br>
 * It must be freed by objectRelease() function.<br>
 * @param[in] ht
 * @return HtIterator*
 */
HtIterator* htGetIterator(Ht *ht);

/**
 * Return the value of the next hash table key, NULL if the iterator is terminated.
 * @param[in] htIterator
 * @return void*
 */
void* htGetNext(HtIterator *htIterator);

/**
 * Reset the hash table iterator for the next iteration cycle.
 * @param[in] ht
 * @param[in] htIterator
 */
void htIteratorReset(Ht *ht, HtIterator *htIterator);

#endif // ULIB_H
