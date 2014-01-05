#include <stdio.h>
#include <string.h>

int str_util_cpy(char *dest, const char *from);
int str_util_cmp(char *dest, const char *from);

int main() {
    char to[1024];
    char *from = NULL;

    str_util_cpy(to, from);
    printf("this is a string %d\n", str_util_cmp(to, from));
    return 0;
}

int str_util_cpy(char *dest, const char *from) {
    if (from == NULL || dest == NULL) {
        return 0;
    }
    strcpy(dest, from);
    return 0;
}

int str_util_cmp(char *dest, const char *from) {
    if (from == NULL || dest == NULL) {
        return 0;
    }
    return strcmp(dest, from);
}
