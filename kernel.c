#define UART0 0x101f1000
#define COLOR 0xff
#define CHAR_LCD 0x1008000
#define KMI0 0x10006000
#define KMI1 0x10007000

#define LCD_CLEAR 1
#define LCD_RETURN (1<<1)
#define LCD_ENTRYMODE(d,s) (1<<2) | (d << 1) | s
#define LCD_DISPLAY(d,c,b) (1<<3) | (d << 2) | (c << 1) | b
#define LCD_SHIFT(c,d) (1<<4) | (c << 3) | (d << 2)
#define LCD_SETFUNC(l,n,f) (1<<5) | (l << 4) | (n << 3) | (f << 2)
#define LCD_SETGCRAM(addr) (1 << 6) | (addr && 0x3f) /*Must check addr size when calling*/
#define LCD_SETDDRAM(addr) (1 << 7) | (addr && 0x7f)


typedef struct char_lcd{
    unsigned int CHAR_COM;
    unsigned int CHAR_DAT;
    unsigned int CHAR_RD;
    unsigned int CHAR_RAW;
    unsigned int CHAR_MASK;
    unsigned int CHAR_STAT;
}charlcd,*pcharlcd;

int main(void){ 
    volatile char * key = KMI0;
    volatile char * stdio = UART0;
    while(1){
        if (key){
            *stdio = *key;
        }
    }
    return 0;
}