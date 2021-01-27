///////////////////////////////////////////////////////////////////////////
////                                                                   ////
////         Include - Function to scan the matrix keyboard            ////
////                                                                   ////
///////////////////////////////////////////////////////////////////////////

// User choice: Uncomment one of the following defines
// Select the type of dead-time

// #define deadTime_Delay
// #define deadTime_Interrupt

//---------------------------------------------------------
// Global variables

__bit btal1c1=0, btal1c2=0, btal1c3=0, btal1c4=0;
__bit btal2c1=0, btal2c2=0, btal2c3=0, btal2c4=0;
__bit btal3c1=0, btal3c2=0, btal3c3=0, btal3c4=0;
__bit btal4c1=0, btal4c2=0, btal4c3=0, btal4c4=0;
char tecla;
__bit flagDeadTime=0;		// used for dead-time given by timer 0 interrupt
char contDeadTime=1;

#ifdef deadTime_Delay   //delay
#define keyboardDeadTime() __delay_ms(5)
#define keyboardScan() keyboardScan2()
#endif

#ifdef deadTime_Interrupt   //Timer 0 interrupt
#define keyboardDeadTime() flagDeadTime=1
#define keyboardScan() keyboardScan3()
#endif

// -------------------------------------------
// Init function

void init_matrixKeyboard() {
    INTCON2bits.RBPU = 0; // PortB pull-ups; 0=enabled, 1=disabled
    ADCON1 = 0x0f; // To disable analog inputs on PortB (comment if using AD library)
#ifdef devkit_neo
    TRISB = 0b11110000;
#endif
#ifdef devkit_acepic
    TRISB = 0b00001111;
#endif
#ifdef devkit_picgenios
    TRISBbits.RB0 = 1;
    TRISBbits.RB1 = 1;
    TRISBbits.RB2 = 1;
    TRISDbits.RD0 = 0;
    TRISDbits.RD1 = 0;
    TRISDbits.RD2 = 0;
    TRISDbits.RD3 = 0;
#endif

#ifdef deadTime_Interrupt
    // Set Timer 0 for a 1ms interrupt
//	T0CONbits.TMR0ON  = 1; // Timer 0 on
//	T0CONbits.T08BIT  = 1; // 1=8 bit timer, 0=16 bit timer
//	T0CONbits.T0CS    = 0; // 0=internal clock, 1=external clock (pin 6, T0CKI)
//	T0CONbits.T0SE    = 0; // external edge: 0=rising edge, 1=falling edge
//	T0CONbits.PSA     = 0; // 0=prescaler is assigned, 1=no prescaler
//    T0CONbits.T0PS    = 2; // prescaler: 0=1:2, 1=4, 2=8, 3=16, 4=32, 5=64, 6=128, 7=256
//
//	INTCONbits.TMR0IE = 1;
//	//INTCONbits.TMR0IF = 0;
//	//INTCONbits.GIE    = 1;
//    //T1CON  = 0b01110001;                       //Configura Timer1 p/ Clock Externo e DIV 1:8, 8bits
#endif
}

//---------------------------------------------------------
// Interrupt-called function
// Must be called from within the Timer 0 interrupt routine
// in order to validade the debounce dead-time
// Assuming timer 0 interrupt interval of 1ms x 10 times count = 10ms
// T0CON  = 0b11000010;
// INTCON = 0b10100000;

void deadTime_isr()
{
	if(flagDeadTime)
		if(--contDeadTime==0) {
			contDeadTime=1;	// restore 10 ms (This value depends on the timer interval)
			flagDeadTime=0;
		}
}

//---------------------------------------------------------
// Kit-specific functions

#ifdef devkit_neo

