#ifndef MINUS
#define MINUS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "header.h"

char *subtract(char *_num1, char *_num2) {
    int length1 = strlen(_num1);
    int length2 = strlen(_num2);
    char *p1;
    char *p2;
    char *result;
    bool remainder = false;
    bool negative = false;



    // check if _num1 is smaller than _num2 if true then the result is a negative number
    // first check if number2 is longer than number1
    if( length1 < length2) {
        negative = true;
    } else if (length1 == length2) { // second if number2 and number1 length is equal
        // If the first chracter that does not match have the lower value
        // in _num1 than _num2 then that _num1 is greater than _num2
        if(strcmp(_num1, _num2) < 0)
            negative = true;
    }

    // swap 2 number if the result is a negative number
    if(negative == true) {
        p1 = rev(_num2);
        p2 = rev(_num1);
    } else {
        p1 = rev(_num1);
        p2 = rev(_num2);
    }


    // find the number that its length is longer
    int longest_length = (strlen(_num1) > strlen(_num2)) ? strlen(_num1) : strlen(_num2);

    result = (char *)calloc(longest_length + 2, sizeof(char));

    for(int i = 0; i < longest_length; p1++, p2++, i++) {
        int number1, number2;

        // convert ascii to integer for calc
        if (*p1 == '\0' && *p2 == '\0') {
            number1 = 0;
            number2 = 0;
            p1--;
            p2--;
        } else if (*p1 == '\0') {
            number1 = 0;
            number2 = *p2 - '0';
            p1--;
        } else if (*p2 == '\0') {
            number2 = 0;
            number1 = *p1 - '0';
            p2--;
        } else {
            number1 = *p1 - '0';
            number2 = *p2 - '0';
        }


        int subtract_result = number1 - number2;
        if (remainder == true) {
            subtract_result -= 1;
            remainder = false;
        }

        if (subtract_result < 0) {
            remainder = true;
            subtract_result = 10 - abs(subtract_result);
        }

        result[i] = digits[subtract_result];
    }

    if(negative == true) {
        result[strlen(result)] = '-';
    }

    rev(_num1);
    rev(_num2);
    return rev(result);
}
#endif /* end of include guard */
