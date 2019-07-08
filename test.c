#include "minus.c"
#include "multiply.c"
#include "division.c"

int main() {
    char nums2[MAX_STR];
    char nums1[MAX_STR];
    printf("Please insert first number: "); scanf("%s", nums1);
    printf("Please insert second number: "); scanf("%s", nums2);

    char *result = division(nums1, nums2);
    printf("the result is: ");
    for(int i = 0; i < strlen(result); i++) {
        if(i == 0 && result[0] == '0')
            continue;
        printf("%c", result[i]);
    }

    printf("\n");
    free(result);
}