char keyboardScan2()
{
	tecla = 0;

	// Activate column 1

	COL1 = 0;
	COL2 = 1;
	COL3 = 1;
	COL4 = 1;

	if (LIN1!=btal1c1) {
		if (btal1c1==1) { btal1c1=0; tecla='1'; keyboardDeadTime(); }
		else            { btal1c1=1; keyboardDeadTime(); } }
	
	if (LIN2!=btal2c1) {
		if (btal2c1==1) { btal2c1=0; tecla='4'; keyboardDeadTime(); }
		else            { btal2c1=1; keyboardDeadTime(); } }
	
	if (LIN3!=btal3c1) {
		if (btal3c1==1) { btal3c1=0; tecla='7'; keyboardDeadTime(); }
		else            { btal3c1=1; keyboardDeadTime(); } }
	
	if (LIN4!=btal4c1) {
		if (btal4c1==1) { btal4c1=0; tecla='*'; keyboardDeadTime(); }
		else            { btal4c1=1; keyboardDeadTime(); } }
	
	// Activate column 2

	COL1 = 1;
	COL2 = 0;
	COL3 = 1;
	COL4 = 1;

	if (LIN1!=btal1c2) {
		if (btal1c2==1) { btal1c2=0; tecla='2'; keyboardDeadTime(); }
		else            { btal1c2=1; keyboardDeadTime(); } }
	
	if (LIN2!=btal2c2) {
		if (btal2c2==1) { btal2c2=0; tecla='5'; keyboardDeadTime(); }
		else            { btal2c2=1; keyboardDeadTime(); } }
	
	if (LIN3!=btal3c2) {
		if (btal3c2==1) { btal3c2=0; tecla='8'; keyboardDeadTime(); }
		else            { btal3c2=1; keyboardDeadTime(); } }
	
	if (LIN4!=btal4c2) {
		if (btal4c2==1) { btal4c2=0; tecla='0'; keyboardDeadTime(); }
		else            { btal4c2=1; keyboardDeadTime(); } }
	
	// Activate column 3

	COL1 = 1;
	COL2 = 1;
	COL3 = 0;
	COL4 = 1;

	if (LIN1!=btal1c3) {
		if (btal1c3==1) { btal1c3=0; tecla='3'; keyboardDeadTime(); }
		else            { btal1c3=1; keyboardDeadTime(); } }
	
	if (LIN2!=btal2c3) {
		if (btal2c3==1) { btal2c3=0; tecla='6'; keyboardDeadTime(); }
		else            { btal2c3=1; keyboardDeadTime(); } }
	
	if (LIN3!=btal3c3) {
		if (btal3c3==1) { btal3c3=0; tecla='9'; keyboardDeadTime(); }
		else            { btal3c3=1; keyboardDeadTime(); } }
	
	if (LIN4!=btal4c3) {
		if (btal4c3==1) { btal4c3=0; tecla='#'; keyboardDeadTime(); }
		else            { btal4c3=1; keyboardDeadTime(); } }
	
	// Activate column 4

	COL1 = 1;
	COL2 = 1;
	COL3 = 1;
	COL4 = 0;

	if (LIN1!=btal1c4) {
		if (btal1c4==1) { btal1c4=0; tecla='A'; keyboardDeadTime(); }
		else            { btal1c4=1; keyboardDeadTime(); } }
	
	if (LIN2!=btal2c4) {
		if (btal2c4==1) { btal2c4=0; tecla='B'; keyboardDeadTime(); }
		else            { btal2c4=1; keyboardDeadTime(); } }
	
	if (LIN3!=btal3c4) {
		if (btal3c4==1) { btal3c4=0; tecla='C'; keyboardDeadTime(); }
		else            { btal3c4=1; keyboardDeadTime(); } }
	
	if (LIN4!=btal4c4) {
		if (btal4c4==1) { btal4c4=0; tecla='D'; keyboardDeadTime(); }
		else            { btal4c4=1; keyboardDeadTime(); } }
	
	return tecla;
}

#endif

//-----------------------------------------------------------------------------

#ifdef devkit_acepic

char keyboardScan2()
{
	tecla = 0;

	// Activate column 1

	COL1 = 0;
	COL2 = 1;
	COL3 = 1;
	COL4 = 1;

	if (LIN1!=btal1c1) {
		if (btal1c1==1) { btal1c1=0; tecla='1'; keyboardDeadTime(); }
		else            { btal1c1=1; keyboardDeadTime(); } }
	
	if (LIN2!=btal2c1) {
		if (btal2c1==1) { btal2c1=0; tecla='4'; keyboardDeadTime(); }
		else            { btal2c1=1; keyboardDeadTime(); } }
	
	if (LIN3!=btal3c1) {
		if (btal3c1==1) { btal3c1=0; tecla='7'; keyboardDeadTime(); }
		else            { btal3c1=1; keyboardDeadTime(); } }
	
	if (LIN4!=btal4c1) {
		if (btal4c1==1) { btal4c1=0; tecla='*'; keyboardDeadTime(); }
		else            { btal4c1=1; keyboardDeadTime(); } }
	
	// Activate column 2

	COL1 = 1;
	COL2 = 0;
	COL3 = 1;
	COL4 = 1;

	if (LIN1!=btal1c2) {
		if (btal1c2==1) { btal1c2=0; tecla='2'; keyboardDeadTime(); }
		else            { btal1c2=1; keyboardDeadTime(); } }
	
	if (LIN2!=btal2c2) {
		if (btal2c2==1) { btal2c2=0; tecla='5'; keyboardDeadTime(); }
		else            { btal2c2=1; keyboardDeadTime(); } }
	
	if (LIN3!=btal3c2) {
		if (btal3c2==1) { btal3c2=0; tecla='8'; keyboardDeadTime(); }
		else            { btal3c2=1; keyboardDeadTime(); } }
	
	if (LIN4!=btal4c2) {
		if (btal4c2==1) { btal4c2=0; tecla='0'; keyboardDeadTime(); }
		else            { btal4c2=1; keyboardDeadTime(); } }
	
	// Activate column 3

	COL1 = 1;
	COL2 = 1;
	COL3 = 0;
	COL4 = 1;

	if (LIN1!=btal1c3) {
		if (btal1c3==1) { btal1c3=0; tecla='3'; keyboardDeadTime(); }
		else            { btal1c3=1; keyboardDeadTime(); } }
	
	if (LIN2!=btal2c3) {
		if (btal2c3==1) { btal2c3=0; tecla='6'; keyboardDeadTime(); }
		else            { btal2c3=1; keyboardDeadTime(); } }
	
	if (LIN3!=btal3c3) {
		if (btal3c3==1) { btal3c3=0; tecla='9'; keyboardDeadTime(); }
		else            { btal3c3=1; keyboardDeadTime(); } }
	
	if (LIN4!=btal4c3) {
		if (btal4c3==1) { btal4c3=0; tecla='#'; keyboardDeadTime(); }
		else            { btal4c3=1; keyboardDeadTime(); } }
	
	// Activate column 4

	COL1 = 1;
	COL2 = 1;
	COL3 = 1;
	COL4 = 0;

	if (LIN1!=btal1c4) {
		if (btal1c4==1) { btal1c4=0; tecla='A'; keyboardDeadTime(); }
		else            { btal1c4=1; keyboardDeadTime(); } }
	
	if (LIN2!=btal2c4) {
		if (btal2c4==1) { btal2c4=0; tecla='B'; keyboardDeadTime(); }
		else            { btal2c4=1; keyboardDeadTime(); } }
	
	if (LIN3!=btal3c4) {
		if (btal3c4==1) { btal3c4=0; tecla='C'; keyboardDeadTime(); }
		else            { btal3c4=1; keyboardDeadTime(); } }
	
	if (LIN4!=btal4c4) {
		if (btal4c4==1) { btal4c4=0; tecla='D'; keyboardDeadTime(); }
		else            { btal4c4=1; keyboardDeadTime(); } }
	
	return tecla;
}

