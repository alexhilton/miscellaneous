#include <stdio.h>

void dump_array(char **str) {
    while (**str != '\0') {
        printf("%c\n", **str);
        (*str)++;
    }
}

/*
 * demonstrate the differences between pointer and array
 */
int main(void) {
    char str[] = {'h', 'e', 'l', 'l', 'o', '\0'};
    char *p = str;
    dump_array(&str);

    return 0;
}
