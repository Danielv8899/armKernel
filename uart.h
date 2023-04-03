#define UART0 (volatile unsigned int *) 0x101f1000
#define UART1 (volatile unsigned int *) 0x101F2000
#define UART2 (volatile unsigned int *) 0x101F3000
#define UART3 (volatile unsigned int *) 0x10009000
#define UARTFR 6

#define uartfr_check_flag(f) (*(UART0+UARTFR) & f)

/*UARTFR flags*/
#define CTS 1
#define DSR (1 << 1)
#define DCD (1 << 2)
#define BUSY (1 << 3)
#define RXFE (1 << 4)
#define TXFF (1 << 5)
#define RXFF (1 << 6)
#define TXFE (1 << 7)
#define RI (1 << 8)
