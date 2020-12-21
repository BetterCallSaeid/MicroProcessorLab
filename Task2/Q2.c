#include <mega16.h>
#include <delay.h>

const int TIMER0_VALUE = 0; 
const int TIMER1_VALUE = 0x7A11; 
static int active_port = 0;
static unsigned int timer = 0;
unsigned char timer_array[4] = {0};

#define D0 0b0111111;
#define D1 0b0000110;
#define D2 0b1011011;
#define D3 0b1001111;
#define D4 0b1100110;
#define D5 0b1101101;
#define D6 0b1111101;
#define D7 0b0000111;
#define D8 0b1111111;
#define D9 0b1101111;

void timer0()
{
    if (active_port >= 4)
        active_port = 0;             
    PORTC = 0x0F & ~(1 << active_port);
    PORTD = bcd(timer_array [active_port]);
    active_port++;
}
void timer1()
{
    int i,digit = timer;
    timer++;  
    if (timer > 9999)
        timer = 0;
    for (i=0 ; i<4 ; i++)
    {
        timer_array[i] = digit % 10;
        digit /= 10;
    }
}
interrupt [TIM0_OVF] void timer0_OF(void)
{
    TCNT0 = 0xFF - TIMER0_VALUE;
    timer0();
}
interrupt [TIM1_OVF] void timer1_OF(void)
{
    TCNT1 = 0xFFFF - TIMER1_VALUE;
    timer1();  
}
char bcd(int number){
    switch (number){
     case 0:    return D0;
     case 1:    return D1;
     case 2:    return D2;
     case 3:    return D3;
     case 4:    return D4;
     case 5:    return D5;
     case 6:    return D6;
     case 7:    return D7;
     case 8:    return D8;
     case 9:    return D9;
    }
}

void main(void)
{
DDRC = 0x0F; 
DDRD = 0xFF; 
PORTC = 0xFE;

TCCR0 = (0 << WGM00) | (0 << COM01) | (0 << COM00) | (0 << WGM01) | (1 << CS02) | (0 << CS01) | (1 << CS00);
TCNT0 = 0xFF - TIMER0_VALUE;
TCCR1A = (0 << COM1A1) | (0 << COM1A0) | (0 << COM1B1) | (0 << COM1B0) | (0 << WGM11) | (0 << WGM10);
TCCR1B = (0 << ICNC1) | (0 << ICES1) | (0 << WGM13) | (0 << WGM12) | (1 << CS12) | (0 << CS11) | (0 << CS10);
TCNT1 = 0xFFFF - TIMER1_VALUE;
TIMSK = (0 << OCIE2) | (0 << TOIE2) | (0 << TICIE1) | (0 << OCIE1A) | (0 << OCIE1B) | (1 << TOIE1) | (0 << OCIE0) | (1 << TOIE0);

#asm("sei")

timer = 1;
while (1);
}
