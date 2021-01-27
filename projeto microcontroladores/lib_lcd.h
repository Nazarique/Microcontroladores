///////////////////////////////////////////////////////////////////////////
////                                                                   ////
////                              BASE.C                               ////
////             Generic Microgenios CHIP18F4550 main file             ////
////                                                                   ////
////                   Mauricio Kaster - NOV/2013                      ////
////                                                                   ////
///////////////////////////////////////////////////////////////////////////

//-------------------------------------------------------------
//    This include file has specific functions for controlling
//    the LCD module. It can drive the hardware LCD (on kits
//    PICGenios, AcePic or Neo) or simulator LCD (on PICSIMLAB)
//-------------------------------------------------------------

// Defines the operating mode of the LCD bus data as 4 or 8 bits
//#define  lcd_mode 4
//#define  lcd_mode 8

// Specific delays: (uncomment the choosen one)
// ..hardware:  for kits PICGenios, AcePic and Neo
// ..PICSIMLAB: for the simulator
//#define lcd_delayType_KIT
//#define lcd_delayType_PICSIMLAB

//---------------------------------------------------------
//    LCD DISPLAY FUNCTIONS
//---------------------------------------------------------

#ifdef lcd_delayType_KIT
	#define delayPulse() __delay_us(1)
#endif
#if lcd_delayType_PICSIMLAB
	#define delayPulse() __delay_us(10)
#endif

//---------------------------------------------------------
void lcd_write8 (char ch, char _rs)
{
	LCD_DADOS = ch;
	if(_rs) RS = 1; else RS = 0;
	delayPulse();
	EN = 0;
	delayPulse();
	EN = 1;
	__delay_us(50);
}

//---------------------------------------------------------
void lcd_writeNibble (char ch)
{
	//EN = 1;
	LCD_DADOS = ch;
	delayPulse();
	EN = 0;
	delayPulse();
	EN = 1;
}

//---------------------------------------------------------
void lcd_write4 (char ch, char _rs)
{
	if(_rs) RS = 1; else RS = 0;
	lcd_writeNibble (ch & 0xf0);
	lcd_writeNibble (ch << 4);
	__delay_us(50);
}

#if lcd_mode==8
	#define   lcd_command(x)   lcd_write8(x,0)
	#define   lcd_data(x)      lcd_write8(x,1)
#elif lcd_mode==4
	#define   lcd_command(x)   lcd_write4(x,0)
	#define   lcd_data(x)      lcd_write4(x,1)
#endif

#define   lcd_clear()       lcd_command(0x01); __delay_ms(2)
#define   lcd_gotoxy(L,C)   lcd_command(0x80+L*0x40+C);
#define   lcd_cursorOff()   lcd_command(0b00001100)
#define   lcd_cursorOn()    lcd_command(0b00001110)
#define   lcd_cursorBlink() lcd_command(0b00001111)

//---------------------------------------------------------
void init_lcd()
{
    //ADCON1 = 0x0f; // Disable analog inputs (comment out if using AD lib)
    TRISD  = 0x00;
    TRISE  = 0x00;

	EN = 0;
	RS = 0;
	__delay_ms(50);
	EN = 1;
#if lcd_mode==8
	lcd_command(0b00111000); //0x38
	__delay_ms(5);
	lcd_command(0b00111000); //0x38
	__delay_ms(1);
	lcd_command(0b00111000); //0x38
#elif lcd_mode==4
	lcd_writeNibble(0b00100000); //0x20
	__delay_ms(5);
	lcd_command(0b00101000); //0x28
	__delay_ms(1);
	lcd_command(0b00101000); //0x28
#endif
	lcd_command(0b00001000); //0x08
	lcd_command(0b00001111); //0x0f
	lcd_command(0b00000001); //0x01
	lcd_command(0b00000110); //0x06
}

//---------------------------------------------------------
//void lcd_stringNNN(char ch[])
// This function has two types:
// ... One will take the string stored in Eprom, which happens
// ... when the string is defined in compile time. Then, the pointer
// ... uses TBLPTR register.
// ... The other will take string stored in Ram, which happens
// ... when the string is defined at runtime. Then, the pointer uses
// ... FSR register.
void lcd_string(const char * ch)
{
    while(*ch != 0) {
        switch(*ch) {
           case '\n': lcd_command(0xc0); break;
           case '\f': lcd_clear(); break;
           default:   lcd_data(*ch);
        }
        ch++;
    }
}

// It is possible to use the instruction 'printf' for sending
// formatted strings to the LCD.
// The syntax is: printf(function,"string",variables)
// Ex.: printf(lcd_stringEprom,"\fValor = %03u",var);

//---------------------------------------------------------
// Additional LCD Functions

void lcd_coord(char l, char c)
{
	lcd_command(0x80+0x40*l+c);
}

//---------------------------------------------------------
void lcd_display3(char val)
{
	static char cent, dez, un;
	
	cent='0';
	dez='0';
	while(val>99) { cent++; val-=100; }
	while(val>9)  { dez++;  val-=10; }
	un='0'+val;
	lcd_data(cent);
	lcd_data(dez);
	lcd_data(un);
}

//---------------------------------------------------------
void lcd_display5(int val)
{
	static char dezmil, unmil, cent, dez, un;
	
	dezmil='0';
	unmil='0';
	cent='0';
	dez='0';
	while(val>9999) { dezmil++; val-=10000; }
	while(val>999)  { unmil++;  val-=1000; }
	while(val>99)   { cent++;   val-=100; }
	while(val>9)    { dez++;    val-=10; }
	un='0'+val;
	// optional: avoid generation of characters outside range 0x30 - 0x3f
	//dezmil = (dezmil&0x0f)|0x30;
	//unmil  = ( unmil&0x0f)|0x30;
	//cent   = (  cent&0x0f)|0x30;
	//dez    = (   dez&0x0f)|0x30;
	//un     = (    un&0xf)|0x30;
	lcd_data(dezmil);
	lcd_data(unmil);
	lcd_data(cent);
	lcd_data(dez);
	lcd_data(un);
}