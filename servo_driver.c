#include<lpc21xx.h>
void servo_init(void)
{
 //select PWM2 function on P0.7
 PINSEL0&=~(3<<14);
 PINSEL0|=(2<<14);

 PWMTCR=(1<<1);

 PWMPR=14;
 PWMMR0=20000;
 PWMMR2=1500;
 PWMMCR=(1<<1);
 PWMPCR=(1<<10);
 PWMLER=(1<<0)|(1<<2);
 PWMTCR=(1<<0)|(1<<3);

}

void servo_angle(unsigned int angle)
{
 if(angle>180)
                         angle=180;
 PWMMR2=1000+(angle*1000)/150;
 PWMLER=(1<<2);
}
