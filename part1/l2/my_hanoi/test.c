int main(){
    int i = 1;
    int x = 0;

    x += ++i;
    printf("pre %d, i: %d\n", x, i);

    x += i++;
    printf("suf %d, i: %d\n", x, i);
}
