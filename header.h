#ifndef HEADER
#define HEADER
#define MAX_STR 1000

// digit array to convert from integer to char
char digits[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

char *rev(char *string) {
    char *p1, *p2;

    if (! string || ! *string)
        return string;
    for (p1 = string, p2 = string + strlen(string) - 1; p2 > p1; p1++, p2--) {
        *p1 ^= *p2;
        *p2 ^= *p1;
        *p1 ^= *p2;
    }

    return string;
}

#endif /* end of include guard */
