/**
 * @file
 * @author Kishou Yusa
 * @date 2019-06-28
 * @brief Addition with 2 big number
*/

#ifndef PLUS
#define PLUS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "header.h"

/**
 * @brief Addition between two big number
 *
 * Convert the number to string, then reverse them to do calculate in little endian after that add them like what you learn from first grade
 * @param _string1 The pointer first big number
 * @param _string2 The pointer second big number
 * @return The pointer to big endian of the result
 * @warning remember to free the pointer because it use max(|_string1|, |_string1|) space in heap
*/
char *plus(char *_string1, char *_string2);

char *plus(char *_string1, char *_string2) {
    char *p1, *p2;
    int length_1, length_2;
    char buffer[5];
    bool remem = false;

    // @dev The longer string is p2 and with length length_2,
    //         the shorter string is p1 and with length length_1
    // Input reverse str1 and str2 to calculate in little endian
    if (strlen(_string1) > strlen(_string2)) {
        length_1 = strlen(_string2);
        length_2 = strlen(_string1);
        p1 = rev(_string2);
        p2 = rev(_string1);
    } else {
        length_1 = strlen(_string1);
        length_2 = strlen(_string2);
        p1 = rev(_string1);
        p2 = rev(_string2);
    }

    char *result = (char *)calloc(length_2 + 2, sizeof(char)); /// @var The pointer to the heap that return the result of this arthimetic

    // loop to calculate multiply
    // @dev it gonna run through every digits of the longest length number
    //      to do addition with digits from smaller length number
    //      and then add 1 to the LSB if the remainder is true
    for (int i = 0; i < length_2 || remem == true; p1++, p2++, i++) {
        // convert ascii to integer
        char num1, num2;
        if (*p1 == '\0' && *p2 == '\0') {
            num1 = 0;
            num2 = 0;
            p1--;
            p2--;
        } else if (*p1 == '\0') {
            num1 = 0;
            num2 = *p2 - '0';
            p1--;
        } else if (*p2 == '\0') {
            num2 = 0;
            num1 = *p1 - '0';
            p2--;
        } else {
            num1 = *p1 - '0';
            num2 = *p2 - '0';
        }

        int sum = num1 + num2;
        // add 1 when there is bool remem is true
        if (remem == true) {
            sum += 1;
            remem = false;
        }

        // if sum >= 10 then remem is true and take the remainder of result
        if (sum >= 10) {
            remem = true;
            sum = sum % 10;
        }

        // insert the sum digit to the result
        result[i] = digits[sum];
    }

    // reverse back the 2 input to it original big endian
    rev(_string1);
    rev(_string2);

    // reverse the result so it is in big endian
    return rev(result);
}
#endif /* end of include guard */
