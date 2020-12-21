/* Pins
7    g
6    b
5    d
4    f
3    DP
2    e
1    a
0    c  */
                    
#include <avr/io.h>
#include <util/delay.h>

#define F_CPU 1000000UL  // 1MHz internal clock 
#define PORT_7_SEGMENT PORTB
#define DDR_7_SEGMENT DDRB

void SevenSegment(uint8_t count,uint8_t dp, uint8_t dec)
{

   if(count <dec)
   {
      switch (count)
      {
         case 0:
         PORT_7_SEGMENT=0b10001000;
         break;

         case 1:
         PORT_7_SEGMENT=0b10111110;
         break;

         case 2:
         PORT_7_SEGMENT=0b00011001;
         break;

         case 3:
         PORT_7_SEGMENT=0b00011100;
         break;

         case 4:
         PORT_7_SEGMENT=0b00101110;
         break;

         case 5:
         PORT_7_SEGMENT=0b01001100;
         break;

         case 6:
         PORT_7_SEGMENT=0b01001000;
         break;

         case 7:
         PORT_7_SEGMENT=0b10111100;
         break;

         case 8:
         PORT_7_SEGMENT=0b00001000;
         break;

         case 9:
         PORT_7_SEGMENT=0b00001100;
         break;
		
      }
      if(dp)
      {
         // if decimal point should be displayed make DP bit Low
         PORT_7_SEGMENT&=0b11110111;
      }
   }
   else
   {
      // E (Error) when display can't handle the number, for example greater than 9
      PORT_7_SEGMENT=0b01111101;
   }
}



int main()
{
   DDR_7_SEGMENT=0xFF;    // make all of them as output
   PORT_7_SEGMENT=0xFF;   // 7segment is off

   uint8_t count=0;
   uint8_t dec=10; // cuz of one digit (decimal)

   while(1) 
   {
      SevenSegment(count,0, dec);

      count++;
      if(count==dec)  
      {
         count=0;
      }
      _delay_ms(100);
   }
}
