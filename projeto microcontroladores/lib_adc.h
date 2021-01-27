///////////////////////////////////////////////////////////////////////////
////                                                                   ////
////                              BASE.C                               ////
////             Generic Microgenios CHIP18F4550 main file             ////
////                                                                   ////
////                   Mauricio Kaster - NOV/2013                      ////
////                                                                   ////
///////////////////////////////////////////////////////////////////////////

// -------------------------------------------
// Global variables
int adcval;

// -------------------------------------------
void adc_init() {
    ADCON0bits.ADON   = 1; // AD on
    ADCON0bits.CHS    = 1; // channel select: 0 to 12
    ADCON0bits.GODONE = 0; // GO /DONE

    ADCON1bits.PCFG   = 0b1110; // config which are analog or digital (page 268)
    ADCON1bits.VCFG0  = 0; // VRef+
    ADCON1bits.VCFG1  = 0; // VRef-

    ADCON2bits.ACQT   = 1; // num Tad , 0=0, 1=2, 2=4, 3=6, 4=8, 5=12, 6=16, 7=20
    ADCON2bits.ADCS   = 1; // divide Fosc/n , 0=2, 1=8, 2=32, 3=derived from AD RC osc, 4=4, 5=16, 6=64, 7=derived from AD RC osc
    ADCON2bits.ADFM   = 1; //Leitura a direita, 16bits
    //TRISAbits.RA0 = 1; // AN0
    //TRISAbits.RA1 = 1; // AN1
    //TRISAbits.RA2 = 1; // AN2
    //TRISAbits.RA3 = 1; // AN3
    // TRISAbits.RA4 = 1; // AN4
    // TRISEbits.RE0 = 1; // AN5
    // TRISEbits.RE1 = 1; // AN6
    // TRISEbits.RE2 = 1; // AN7
    // TRISBbits.RB2 = 1; // AN8
    // TRISBbits.RB3 = 1; // AN9
    // TRISBbits.RB1 = 1; // AN10
    // TRISBbits.RB4 = 1; // AN11
    // TRISBbits.RB0 = 1; // AN12

    // INTCONbits.GIE  = 1; // Global interrupt enable
    // INTCONbits.PEIE = 1; // Peripheral interrupt enable
    // PIE1bits.ADIE   = 1; // AD converter interrupt
}
// -------------------------------------------
void adc_channelSelect(char ch) {
    ADCON0bits.CHS = ch;
}
// -------------------------------------------
int adc_read() {
	static int result;
	result = ADRESH << 8;
	result += ADRESL;
	return result;
}
// -------------------------------------------
int adc_conversion() {
	ADCON0bits.GODONE = 0;
	while(ADCON0bits.GODONE==1) {}
	return adc_read();
}
// -------------------------------------------
int isr_AD() {
	PIR1bits.ADIF = 0;
	adcval = adc_read();
	// If continuous conversion is desired, then start a new conversion
	ADCON0bits.GODONE = 1;
    return adcval;
}