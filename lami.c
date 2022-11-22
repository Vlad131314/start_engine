
#include "avrlibdefs.h"
#include "avrlibtypes.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/wdt.h>

#include <avr/signal.h>

#include "lami.h"
#include "zero.c"
//////////////////////////////////////
//ïðîãðàììà îáðàáîòêè ñèñòåìíîãî ïðåðûâàíèÿ ñ ïåðèîäîì 20 ìèêðîñåêóíä
SIGNAL(SIG_OUTPUT_COMPARE2) 
{
  drv_act();
//  counts++;
};
//////////////////////////////////////

void InitTimers(void)
{
// Timer 2 system interrupt
   TIMSK |= 0x80 | 0x04 | 0x01;

   TCCR2 = 0xA;//0.125us * 8 * ((OCR2+1))
   OCR2 = 19;// 20us, 10ms/20us=500 øàãîâ ØÈÌ 
   
   TCCR0 = 0x07;
   TCCR1A = 0x00; //Setup TC1 to count PB1
   TCCR1B = 0x0F;
};
//////////////////////////////////////
void ioinit(void)
{

 	DDRA = 0x00;
 	PORTA = 0xFF; //pull up

 	DDRB  = 0x00;
 	PORTB = 0xFF;


 	DDRC  = 0x40;
 	PORTC = 0xFF;//0x00

 	DDRD = 0x00;
 	PORTD = 0xFF; 

};


 void proc_sec(void)
{ u16 n;

/*
 rpm = TCNT1 * 2.5;//5
 TCNT1 = 0;

 counts = 0;
 count4s++;
 if (count4s == 2) 
 {
  for (n=0;n<count_trip;n++) pwm_array[n] = 400;
 };

 if (count4s > 10) 
 {
  drv_mode = 0;
 };
 NormalCtrl();		
*/ 
}

//////////////////////////////////////
void main (void)

{

 ioinit(); 

 cli();

 InitTimers();
 TCNT1 = 0;
 TCNT0 = 0;

/////////////////////////////////////////////////////////

 drv_mode = 0; // stop mixer
 drv_mode = 1; // stert mixer

 zero_init();

 sei();

 while(1)
 {
   if (counts > 50000) proc_sec();
 };
};
