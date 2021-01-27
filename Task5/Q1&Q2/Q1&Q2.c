#include <mega16.h>
#include <delay.h>

int steps[4] = {9 , 10 , 6 , 5};
int position;
int direction;

void main(void)
{

	position = 0;
	direction = 1;

	DDRA=0xff;
	PORTA=0x00;

	DDRC=0x00;
	PORTC=0x00;

	TCCR0=(0<<WGM00) | (0<<COM01) | (0<<COM00) | (0<<WGM01) | (0<<CS02) | (1<<CS01) | (1<<CS00);
	TCNT0=0x00;
	OCR0=0x00;

	TIMSK=(0<<OCIE2) | (0<<TOIE2) | (0<<TICIE1) | (0<<OCIE1A) | (0<<OCIE1B) | (0<<TOIE1) | (0<<OCIE0) | (1<<TOIE0);

	#asm("sei")

	while (1)
    {
   		if(PINC.2 == 0)
        {
        	direction = 1;

        } else
        {
           	direction = -1;
        }

     }
}

interrupt [TIM0_OVF] void timer0_ovf_isr(void)
{
	position = 0;
    TCNT0 = 6;

    PORTA = steps[position];

    if(direction > 0)
    {
        if(position < 3)
        {
            ++position;
        } else
        {
            position = 0;
        }
    } else
    {
        if(position > 0)
        {
            --position;
        } else
        {
            position = 3;
        }
    }
}

