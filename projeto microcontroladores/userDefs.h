// -------------------------------------------
// Specific clock definition for PICGENIOS, ACEPIC and NEO201 development boards
#define _XTAL_FREQ 8000000

// -------------------------------------------
// General definition of type byteBitDef (author: Mauricio Kaster)
// Just apply it to a new variable to be able to access its 8-bit (byte)
// or its bits individually.
// Usage:
//      byteBitDef var1;
//      var1.byte = 0x0f;
//      var1.bit0 = 0;

typedef union {
    struct {
        unsigned bit0 :1;
        unsigned bit1 :1;
        unsigned bit2 :1;
        unsigned bit3 :1;
        unsigned bit4 :1;
        unsigned bit5 :1;
        unsigned bit6 :1;
        unsigned bit7 :1;
    };
    struct {
        unsigned char byte;
    };
} byteBitDef;

// -------------------------------------------
// Kit-specific hardware bindings

#ifdef devkit_acepic
    #include "kit_acepicPro3.h"
#endif
#ifdef devkit_neo
    #include "kit_neo201.h"
#endif
#ifdef devkit_picgenios
    #include "kit_picgenios.h"
#endif

void delay_ms(unsigned char milliseconds)
{
   while(milliseconds > 0)
   {
      milliseconds--;
       __delay_us(990);
   }
}
