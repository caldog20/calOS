#include <string.h>

// Function to swap two numbers
static void swap(char *x, char *y) {
    char t = *x;
    *x = *y;
    *y = t;
}

// Function to reverse `buffer[i…j]`
static char *reverse(char *buffer, int i, int j) {
    while (i < j) {
        swap(&buffer[i++], &buffer[j--]);
    }

    return buffer;
}

static int abs(int v) { return v * ((v > 0) - (v < 0)); }

static char *_strrev(char *str) {
    int i;
    int len = 0;
    char c;
    if (!str) return NULL;
    while (str[len] != '\0') {
        len++;
    }
    for (i = 0; i < (len / 2); i++) {
        c = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = c;
    }
    return str;
}

char *itoa(int i, char *strout, int base) {
    char *str = strout;
    int digit, sign = 0;
    if (i < 0) {
        sign = 1;
        i *= -1;
    }
    while (i) {
        digit = i % base;
        *str = (digit > 9) ? ('A' + digit - 10) : '0' + digit;
        i = i / base;
        str++;
    }
    if (sign) {
        *str++ = '-';
    }
    *str = '\0';
    _strrev(strout);
    return strout;
}