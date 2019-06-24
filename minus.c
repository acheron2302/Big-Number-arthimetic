#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "header.h"

char *subtract(char *num1, char *num2) {
    int length1 = strlen(num1);
    int length2 = strlen(num2);
    int MAX_LENGTH;
    char *p1;
    char *p2;
    char *result;
    bool remainder = false;
    bool negative = false;

    // check if num1 is greater than num2 if true then the result is a negative number
    if(
        (length1 < length2) ||
        (num1[length1 - 1] < num2[length2 - 1] && length1 == length2)
    ) {
        negative = true;
    }

    // swap if the result is a negative number
    if(negative == true) {
        p1 = rev(num2);
        p2 = rev(num1);
    } else {
        p1 = rev(num1);
        p2 = rev(num2);
    }

    MAX_LENGTH = (strlen(num1) > strlen(num2)) ? strlen(num1) : strlen(num2);

    result = (char *)calloc(MAX_LENGTH, sizeof(char));

    for(int i = 0; i < MAX_LENGTH; p1++, p2++, i++) {
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

    for (; result[strlen(result) - 1] == '0';) {
        result[strlen(result) - 1] = '\0';
    }

    if(negative == true) {
        result[strlen(result)] = '-';
    }

    rev(num1);
    rev(num2);
    return rev(result);
}
