/* Write a C program to remove leading and trailing spaces from a string in place.*/
#include <stdio.h>
#include <string.h>

static char *
remove_space(char *str) 
{
    int s = 0;
    int e = 0;
    size_t len = 0;

    /* Check if there are no leading / trailing spaces */
    if (str[0] != ' ' && str[strlen(str)-1] != ' ')
        return str;

    for (s = 0; str[s] == ' '; s++);
    str = &str[s];
    len = strlen(str) - 1;
    for (e = len; str[e] == ' '; e--);
    str[++e] = '\0';
    return str;
}

int main() {
    char str[] = "   Hello Saimohan rao             ";
    printf("string len:%d\n", strlen(str));
    char *new;
    new = remove_space(str);
    printf("%s. strlen:%d\n", new, strlen(new));
}
