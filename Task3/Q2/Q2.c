#include <stdio.h>
#include <mega16.h>
#include <delay.h>
#include <lcd.h>

void main(void){
    int i;
    char characters[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    PORTB = 0x00;
    DDRB = 0x00;
    
    lcd_init(16);
    lcd_clear(); 
    
    while(1){
        for(i=0;i<27;i++){
            
            if(i<15)
            {
                 lcd_gotoxy(i,0);
            }else
            	{
                	lcd_gotoxy(i%15,1);
            	} 
            lcd_putchar(characters[i]);
            delay_ms(50); 
            
        }            
        
        lcd_clear(); 
    }
            
}