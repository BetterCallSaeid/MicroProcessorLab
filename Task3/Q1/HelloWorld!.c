#include <mega16.h>
#include <alcd.h>

void main(void)
{
	PORTB = 0x00;
	DDRB = 0x00;

	lcd_init(16);
	lcd_clear();

	while (1) 
	{
		lcd_gotoxy(0,0);
		lcd_putsf("Hello World!");

	}
}