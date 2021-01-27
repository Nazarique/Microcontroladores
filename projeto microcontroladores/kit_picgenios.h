///////////////////////////////////////////////////////////////////////////
////                                                                   ////
////                KIT MICROGENIOS HARDWARE BINDINGS                  ////
////                                                                   ////
////                   Mauricio Kaster - MAR/2014                      ////
////                                                                   ////
///////////////////////////////////////////////////////////////////////////

// BOTOES
#define   BT1      PORTBbits.RB3
#define   BT2      PORTBbits.RB4
#define   BT3      PORTBbits.RB5
#define   BT4      PORTAbits.RA5
#define   BTX      PORTBbits.RB2
#define   BTY      PORTBbits.RB1
#define   BTZ      PORTBbits.RB0
// TECLADO MATRICIAL
#define   LIN1     PORTDbits.RD3 // output
#define   LIN2     PORTDbits.RD2 // output
#define   LIN3     PORTDbits.RD1 // output
#define   LIN4     PORTDbits.RD0 // output
#define   COL1     PORTBbits.RB0 // input
#define   COL2     PORTBbits.RB1 // input
#define   COL3     PORTBbits.RB2 // input
// DISPLAY DE 7 SEGMENTOS
#define   SEGA     PORTDbits.RD0
#define   SEGB     PORTDbits.RD1
#define   SEGC     PORTDbits.RD2
#define   SEGD     PORTDbits.RD3
#define   SEGE     PORTDbits.RD4
#define   SEGF     PORTDbits.RD5
#define   SEGG     PORTDbits.RD6
#define   SEGP     PORTDbits.RD7
#define   ENDISP1  PORTAbits.RA2
#define   ENDISP2  PORTAbits.RA3
#define   ENDISP3  PORTAbits.RA4
#define   ENDISP4  PORTAbits.RA5
// LEDS
#define	  LEDS_GROUP_1  PORTD
#define	  LEDS_GROUP_2  PORTB
// DISPLAY LCD
#define  LCD_DADOS  PORTD
#define   RS       PORTEbits.RE2   // 1->DADO  0->COMANDO
#define   EN       PORTEbits.RE1
// RELÊS
#define   RELE1    PORTCBITS.RC0
#define   RELE2    PORTEBITS.RE0
// A/D CHANNELS (TRIMPOTS)
#define   POTA     PORTAbits.RA0
#define   POTB     PORTAbits.RA1
// FAN MODULE
#define   VENT     PORTCbits.RC2 //CCP1
#define   TACOM    PORTCbits.RC0 //T13CKI
// HEAT MODULE
#define   SENSTEMP PORTEbits.RE0 //AN5
#define   RESIST   PORTCbits.RC5 //
// BUZZER
#define   BUZZER   PORTCbits.RC1 //CCP2

// REAL-TIME CLOCK
#ifdef processor_PIC18F4550
	#define   RTC_SCL   PORTBbits.RB1 // Config DIP?
	#define   RTC_SDA   PORTBbits.RB0 // Config DIP?
#else
	#define   RTC_SCL   PORTCbits.RC3 // Config DIP?
	#define   RTC_SDA   PORTCbits.RC4 // Config DIP?
#endif
// I2C MEMORY 25LC256
#ifdef processor_PIC18F4550
	#define   MEM_SCK   PORTBbits.RB1 // Config DIP?
	#define   MEM_SDI   PORTBbits.RB0 // Config DIP?
	#define   MEM_SDO   PORTCbits.RC7 // Config DIP?
#else
	#define   MEM_SCK   PORTCbits.RC3 // Config DIP?
	#define   MEM_SDI   PORTCbits.RC4 // Config DIP?
	#define   MEM_SDO   PORTCbits.RC5 // Config DIP?
#endif
#define   MEM_CS   PORTAbits.RA3
