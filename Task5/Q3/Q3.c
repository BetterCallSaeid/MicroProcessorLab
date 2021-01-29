#include <mega16.h>

int steps[4] = {9 , 10 , 6 , 5};
int delay;
int position;
int flag;

void main(void)
{
    delay = 0;  
    position = 1; 
    flag = 1;
    
    DDRC = 0x00;   
    PINC = 0x00;  
       
    DDRA = 0xff;  
    PORTA = 0x00; 

    TCCR0=(0<<WGM00) | (0<<COM01) | (0<<COM00) | (0<<WGM01) | (1<<CS02) | (0<<CS01) | (1<<CS00);
    TCNT0=0x0C;
    OCR0=0x00;

    TIMSK=(0<<OCIE2) | (0<<TOIE2) | (0<<TICIE1) | (0<<OCIE1A) | (0<<OCIE1B) | (0<<TOIE1) | (0<<OCIE0) | (1<<TOIE0);

    #asm("sei")

    while (1) {
        if(PINC.2==0) { 
            if(flag>0) {
                flag = -1;
                if(position>0) {
                    --position;
                } else {
                    position=3;
                }      
            } else {
                flag = 1;    
                if(position<3) {
                    ++position;
                } else {
                    position=0;
                }       
            }
        }
    }
}

interrupt [TIM0_OVF] void timer0_ovf_isr(void)
{
    TCNT0=0x0C;
    
    PORTA.0 = steps[position][0];  
    PORTA.1 = steps[position][1];
    PORTA.2 = steps[position][2];
    PORTA.3 = steps[position][3];
    
    if(flag>0)
    {
        if(position<3)
        {
            ++position;
        } else
        {
            position=0;
        }  
    } else
        {
            if(position>0)
            {
                --position;
            } else
            {
                position=3;
            }     
        }
         
    
}

