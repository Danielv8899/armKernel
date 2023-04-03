#include "uart.h"
#include "asm.h"

#define KMI0 (volatile unsigned int *) 0x10006000
#define KMI1 (volatile unsigned int *) 0x10007000

#define SPSR_PREFIX 0x10

enum CPSRmode{
    User = 0,
    FIQ,
    IRQ,
    Supervisor,
    Monitor,
    Abort,
    Hyp,
    Undefined,
    System
};

void memset(void * dest, char val, unsigned int count){
    for (unsigned int i = 0;i <count;i++){
            ((char*)dest)[i] = val;
    }
}

int puts(char* buf){
    while (*buf && (uartfr_check_flag(TXFF) == 0)){
        *(char*)UART0 = (*buf);
        buf++;
    }
    return 0;
}

int main(void){ 
    activate();
    setmsr(User+SPSR_PREFIX);
    int msr = getmsr();
    puts("this\n");
    puts("is\n");
    puts("test\n");
}

void usermain(void){
    puts("usermode test\n");
    test();
    while(1);
}