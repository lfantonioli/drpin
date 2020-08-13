#include<stdio.h>

int fib0(){
    return 0;
}
int fib1(){
    return 1;
}
int fib2(){
    return fib1() + fib0();
}
int fib3(){
    return fib2() + fib1();
}
int fib4(){
    return fib3() + fib2();
}
int fib5(){
    return fib4() + fib3();
}
int fib6(){
    return fib5() + fib4();
}

void print(int value){
    printf("The 6th fibonacci number: %d\n", value);
}


int main(int argc, char const *argv[])
{
    int value = fib6();
    print(value);
    return 0;
}

