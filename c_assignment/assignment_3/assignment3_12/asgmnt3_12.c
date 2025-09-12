#include <stdio.h>
#include <ctype.h>

char CaseReverse(char c) {
    if (islower(c)) return toupper(c);
    else if (isupper(c)) return tolower(c);
    else return c;
}

int main() {
    char ch;
    printf("Enter a character: ");
    scanf(" %c", &ch);
    printf("Case reversed: %c\n", CaseReverse(ch));
    return 0;
}

