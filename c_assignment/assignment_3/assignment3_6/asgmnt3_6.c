#include <stdio.h>
#include <ctype.h>

int fun_alpha_num(char c) {
    return (isalnum(c) ? 1 : 0);
}

int main() {
    char ch;
    printf("Enter a character: ");
    scanf(" %c", &ch);
    if (fun_alpha_num(ch))
        printf("%c is Alphanumeric\n", ch);
    else
        printf("%c is Not Alphanumeric\n", ch);
    return 0;
}

