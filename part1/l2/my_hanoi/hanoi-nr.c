#include <stdio.h>
#include <assert.h>

typedef struct{
    int pc;

    int n;
    char from, to, via;

    int c1, c2;
}Frame;

int hanoi(int n, char from, char to, char via){
    Frame stk[64];
    Frame *top = stk - 1;


    // push a new frame with PC=0 onto the stack.
    #define call(...) ({*(++top)=(Frame){.pc = 0, __VA_ARGS__};})

    // pop the top-most frame
    #define ret(val) ({top --;retval = (val);})

    int retval = 0;

    // ???
    call(n, from, to, via);
    
    while(1){
        Frame *f = top;
        if (top < stk){
            break;
        }
    
        int next_pc = f->pc + 1;

        int n = f->n, from = f->from, to = f->to, via = f->via;

        switch (f->pc){
            case 0:
                if(n==1){
                    printf("%c -> %c\n", from, to);
                    ret(1);
                }
                break;
            case 1: call(n - 1, from, via, to);break;
            case 2: f->c1 = retval;break;
            case 3: call(1, from, to, via);break;
            case 4: call(n -1 , via, to, from);break;
            case 5: f->c2 = retval;break;
            case 6: ret(f->c1 + f->c2 + 1);break;
            default: assert(0);
            // default: printf("\n%d\n", f->pc);
        }

        f->pc = next_pc;
    }

    return retval;
}
