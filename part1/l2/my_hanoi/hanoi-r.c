#include <stdio.h>

int hanoi(int n, char from, char to, char via){
    if (n == 1){
        printf("%c -> %c\n", from, to);
        return 1;
    }
    else{
        int first_steps = hanoi(n-1, from, via, to);
        printf("%c -> %c\n", from, to);
        int last_steps = hanoi(n-1, via, to, from);
        return first_steps + 1 + last_steps;
    }

}
