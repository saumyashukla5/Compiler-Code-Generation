#include <stdio.h>
int main() {
    int num = 121, temp, rev = 0, digit;
    temp = num;
    while(num != 0) {
        digit = num % 10;
        rev = rev * 10 + digit;
        num = num / 10;
    }
    if(temp == rev)
        printf("Palindrome\n");
    else
        printf("Not Palindrome\n");
    return 0;
}