#include "uart.h"
#include "asm.h"
#include "mm.h"

#define KMI0 (volatile unsigned int *) 0x10006000
#define KMI1 (volatile unsigned int *) 0x10007000

#define SPSR_PREFIX 0x10
#define KERNEL_STACK 0x07FFFFF0
#define HEAP_BASE 0x02fffff0
#define INT_MAX 2<<32

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

void divide(int dividend, int divisor, int* quotient, int* remainder) {
    int sign = 1;

    // Handle negative numbers
    if ((dividend < 0 && divisor > 0) || (dividend > 0 && divisor < 0)) {
        sign = -1;
    }

    unsigned int u_dividend = (dividend < 0) ? -dividend : dividend;
    unsigned int u_divisor = (divisor < 0) ? -divisor : divisor;

    *quotient = 0;
    *remainder = 0;

    while (u_dividend >= u_divisor) {
        u_dividend -= u_divisor;
        (*quotient)++;
    }

    *quotient *= sign;
    *remainder = u_dividend * sign;
}

void reverse(char* str, int length) {
    int start = 0;
    int end = length - 1;
    while (start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
}

void itoa(int num, char* str, int base) {
    if (num == 0) {
        str[0] = '0';
        str[1] = '\0';
        return;
    }

    int is_negative = 0;
    int i = 0;

    if (num < 0 && base == 10) {
        is_negative = 1;
        num = -num;
    }

    int quotient, remainder;
    while (num != 0) {
        divide(num, base, &quotient, &remainder);
        str[i++] = (remainder > 9) ? (remainder - 10) + 'a' : remainder + '0';
        num = quotient;
    }

    if (is_negative) {
        str[i++] = '-';
    }

    str[i] = '\0';

    reverse(str, i);
}

int atoi(const char* str) {
    int sign = 1;  // 1 for positive, -1 for negative
    int result = 0;
    int i = 0;

    // Handle leading whitespace
    while (str[i] == ' ') {
        i++;
    }

    // Handle sign
    if (str[i] == '-') {
        sign = -1;
        i++;
    }

    // Parse digits
    while (str[i] >= '0' && str[i] <= '9') {
        // Check for overflow before adding the next digit
        if (result > INT_MAX / 10 || (result == INT_MAX / 10 && (str[i] - '0') > INT_MAX % 10)) {
            // Handle overflow here (e.g., set an error flag)
            // ...
            return 0;  // Return an appropriate value or handle the error as needed
        }

        result = result * 10 + (str[i] - '0');
        i++;
    }

    return sign * result;
}

int puts(char* buf){
    while (*buf && (uartfr_check_flag(TXFF) == 0)){
        *(char*)UART0 = (*buf);
        buf++;
    }
    return 0;
}

void memcpy(void * dest, void * src, unsigned int count){
    for (unsigned int i = 0;i <count;i++){
            ((char*)dest)[i] = ((char*)src)[i];
    }
}

void usermain(void){
    char * buf1 = alloc(8);
    char * addrbuf1 = alloc(4);
    char * addrbuf2 = alloc(4);
    char* buf2 = alloc(10);
    itoa(buf1,addrbuf1,16);
    itoa(buf2,addrbuf2,16);
    if (buf1 == buf2){
    memcpy(buf1,(void*)"this is\n", 8);
    puts(buf1);
    puts("\nptr: ");
    puts(addrbuf1);
    puts(buf2);
    puts("\nptr: ");
    puts(addrbuf2);
    syscall();
    puts("syscal called\n");
    }
}

int main(void){ 
    allocator_init(HEAP_BASE,2<<32);
    unsigned int stack[256];
    unsigned int *start_stack = stack + 256 - 16;
    start_stack[0] = 0x10;
    start_stack[1] = (unsigned int)&usermain;
    activate(start_stack);
    puts("dfhfjfg\n");
    while(1);
    return 0;
}