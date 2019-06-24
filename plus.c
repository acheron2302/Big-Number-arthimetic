#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "header.h"

// @notice add two big number
// @params _string1 the first big number
// @params _string2 the second big number
// @dev convert the number to string, then reverse them to do calculate in
// little endian after that add them like what you learn from first grade
// @return the pointer to big endian of the result
char *plus(char *_string1, char *_string2) {
    char *p1, *p2;
    int length_1, length_2;
    // @notice The longer string is p2 and length_2
    // The shorter string is p1 and length_1
    // @dev input reverse str1 and str2 to calculate in little endian
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
    char buffer[5];
    bool remem = false;

    char *result = (char *)malloc(MAX_STR * sizeof(char));
    for (int i = 0; i < strlen(_string1) || i < strlen(_string2) || remem == true; p1++, p2++, i++) {
        // convert ascii to integer for calc
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
        // add the sum to the result
        result[i] = digits[sum];
    }

    // reverse back the 2 input to normal
    rev(_string1);
    rev(_string2);
    // reverse the result show it return big endian
    return rev(result);
}
