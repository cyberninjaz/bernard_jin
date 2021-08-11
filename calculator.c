#include <stdio.h>

int main() {
    int x, y;
    char op;
    char buf[100];
    printf("Put in 1 number: ");
    scanf("%d", &x);
    printf("\nPut in an operator:");
    scanf(" %c", &op);
    printf("\nPut in another number: ");
    scanf("%d", &y);
    float result;
    if(op == '+') {
        result = x + y;
    }
    else if(op == '-') {
        result = x - y;
    }
    else if(op == '*') {
        result = x * y;
    }
    else if(op == '/') {
        result = x / y;
    }
    else if(op == '^') {
        result = x ^ y;
    }
    else if(op == '%') {
        result = x % y;
    }
    printf("%d %c %d = %f", x, op, y, result);
}
