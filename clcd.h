#define CLCD (volatile unsigned int *) 0x10120000
#define SYS_CLCD (volatile unsigned int *)0x10000050 
#define SYS_CLCDSER SYS_CLCD + 4
#define LCDC_HWCURSOR (volatile unsigned int *) 0x10120800
#define CLCDE_PERIPHBASE (volatile unsigned int *) 0x10120fe0
#define SYS_OSCCLK4 (volatile unsigned int *) 0x1000001C
#define CLCD_TIM0 (volatile unsigned int *) 0x10120000
#define CLCD_TIM1 (volatile unsigned int *) 0x10120004
#define CLCD_TIM2 (volatile unsigned int *) 0x10120008
#define CLCDCON (volatile unsigned int *) 0x10120018
#define LCDPALLETE CLCD + 0x200

struct _HAP {
    unsigned int : 2;
    unsigned int ppl : 6;
    unsigned int hsw : 8;
    unsigned int hfp : 8;
    unsigned int hbp : 8;
};

struct _VAP {
    unsigned int lpp: 10;   
    unsigned int vsw: 6;    
    unsigned int vfp: 8;    
    unsigned int vbp: 8;  
};

struct _CSP {
    unsigned int PCD_LO : 5;     
    unsigned int CLKSEL : 1;    
    unsigned int ACB : 5;        
    unsigned int IVS : 1;       
    unsigned int IHS : 1;        
    unsigned int IPC : 1;        
    unsigned int IEO : 1;       
    unsigned int : 1;        
    unsigned int CPL : 10;
    unsigned int BCD : 1;        
    unsigned int PCD_HI : 5;      
};

struct _LEC {
    unsigned int LED : 7;
    unsigned int : 9;
    unsigned int LEE : 1;
    unsigned int : 15;
};

struct _LCDUPBASE{
    unsigned int : 1;
    unsigned int LCDUPBASE : 31;
};

struct _LCDIMSC {
    unsigned int : 1;
    unsigned int FUFINTRENB : 1;
    unsigned int LNBUINTRENB : 1;
    unsigned int VCOMPINTRENB : 1;
    unsigned int MBERRINTRENB : 1;
    unsigned int : 27;
};

struct _LCDControl {
    unsigned int LcdEn: 1;
    unsigned int LcdBpp: 3;
    unsigned int LcdBW: 1;
    unsigned int LcdTFT: 1;
    unsigned int LcdMono8: 1;
    unsigned int LcdDual: 1;
    unsigned int BGR: 1;
    unsigned int BEBO: 1;
    unsigned int BEPO: 1;
    unsigned int LcdPwr: 1;
    unsigned int LcdVComp: 2;
    unsigned int : 2;
    unsigned int WATERMARK: 1;
    unsigned int : 15;
};

struct _LCDRIS{
    unsigned int : 1;
    unsigned int FUF : 1;
    unsigned int LNBU : 1;
    unsigned int Vcomp : 1;
    unsigned int MBERROR : 1;
    unsigned int : 27;
};

struct _LCDPallete{
    unsigned int R2 : 5;
    unsigned int G2 : 5;
    unsigned int B2 : 5;
    unsigned int i : 1;
    unsigned int R : 5;
    unsigned int G : 5;
    unsigned int B : 5;
    unsigned int ui : 1;
};

 struct clcd{
    struct _HAP LCDTiming0;
    struct _VAP LCDTiming1;
    struct _CSP LCDTiming2;
    struct _LEC LCDTiming3;
    struct _LCDUPBASE LCDUPBASE;
    struct _LCDUPBASE LCDLPBASE;
    struct _LCDIMSC LCDIMSC;
    struct _LCDControl LCDControl;
    struct _LCDRIS LCDRIS;
    struct _LCDRIS LCDMIS;
    struct _LCDRIS LCDICR;
    unsigned int LCDUPCURR;
    unsigned int LCDLPCURR;
    unsigned int reserverd [0x72];
    struct _LCDPallete CLDPallete [0x7f];
};

struct _CLCDPERIPH {
    unsigned int PartNumber : 12;
    unsigned int DesignerID : 8;
    unsigned int Revision : 4;
    unsigned int Configuration : 8;
};

struct _CLCDPCELLID{
    unsigned int PCELLID : 8;
    unsigned int : 26;
};

struct clcdperiph{
    struct _CLCDPERIPH CLCDPERIPHID0;
    struct _CLCDPERIPH CLCDPERIPHID1;
    struct _CLCDPERIPH CLCDPERIPHID2;
    struct _CLCDPERIPH CLCDPERIPHID3;
    struct _CLCDPCELLID CLCDPCELLID0;
    struct _CLCDPCELLID CLCDPCELLID1;
    struct _CLCDPCELLID CLCDPCELLID2;
    struct _CLCDPCELLID CLCDPCELLID3;
};