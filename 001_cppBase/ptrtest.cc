#include <stdio.h>
int main() {
    struct A { char a; int b; };
    A* p = new A;
    int a = sizeof(p);

    printf("%d\n", a);
}