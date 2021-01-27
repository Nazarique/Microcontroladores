// Define microcontroller:
// #define processor_PIC18F4520
#define processor_PIC18F4550
// Development kit under use:
// #define devkit_neo
// #define devkit_acepic
#define devkit_picgenios
#include "configBits.h"
#include <xc.h>
#include "userDefs.h"
#include "pwm.h"
#include "lib_adc.h"
#define lcd_mode 4
#define lcd_delayType_KIT
#include "lib_lcd.h"
#define deadTime_Interrupt
#include "lib_tecladoMatricial.h"

#define servo1 PORTBbits.RB3                   //Servo1 ligado ao pino RB0
#define servo2 PORTBbits.RB4                   //Servo1 ligado ao pino RB1
#define servo3 PORTAbits.AN2                   //Servo1 ligado ao pino RA2
#define servo4 PORTAbits.AN3                   //Servo1 ligado ao pino RA3

unsigned int duty1[2] = {16,32};               //16 = 90° e 32 = -90°
unsigned int duty2[2] = {16,32};
unsigned int duty3[2] = {16,32};
unsigned int duty4[2] = {16,32};
__bit flag = 0;                                //Variavel para troca de posicao inicial e final
unsigned int pwm = 16;                         //Variável para alterar o duty
char selecao = 4;                              //Variável para alterar o servo
char retsak = 1;                               //Variavel para troca de servo em movimento
unsigned char estado = 1;   		           //maq de estado
int flamis = 0;                                //Variável temporaria de PWM
//Flamis Marin


	//Estouro Timer0 = TMR0 x prescaler x ciclo de máquina
    //Estouro Timer0 = 256  x   128     x    5E-7   = 16,4 ms



	//Estouro Timer1 = TMR1 x prescaler x ciclo de máquina
    //Estouro Timer1 = 256  x    8      x     5E-7  =   1  ms




