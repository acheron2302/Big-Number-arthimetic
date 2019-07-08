#ifndef MULTIPLY
#define MULTIPLY

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

// @notice add two big number
// @params _string1 the first big number
// @params _string2 the second big number
// @dev convert the number to string, then reverse them to do calculate in
// little endian after that add them like what you learn from first grade
// @return the pointer to big endian of the result
char *add(char *_string1, char *_string2) {
    int length_1, length_2;
    int i;
    char *p1, *p2;

    // @notice The longer string is p2 and length_2
    // The shorter string is p1 and length_1
    // @dev input reverse str1 and str2 to calculate in little endian
    if (strlen(_string1) > strlen(_string2)) {
        length_1 = strlen(_string2);
        length_2 = strlen(_string1);
        p1 = (_string2);
        p2 = (_string1);
    } else {
        length_1 = strlen(_string1);
        length_2 = strlen(_string2);
        p1 = (_string1);
        p2 = (_string2);
    }

    char buffer[5];
    bool remem = false;
    int longest_length = (strlen(_string1) < strlen(_string2)) ? strlen(_string2) : strlen(_string1);

    char *result = (char *)calloc(longest_length + 3, sizeof(char));
    // set null pointer

    for (i = 0; i < strlen(_string1) || i < strlen(_string2) || remem == true; p1++, p2++, i++) {
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

    // reverse the result show it return big endian
    result[i + 1] = '\0';
    return result;
}

char *mul(char *str1, char *str2) {
    int length_1, length_2;
    char *p1, *p2;
    char *temp;

    // @notice The longer string is p2 and length_2
    // The shorter string is p1 and length_1
    // @dev input reverse str1 and str2 to calculate in little endian
    if (strlen(str1) > strlen(str2)) {
        length_1 = strlen(str2);
        length_2 = strlen(str1);
        p1 = rev(str2);
        p2 = rev(str1);
    } else {
        length_1 = strlen(str1);
        length_2 = strlen(str2);
        p1 = rev(str1);
        p2 = rev(str2);
    }

    // malloc array
    char *result = (char *)calloc(length_1 + length_2 + 3, sizeof(char));
    // set null pointer

    // loop for every element in the list
    for (int i = 0; i < length_1; i++, p1++) {
        int num1 = *p1 - '0';
        int remainder = 0;
        char *array = (char *)calloc(length_2 + 3, sizeof(char));

        for (int x = 0; x < i; x++)
            array[x] = '0';

        for (int x = i; p2[x - i] != 0 || remainder > 0; x++) {
            int product;

            if (p2[x - i] == '\0') {
                product = 0;
            } else {
                int num2 = p2[x - i] - '0';
                product = num1 * num2;
            }

            if (remainder > 0) {
                product += remainder;
                remainder = 0;
            }

            if (product >= 10) {
                remainder = product / 10;
                product = product % 10;
            }
                array[x] = digits[product];
        }

        temp = result;
        result = add(array, result);
        free(temp);
        free(array);
    }

    return rev(result);
}

char *factorial(char *string) {
    char *str;
    char *result;
    char *temp;
    result = "1";
    str = "0";
    str = rev(add(str, "1"));
    result = mul(result, str);

    for (int i = 0; i < atoi(string) - 1; i++) {
        temp = str;
        str = rev(add(str, "1"));
        free(temp);

        temp = result;
        result = mul(result, str);
        free(temp);
    }

    free(str);
    return result;
}
#endif /* end of include guard */
