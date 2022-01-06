#include <stdio.h>
    int main() {
        char ch;
        int a = 10, b = 20, c = 0, i = 0;
        int f;
        for (i; i < 5; i++){
            printf("Enter math operation: ");
            scanf(" %c", &ch);
            switch(ch){
                case '+': f = a + b; printf("ch = %c\n", ch); printf("f = %d\n", f); break;
                case '-': f = a - b; printf("ch = %c\n", ch); printf("f = %d\n", f); break;
                case '*': f = a * b; printf("ch = %c\n", ch); printf("f = %d\n", f); break;
                case '/': f = a / b; printf("ch = %c\n", ch); printf("f = %d\n", f); break;
                default: printf("invalid operator\n");
            }
            fflush(stdin); 
        }
    return c;
    }
        
