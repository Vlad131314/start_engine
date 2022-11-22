
//#include "lami.h"

/*
void testout(void)
{

if ((PIND & 0x80) == 0x80) PORTD &= ~0x80;
  else  PORTD |= 0x80;

};


void delaymini(void)
{
  u16 n;
  for (n=0;n<10000;n++); //задержка
};

*/

u08 my_eep_byte_read(u16 uiAddress)
{
 while(EECR & (1<<EEWE));
 EEAR = uiAddress;
 EECR |= (1<<EERE);
 return EEDR;
};

void my_eep_byte_write(u16 __addr, u08 __value)
{
	u08 __hi_addr;
	u08 __low_addr;
	
    __hi_addr = HIBYT(__addr);
	__low_addr = LOBYT(__addr);
	
	__asm__ __volatile__ (
		"my_EEPROM_byte_write:" "\n\t"
	    // Wait for completion of previous write	
		"sbic 	0x1C,1" "\n\t"
		"rjmp 	my_EEPROM_byte_write" "\n\t"
		// Set up address in address register
		"out 	0x1F, %1" "\n\t"
		"out 	0x1E, %2" "\n\t"
		// Write data to data register
		"out 	0x1D, %0" "\n\t"
		// Write logical one to EEMWE
		"sbi 	0x1C, 2" "\n\t"
	    // Start eeprom write by setting EEWE
		"sbi 	0x1C, 1" "\n\t" 
		:
		: "r" (__value), "r" (__hi_addr), "r" (__low_addr)
	);

};

void delay(u16 ms)
{ u32 t;
  u32 mt;
  mt = (F_CPU / 11290) * ms;//импирика корректировка при оптимизации
  for (t=0;t<mt;t++)
  	{
  	  __asm__ __volatile__ ("nop");  
	  __asm__ __volatile__ ("nop");  
	};
};

