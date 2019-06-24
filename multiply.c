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
char *add(char *_string1, char *_string2) {
    char *p1, *p2;
    int length_1, length_2;
    // @notice The longer string is p2 and length_2
    // The shorter string is p1 and length_1
    // @notice we are going to do math on little endian
    // so we need to reverse str1 and str2
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

    // reverse the result show it return big endian
    return result;
}

// @params _string1 the first big number
// @params _string2 the second big number
// @dev first convert the string into little endian array and then
// do the multiply like third grade
// @return *result the array of char that represent the number
char *mul(char *str1, char *str2) {
    int length_1, length_2;
    char *p1, *p2;

    // @notice The longer string is p2 and length_2
    // The shorter string is p1 and length_1
    // @notice we are going to do math on little endian
    // so we need to reverse str1 and str2
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


    // @dev malloc array return
    char *result = (char *)malloc(MAX_STR * sizeof(char));

    // loop for every element in the list
    for (int i = 0; i < length_1; i++, p1++) {
        int num1 = *p1 - '0';
        char *array = (char *)malloc(MAX_STR * sizeof(char));
        // @notice push the first LSB by zero to the number of i
        // just like multiply
        for (int x = 0; x < i; x++)
            array[x] = '0';
        int remainder = 0;

        // @notice start from the number i,
        // check if the the array p2 at xth element is NULL
        // if there is still a remainder then add it to the MSB
        for (int x = i; p2[x - i] != 0 || remainder > 0; x++) {
            int product;
            // check if the element of p2 is NULL if yes add 1 to product
            // if not then convert string to number and then multiply by num1
            if(p2[x - i] == '\0') {
                product = 0;
            } else {
                int num2 = p2[x - i] - '0';
                product = num1 * num2;
            }

            if (remainder > 0) {
                product += remainder;
                remainder = 0;
            }

            // if the product is great than 10 then
            // convert it to a singer digit and
            // carry the rest to the next digit
            if (product >= 10) {
                remainder = product / 10;
                product = product % 10;
            }
            array[x] = digits[product];
        }

        // add the result the the previous result
        result = add(array, result);
    }


    rev(str1);
    rev(str2);
    return rev(result);
}

// @param string: the number you need to factorial
char *factorial(char *string) {
    // This variable is an incremental number to multiply the result
    char *str = (char *)malloc(4 * sizeof(char));
    // This variable is a pointer to another heap so that we can free it
    char *temp;
    // Initialize the result
    char *result = (char *)malloc(MAX_STR * sizeof(char));

    // set result to 1
    result = "1";
    str = "0";

    for (int i = 0; i < atoi(string); i++) {
        temp = str;
        str = rev(add(str, "1"));
        free(temp);

        result = mul(result, str);
    }

    free(str);
    return result;
}