#endif

//-----------------------------------------------------------------------------

#ifdef devkit_picgenios

char keyboardScan2()
{
	tecla = 0;

	// Activate line 1

	LIN1 = 0;
	LIN2 = 1;
	LIN3 = 1;
	LIN4 = 1;

	if (COL1!=btal1c1) {
		if (btal1c1==1) { btal1c1=0; tecla='1'; keyboardDeadTime(); }
		else            { btal1c1=1; keyboardDeadTime(); } }

	if (COL2!=btal1c2) {
		if (btal1c2==1) { btal1c2=0; tecla='2'; keyboardDeadTime(); }
		else            { btal1c2=1; keyboardDeadTime(); } }

	if (COL3!=btal1c3) {
		if (btal1c3==1) { btal1c3=0; tecla='3'; keyboardDeadTime(); }
		else            { btal1c3=1; keyboardDeadTime(); } }

	// Activate line 2

	LIN1 = 1;
	LIN2 = 0;
	LIN3 = 1;
	LIN4 = 1;

	if (COL1!=btal2c1) {
		if (btal2c1==1) { btal2c1=0; tecla='4'; keyboardDeadTime(); }
		else            { btal2c1=1; keyboardDeadTime(); } }

	if (COL2!=btal2c2) {
		if (btal2c2==1) { btal2c2=0; tecla='5'; keyboardDeadTime(); }
		else            { btal2c2=1; keyboardDeadTime(); } }

	if (COL3!=btal2c3) {
		if (btal2c3==1) { btal2c3=0; tecla='6'; keyboardDeadTime(); }
		else            { btal2c3=1; keyboardDeadTime(); } }

	// Activate line 3

	LIN1 = 1;
	LIN2 = 1;
	LIN3 = 0;
	LIN4 = 1;

	if (COL1!=btal3c1) {
		if (btal3c1==1) { btal3c1=0; tecla='7'; keyboardDeadTime(); }
		else            { btal3c1=1; keyboardDeadTime(); } }

	if (COL2!=btal3c2) {
		if (btal3c2==1) { btal3c2=0; tecla='8'; keyboardDeadTime(); }
		else            { btal3c2=1; keyboardDeadTime(); } }

	if (COL3!=btal3c3) {
		if (btal3c3==1) { btal3c3=0; tecla='9'; keyboardDeadTime(); }
		else            { btal3c3=1; keyboardDeadTime(); } }

	// Activate line 4

	LIN1 = 1;
	LIN2 = 1;
	LIN3 = 1;
	LIN4 = 0;

	if (COL1!=btal4c1) {
		if (btal4c1==1) { btal4c1=0; tecla='*'; keyboardDeadTime(); }
		else            { btal4c1=1; keyboardDeadTime(); } }

	if (COL2!=btal4c2) {
		if (btal4c2==1) { btal4c2=0; tecla='0'; keyboardDeadTime(); }
		else            { btal4c2=1; keyboardDeadTime(); } }

	if (COL3!=btal4c3) {
		if (btal4c3==1) { btal4c3=0; tecla='#'; keyboardDeadTime(); }
		else            { btal4c3=1; keyboardDeadTime(); } }

	return tecla;
}

#endif

//---------------------------------------------------------
// This function is used only when dead-time is given by interrupt.
char keyboardScan3()
{
	tecla = 0;
	if(flagDeadTime==0) keyboardScan2();
	return tecla;
}