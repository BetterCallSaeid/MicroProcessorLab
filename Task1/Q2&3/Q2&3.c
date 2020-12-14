#include <mega16.h>
#include <delay.h>

void main(void) 
{
	DDRA = 0x00; //make all of 8 ports to input
	PINA = 0x00; //0 in input
	DDRB = 0xff; //make all of 8 ports to output
	PORTB = 0x00; //0 in output

	while(1)
	{
		if(PINA.0 == 1)
		{
			PORTB = 0x01;
			delay_ms(1000);

			PORTB = 0x02;
			delay_ms(1000);

			PORTB = 0x04;
			delay_ms(1000);

			PORTB = 0x08;
			delay_ms(1000);

			PORTB = 0x10;
			delay_ms(1000);

			PORTB = 0x20;
			delay_ms(1000);

			PORTB = 0x40;
			delay_ms(1000);

			PORTB = 0x80;
			delay_ms(1000);---

			PORTB = 0x40;
			delay_ms(1000);

			PORTB = 0x20;
			delay_ms(1000);

			PORTB = 0x10;
			delay_ms(1000);

			PORTB = 0x08;
			delay_ms(1000);

			PORTB = 0x04;
			delay_ms(1000);

			PORTB = 0x02;
			delay_ms(1000);

			PORTB = 0x01;
			delay_ms(1000);

			PORTB = 0x00;

		} else {
			PORTB = 0x00;
		}
	}
}











