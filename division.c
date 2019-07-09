/**
 * @file
 * @author Kishou Yusa
 * @brief alogrithm to divide 2 big number
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "multiply.c"
#include "minus.c"

/// Turn a chracter number into a number it correspond
int numlify(char number) {
    return number - '0';
}

/** @brief A function to multiply a big number with a single digit number
 *
 * It gonna loop through every element of the list and divide the each digit of the dividend by divisor
 *
 * Let the multplier be \f$ u = (u_{n}u_{n-1}...u_0) \f$ \textrm{with} \f$ n = ||num1|| \f$
 * result quotient be \f$ q = (q_{n+1}q_{n}...q_0)\f$
 * and the remainder \f$ r \f$
 *
 * From i = 0 to n + 1 do:
 * \f{eqnarray*} {
 *      q_i = (u_i \times num2 + remainder) \bmod 10 \\
 *      r = \frac{u_i \times num2 + remainder}{10} \\
 *      u_i = \left\{\begin{matrix}
 *            & 0   & \textrm{if} \quad i > n \\
 *            & u_i & \textrm{else}
 *            \end{matrix}\right.
 * \f}
 * @param *num1 the pointer to a big number
 * @param num2 a single digit number
 * @return The pointer to the result
 * @warning Remember to clear the result after it have been used
 */
char *single_mul1(char *num1, char num2) {
    // initilize the heap to return the result pointer to
    char *result = (char *)calloc(strlen(num1) + 2, sizeof(char));
    int number, product;
    int remainder = 0;

    for(int i = 0; i < strlen(num1) || remainder; i++) {
        if(i >= strlen(num1)) {
            number = 0;
        } else {
            number = numlify(num1[strlen(num1) - i - 1]);
        }

        product = number * num2 + remainder;
        remainder = product / 10;
        product = product % 10;

        result[strlen(num1) - i] = product + '0';
    }

    if(result[0] == 0)
        result[0] = '0';

    return result;
}

/// @brief A function to multiply a big number with a single digit number
/// Like @ref single_mul1 but no leading 0 (
/// \f$ \textrm{if} \quad q_{n+1} \equiv 0 \Rightarrow q_{n+1} = \emptyset \f$).
/// @copydetails single_mul1()
char *single_mul2(char *num1, char num2) {
    // initilize the heap to return the result pointer to
    char *result = (char *)calloc(strlen(num1) + 1, sizeof(char));
    int number, product;
    int remainder = 0;

    for(int i = 0; i < strlen(num1) || remainder; i++) {
        if(i >= strlen(num1)) {
            number = 0;
        } else {
            number = numlify(num1[strlen(num1) - i - 1]);
        }

        product = number * num2 + remainder;
        remainder = product / 10;
        product = product % 10;

        result[strlen(num1) - i - 1] = product + '0';
    }

    return result;
}

/**
 * @brief divsion of a big number by a single digit number
 *
 * @detail Let the dividend be \f$ u = (u_0u_1...u_{n-1}) \f$ with \f$ n = ||num1|| \f$,
 *  the divisor is a single number between 0 and 10
 * the quotient is \f$ q = (q_0q_1...q_{n})\f$ . If divisor is 0 return error,
 * if not do the following:
 * \f{eqnarray*} {
 *      q_i = \frac{u_i + remainder \times 10}{10}
 *      \quad \textrm{with} \quad 0 \leq i < ||u||\\
 *      r = (u_i + remainder \times 10) \bmod 10
 * \f}
 * @param *num1 the pointer the a big number
 * @param num2 a number that is between 0 and 10
 * @return The pointer to the heap that contain the quotient (or the remainder if return_remainder is true)
 * @warning Remember to clear the result after it have been used
 * @warning If @p num2 is zero then it will terminate the function and return back
 * > ERROR: CANNOT DIVIDE BY 0
 */