//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
void init() {
    init_lcd();                                //biblioteca flamis, RA0 e RA1 entradas analog, AD on, ADCON2 2 TAD, divide Fosc/8
    adc_init();                                //biblioteca adc, RA0 e RA1 entradas analog, AD on, ADCON2 2 TAD, divide Fosc/8
    init_matrixKeyboard();                     //biblioteca teclado matrixial, RA0 e RA1 entradas analog, AD on, ADCON2 2 TAD, divide Fosc/8
    T0CON  = 0b11000110;                       //Configura Enable Timer0, 8bits, TIMER0 para div 1:128 e outras especificações
    //T1CON  = 0b01110001;                     //Configura Timer1 p/ Clock Externo e DIV 1:8, 8bits
    INTCON = 0b11100000;                       //Habilita o TIMER0, GIE = 1, PEIE = 1 ( OUTROS TIMERS ) , TMR0IE = 1
    TRISB  = 0b11100111;                       //saídas: RB3 Servo1, RB4 Servo2
    TRISA  = 0b11110011;                       //entrada: RA1; saídas: RA2 Servo3, RA3 Servo4

}
//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
void set_duty(int val){                        //Set valor do pwm 
    pwm = val;                               
}
//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
void selecaoServos(char p){                  //Salva o valor do aux, maq estado = 4
    	switch (selecao) {                    //p Valor inicial = 0x00, final = 0x01, de posicao do servo 
		case 1:
			duty1[p] = pwm;                  //duty servo 1
		break;
		case 2:
			duty2[p] = pwm;                  //duty servo 2
		break;
		case 3:
			duty3[p] = pwm;				     //duty servo 3
		break;
		case 4:
			duty4[p] = pwm;			         //duty servo 4
		break;
        }
}
//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
void maqTeste() {
    unsigned char val = 0;					  //Variavel do teclado  
    switch (retsak) {                         //Variavel de selecao de servo, em movimento
        case 1:								  //Teste servo 1
            val = keyboardScan();             //Leitura de caracter
            selecao = 1;                      //Seleciona o servo que será acionado           
            set_duty(duty1[flag]);            //Atribui um novo valor ao PWM
            lcd_gotoxy(1,2);                  //Vai até a posição desejada
            lcd_display3(selecao);            //Coloca o indice do Servo
            lcd_gotoxy(1,10);                 //Vai até a posição desejada
            lcd_display3(pwm);                //Coloca o o valor do pwm
             if(val == '*'){					  //Escape                               
                estado = 1;					  //Volta para selecao Inicial
                selecao = 0;              	  //zera a variavel de selecao
                tela0();                      //Tela de selecao Inicial
            }
            break;
            
        case 2:                               //Teste servo 2
            val = keyboardScan();             //Leitura de caracter
            selecao = 2;                      //Seleciona o servo que será acionado           
            set_duty(duty2[flag]);            //Atribui um novo valor ao PWM
            lcd_gotoxy(1,2);                  //Vai até a posição desejada
            lcd_display3(selecao);            //Coloca o indice do Servo
            lcd_gotoxy(1,10);                 //Vai até a posição desejada
            lcd_display3(pwm);                //Coloca o o valor do pwm
             if(val == '*'){					  //Escape                               
                estado = 1;					  //Volta para selecao Inicial
                selecao = 0;              	  //zera a variavel de selecao
                tela0();                      //Tela de selecao Inicial
            }
            break;
            
        case 3:				   			      //Teste servo 3
            val = keyboardScan();             //Leitura de caracter
            selecao = 3;                      //Seleciona o servo que será acionado           
            set_duty(duty3[flag]);            //Atribui um novo valor ao PWM
            lcd_gotoxy(1,2);                  //Vai até a posição desejada
            lcd_display3(selecao);            //Coloca o indice do Servo
            lcd_gotoxy(1,10);                 //Vai até a posição desejada
            lcd_display3(pwm);                //Coloca o o valor do pwm
             if(val == '*'){					  //Escape                               
                estado = 1;					  //Volta para selecao Inicial
                selecao = 0;              	  //zera a variavel de selecao
                tela0();                      //Tela de selecao Inicial
            }
            break;
            
        case 4:							      //Teste servo 4
            val = keyboardScan();             //Leitura de caracter
            selecao = 4;                      //Seleciona o servo que será acionado           
            set_duty(duty4[flag]);            //Atribui um novo valor ao PWM
            lcd_gotoxy(1,2);                  //Vai até a posição desejada
            lcd_display3(selecao);            //Coloca o indice do Servo
            lcd_gotoxy(1,10);                 //Vai até a posição desejada
            lcd_display3(pwm);                //Coloca o o valor do pwm
             if(val == '*'){					  //Escape                               
                estado = 1;					  //Volta para selecao Inicial
                selecao = 0;              	  //zera a variavel de selecao
                tela0();                      //Tela de selecao Inicial
            }
            break; 
        }
}    
//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
void maqEstados() {
    int adc = 0x00;                           //Variável para leitura AD, variavel de temporaria de PWM
    unsigned char val = 0;					  //Variavel do teclado
    switch (estado) {
        case 1:								 
            val = keyboardScan();             //Leitura de caracter
            if(val == '#'){					  //Configurar
                estado = 2;					  //Selecao de servos
                tela1();                      //Tela 1  de selecao de servos
            }
            if(val == '*'){					  //Testar o braco
                tela4();                      //tela de escape 
                estado = 6;
            }
            break;
        case 2:								  //Seleção de Servos
            val = keyboardScan();             //Leitura de caracter
            if(val == '1') {                  //Servo 1
                estado = 3;					  //Avança para o estado 3
                selecao = 1;                  //Servo escolhido 
                tela2();                      //Tela de movimentos
            }
            if(val == '2') {                  //Servo 2
                estado = 3;					  //Avança para o estado 3
                selecao = 2;                  //Servo escolhido 
                tela2();                      //Tela de movimentos
            }
            if(val == '3') {                  //Servo 3
                estado  = 3;				  //Avança para o estado 3
                selecao = 3;                  //Servo escolhido 
                tela2();                      //Tela de movimentos
            }
            if(val == '4') {                  //Servo 4
                estado = 3;					  //Avança para o estado 3
                selecao = 4;                  //Servo escolhido 
                tela2();                      //Tela de movimentos
            }
            if(val == '*') {                  //Escape
                estado = 1;					  //Retorna ao estado 1
                tela1();                      //Tela de movimentos
            }
            break;
        case 3:								  //Seleção de movimentos 
                val = keyboardScan();         //Leitura de caracter
                adc = isr_AD()/16;            //Variável adc recebe valor anologico do AN0
        		adc = adc ;	         	      //Variável de valor temporario duty 
                flamis = pwm;                 //Salva o valor anterio de DUTY  
                set_duty(adc);                //Movimento do Braço
            if(val == '1'){					  //Movimento 1
                estado = 4;					  //Avança para o estado 4
                tela31();                     //Tela de salvamento 
            }
            if(val == '2'){					  //Movimento 2
                estado = 5;					  //Avança para o estado 5
                tela32();                     //Tela de salvamento 
            }
            break;
        case 4:								  //Posicao 1
            val = keyboardScan();             //Leitura de caracter
            if(val == '#'){					  //Enter
                estado = 1;					  //Volta para selecao Inicial
                selecaoServos(0x00);          //Atribui o valor temporario de flamis para duty, posicao 1
                flamis = 0;					  //zera a variavel temporaria
                selecao = 0;                  //zera a variavel de selecao
                tela0();                  	  //Tela de selecao Inicial 
            }
            if(val == '*'){					  //Escape
                estado = 1;					  //Volta para selecao Inicial
                set_duty(flamis);             //Movimento do Braço
                flamis = 0;					  //zera a variavel temporaria
                selecao = 0;                  //zera a variavel de selecao
                tela0();                      //Tela de selecao Inicial
            }
            break;
        case 5:								  //Posicao 2
            val = keyboardScan();             //Leitura de caracter
            if(val == '#'){					  //Enter
                estado = 1;					  //Volta para selecao Inicial
                selecaoServos(0x01);          //Atribui o valor temporario de flamis para duty, posicao 2
                flamis = 0;                   //zera a variavel temporaria
                selecao = 0;              	  //zera a variavel de selecao
                tela0();                      //Tela de selecao Inicial
            }
            if(val == '*'){					  //Escape
                estado = 1;					  //Volta para selecao Inicial
                set_duty(flamis);             //Movimento do Braço
                flamis = 0;                   //zera a variavel temporaria
                selecao = 0;              	  //zera a variavel de selecao
                tela0();                      //Tela de selecao Inicial
            }
            break;							  //end Config    
        case 6:
            maqTeste();                       //loop Teste
            break;
    }
}
//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
void tela0() {								 //Tela inicial
    lcd_string("\fBraco Robotico:\n*-Testar #-Conf");
    lcd_cursorOff();						 //Desliga o cursor
}
//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
void tela1() {								 //Tela de seleção de
    lcd_string("\fEscolha o Servo:\n1 2 3 4 *-ESC");
    lcd_cursorOff();						//Desliga o cursor
}
//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
void tela2() {								//Tela de escolha de movimento inicial ou final
    lcd_string("\fEscolha Mov-S\n1-P1 2-P2");
    lcd_gotoxy(0,13);						//Vai até a posição desejada
    lcd_display3(selecao);					//Coloca o indice do Servo
}
//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
void tela31() {								//Tela de salvamento P1 de cada servo 
    lcd_string("\fSalvar Posi-1 S\n*-ESC #-ENTER");
    lcd_gotoxy(0,15);						//Vai até a posição desejada
    lcd_display3(selecao);					//Coloca o indice do Servo
}
//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
void tela32() {								//Tela de salvamento P2 de cada servo 
    lcd_string("\fSalvar Posi-2 S\n*-ESC #-ENTER");
    lcd_gotoxy(0,15);					    //Vai até a posição desejada
    lcd_display3(selecao);					//Coloca o indice do Servo
}
//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
void tela4() {								//Tela de Teste
    lcd_string("\fPressione *-ESC\nS:    pwm:");
}
//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
void __interrupt(high_priority) isrH() {      //Houve estouro do Timer0? 
    if(INTCONbits.TMR0IF == 1) isr_Timer0();  //Sim...  
}                                             //end if TMR0IF
//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
void isr_Timer0() {                             	               
    INTCONbits.TMR0IF = 0;                   //Limpa flag
    static char cont = 63;                   //Variavel de contagem tempo morto, 63*16 = 1segundo
    static char cont2 = 8;                   //Variavel de contagem para alterar o servo na funcao teste
    deadTime_isr();                          //Tempo morto teclado matrix
    if(--cont==0){
        if(cont2 == 8)   retsak = 1;         //primeiro servo 
        if(cont2 == 6)   retsak = 2;         //segundo servo
        if(cont2 == 4)   retsak = 3;         //terceiro servo
        if(cont2 == 2)   retsak = 4;         //quarto servo
        if(--cont2==0){
            cont2 = 8;
        }
        cont = 63;
        if(flag == 1)
            {
               flag = 0;                     //flag de movimento, movimento posicao inicial
            }
            else
            {
               flag = 1;                    //flag de movimento, movimento posicao final
            }
    }
    switch(selecao){                        //Seleção do servo motor
        case 1:
            if(servo1)                      //Saída servo1 em high?
            {                               //Sim...
                TMR0 = pwm;                 //TMR0 recebe valor atual do duty1
                servo1 = 0x00;              //Saída do servo1 em low
                
            }                               //end if servo1
                else                        //Senão...
            {

                TMR0 = (255 - pwm);         //TMR0 recebe valor máximo menos valor do duty1
                servo1 = 0x01;              //Saída do servo1 em high
              
            }                               //end else
            break;                          //end case 1
            
        case 2:
            if(servo2)                      //Saída servo2 em high?
            {                               //Sim...
                TMR0 = pwm;                 //TMR0 recebe valor atual do duty1
                servo2 = 0x00;              //Saída do servo2 em low
            }                               //end if servo2
                else                        //Senão...
            {

                TMR0 = (255 - pwm);         //TMR0 recebe valor máximo menos valor do duty1
                servo2 = 0x01;              //Saída do servo2 em high
            }                               //end else
            break;                          //end case 2
            
        case 3:
            if(servo3)                      //Saída servo3 em high?
            {                               //Sim...
                TMR0 = pwm;                 //TMR0 recebe valor atual do duty1
                servo3 = 0x00;              //Saída do servo3 em low
            }                               //end if servo3
                else                        //Senão...
            {

                TMR0 = (255 - pwm);         //TMR0 recebe valor máximo menos valor do duty1
                servo3 = 0x01;              //Saída do servo3 em high
            }                               //end else
            break;                          //end case 3
            
        case 4:
            if(servo4)                      //Saída servo4 em high?
            {                               //Sim...
                TMR0 = pwm;                 //TMR0 recebe valor atual do duty1
                servo4 = 0x00;              //Saída do servo4 em low
            }                               //end if servo4
                else                        //Senão...
            {

                TMR0 = (255 - pwm);         //TMR0 recebe valor máximo menos valor do duty1
                servo4 = 0x01;              //Saída do servo4 em high
            }                               //end else
            break;                          //end case 4
        }                                   //end switch
}                                           //end Timer0
//HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
void main(void) {
     init();                                //Seta todas as configurações
     lcd_string("\fBraco Robotico\nHenrique N. R.");
     lcd_cursorOff();						//Retira o Curso
     __delay_ms(4000);
     tela0();                               //Tela zero, testar ou configurar 
     while(1)                               //Loop infinito
     {
        maqEstados();                       //Maquina de estados
     }                                      //end while
    return;
}                                           //end main
