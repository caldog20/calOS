#include <limits.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <tty.h>

static bool print(const char* data, size_t length) {
    // const unsigned char* bytes = (const unsigned char*) data;
    // for (size_t i = 0; i < length; i++)
    // 	if (putchar(bytes[i]) == EOF)
    // 		return false;
    // return true;
    terminal_writestring(terminal_request, data);
}

int printf(const char* str, ...) {
    va_list vl;
    int i = 0, j = 0;
    char buff[100] = {0}, tmp[20];
    char* str_arg;

    va_start(vl, str);
    while (str && str[i]) {
        if (str[i] == '%') {
            i++;
            switch (str[i]) {
                /* Convert char */
                case 'c': {
                    buff[j] = (char)va_arg(vl, int);
                    j++;
                    break;
                }
                /* Convert decimal */
                case 'd': {
                    itoa(va_arg(vl, int), tmp, 10);
                    strcpy(&buff[j], tmp);
                    j += strlen(tmp);
                    break;
                }
                /* Convert hex */
                case 'x': {
                    itoa(va_arg(vl, int), tmp, 16);
                    strcpy(&buff[j], tmp);
                    j += strlen(tmp);
                    break;
                }
                /* Convert octal */
                case 'o': {
                    itoa(va_arg(vl, int), tmp, 8);
                    strcpy(&buff[j], tmp);
                    j += strlen(tmp);
                    break;
                }
                /* copy string */
                case 's': {
                    str_arg = va_arg(vl, char*);
                    strcpy(&buff[j], str_arg);
                    j += strlen(str_arg);
                    break;
                }
            }
        } else {
            buff[j] = str[i];
            j++;
        }
        i++;
    }
    print(buff, strlen(buff));
    va_end(vl);
    return j;
}