char *short_division(char *num1, char num2, bool return_remainder) {
    char *result = (char *)calloc(strlen(num1) + 1, sizeof(char));
    char division;
    char remainder;

    if (num2 == 0) {
        printf("ERROR: CANNOT DIVIDE BY 0\n");
        exit(1);
    } else {
        for(int i = 0; i < strlen(num1); i++) {
            division = ( remainder * 10 + numlify(num1[i]) ) / num2;
            remainder = ( remainder * 10 + numlify(num1[i]) ) % num2;
            result[i] = division + '0';
        }
    }


    if(!return_remainder) {
        return result;
    } else {
        result[0] = remainder + '0';
        result[1] = '\0';
        return result;
    }
}

char *division(char *num1, char *num2) {
    int x = 0;
    int len2 = strlen(num2);
    int d;

    // Find d so that nums2[0] >= 5
    if(num2[0] >= '5') {
        d = 1;
    } else {
        for (int i = 1; i <= 3; i++) {
            char *temp = single_mul2(num2, pow(2, i));
            if(temp[0] - '0' >= 5) {
                d = pow(2, i);
                free(temp);
                break;
            }
            free(temp);
        }
    }
    char quotient;
    char remain;

    // The result heap to return
    char *result = (char *)calloc(strlen(num1) - strlen(num2), sizeof(char));
    char *nums1 = single_mul1(num1, d);
    char *nums2 = single_mul2(num2, d);
    char *divisor;
    char *temp;

    // @param diff the different between the length of num1 and num2
    for(int i = 0; i <= (strlen(num1) - strlen(num2)); i++) {
        quotient = (numlify(nums1[i]) * 10 + numlify(nums1[i + 1])) / numlify(nums2[0]);
        remain = (numlify(nums1[i]) * 10 + numlify(nums1[i + 1])) % numlify(nums2[0]);

        divisor = (char *)calloc(len2 + 3, sizeof(char));
        // move the digits nums1 to the biggest digit that can be divided to nums2
        strncpy(divisor, nums1 + i, len2 + 1);

        // test if quotient equal to 10 or quotient * nums[length2 - 2] > 10 * remainder + nums1[diff + length2 - 2]
        if(quotient == 10 || quotient * numlify(nums2[1]) > 10 * remain + numlify(nums1[i + 2])) {
            quotient -= 1;
            remain += nums2[0];

            // Test again if the remain is bigger than or equal to 10
            if (remain < 10) {
                if(quotient == 10 || quotient * nums2[1] > 10 * remain + nums1[i + 2]) {
                    quotient -= 1;
                    remain += nums2[0];
                }
            }
        }

        char *product = single_mul1(nums2, quotient);

        temp = divisor;
        divisor = subtract(divisor, product);
        free(temp);
        free(product);

        // if the result of the last subtract is negative. Minus 1 to the quotient
        // and then add the divisor to the remainder
        if(divisor[0] == '-') {
            // calculate the absolute of divisor by remove the minus sign in the beginning
            memmove(divisor, divisor + 1, len2 + 1);
            // add NULL to the end of the divisor
            divisor[strlen(divisor) - 1] = '\0';

            /* There is a error occur when the nums2 first 2 digit is 0
            * so we fix it by remove the first 0 digit and do the subtract,
            * then we add the first 0 back to the result of that division
            */
            // this varialbe check if there is a need to add back 0 at the beginning after the subtract
            bool check_2 = 0;
            if(divisor[0] == '0' && divisor[1] == '0') {
                memmove(divisor, divisor + 1, len2);
                divisor[strlen(divisor) - 1] = '\0';
                check_2 = 1; // check_2 is true so that the next if statement is gonna execute
            }

            quotient -= 1;
            temp = divisor;
            divisor = subtract(nums2, divisor);
            free(temp);

            // add back 0 at the beginning to the result by move each digit by 1
            // and leave the first digit as 0
            if(check_2)
                memmove(divisor + 1, divisor, strlen(divisor));

            // let nums1 be the remainder concatenate with the next nums1[len2 + i + 1]
            // and repeat the loop if the condition haven't been satisfy
            memmove(nums1 + i, divisor, len2 + 1);
            free(divisor);
        }else{
            // let nums1 be the remainder concatenate with the next nums1[len2 + i + 1]
            // and repeat the loop if the condition haven't been satisfy
            memmove(nums1 + i, divisor, len2 + 1);
            free(divisor);
        }

        result[i] = quotient + '0';
    }

    free(nums1);
    free(nums2);
    return result;
}
