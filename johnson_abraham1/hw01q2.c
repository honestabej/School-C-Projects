/* This C program demonstrates the switch statement without using breaks. */
#include <stdio.h>
    int main() {
        char ch = '+';
        int a = 10, b = 20;
        double f;
        printf("ch = %c\n", ch);
        switch (ch) {
            case '+': f = a + b; printf("f = %d\n", f);
            case '-': f = a - b; printf("f = %d\n", f);
            case '*': f = a * b; printf("f = %d\n", f);
            case '/': f = a / b; printf("f = %d\n", f);
            default: printf("invalid operator\n");
        }
        ch = '-';
        printf("ch = %c\n", ch);
        switch (ch) {
            case '+': f = a + b; printf("f = %d\n", f);
            case '-': f = a - b; printf("f = %d\n", f);
            case '*': f = a * b; printf("f = %d\n", f);
            case '/': f = a / b; printf("f = %d\n", f);
            default: printf("invalid operator\n");
        }
        ch = '*';
        printf("ch = %c\n", ch);
        switch (ch) {
            case '+': f = a + b; printf("f = %d\n", f);
            case '-': f = a - b; printf("f = %d\n", f);
            case '*': f = a * b; printf("f = %d\n", f);
            case '/': f = a / b; printf("f = %d\n", f);
            default: printf("invalid operator\n");
        } 
        ch = '/';
        printf("ch = %c\n", ch);
        switch (ch) {
            case '+': f = a + b; printf("f = %d\n", f);
            case '-': f = a - b; printf("f = %d\n", f);
            case '*': f = a * b; printf("f = %d\n", f);
            case '/': f = a / b; printf("f = %d\n", f);
            default: printf("invalid operator\n");
        } 
        ch = '%';
        printf("ch = %c\n", ch);
        switch (ch) {
            case '+': f = a + b; printf("f = %d\n", f);
            case '-': f = a - b; printf("f = %d\n", f);
            case '*': f = a * b; printf("f = %d\n", f);
            case '/': f = a / b; printf("f = %d\n", f);
            default: printf("invalid operator\n");
        } 
    }