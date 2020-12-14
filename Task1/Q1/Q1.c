#include <mega16.h>
static unsigned int time_count;

interrupt [TIM0_OVF] void timer0_ovf_isr(void) 
{
    TCNT0 = 56; 
    ++time_count; 
    if (time_count == 47)
  {
        PORTC.0 = (PORTC.0 ^ 1); //toggle 
        time_count = 0; //reset every 0.5 sec
     }
}

void main (void) {
    DDRC = 0x01;

    TCCR0 = 0x03; //prescaler tp clk/64
    TCNT0 = 0x00;
    OCR0 = 0x00
   
    TIMSK = 0x01;

    #asm ("sei") //enable interrupts

    while (1) 
    {
        ; //do nothing in here
    }
}