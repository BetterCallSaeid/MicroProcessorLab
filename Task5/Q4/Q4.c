#include <mega16.h>
#include <delay.h>

int steps[4] = {9 , 10 , 6 , 5};
int position , counter , currentStep , direction , timerStarted , delay , maxDelay , minDelay;

void main(void)
{
    DDRA=0xff;
    PORTA=0x00;

    DDRC=0x00;
    PINC=0x00;
    currentStep = 0;
    timerStarted = 1;
    direction = -1;
    maxDelay = 200;
    minDelay = -200;
    counter = 0;

    TCCR0=(0<<WGM00) | (0<<COM01) | (0<<COM00) | (0<<WGM01) | (0<<CS02) | (0<<CS01) | (1<<CS00);
    TCNT0 = 255;
    OCR0=0x00;

    TIMSK=(0<<OCIE2) | (0<<TOIE2) | (0<<TICIE1) | (0<<OCIE1A) | (0<<OCIE1B) | (0<<TOIE1) | (0<<OCIE0) | (1<<TOIE0);
    #asm("sei")
while (1)
      {
        if(PINC.2==0 &&  timerStarted==0) {
                 delay = maxDelay;
                 counter = 0;
                 direction = -1;
                 timerStarted = 1;
            }
        }
}

interrupt [TIM0_OVF] void timer0_ovf_isr(void)
{
    TCNT0=0x0C;
    position = 0;

    if(timerStarted==1)
    {
        if(counter>=delay)
        {
            PORTA = steps[position] ;

            if(position < 3)
            {
                ++position;
            } else
            {
                position=0;
            }

            if(direction<0)
            {
                if(delay>minDelay)
                {
                    delay--;
                } else
                {
                    direction = 1;
                }
            } else
            {
                if(delay<maxDelay)
                {
                    delay++;
                } else
                {
                    direction = -1;
                    timerStarted=0;
                }
            }

            counter = 0;
        }

        counter++;
    }

}
