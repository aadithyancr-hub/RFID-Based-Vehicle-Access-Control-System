#include<lpc21xx.h>
 #include"header.h"
 #define LED1 0XF
 #define LED2 0XFF
 int main()
 {
 int i,entry=0;
 char key,password[5],pass[5]="1918";
 unsigned char rfid_og[13]="4900C8E53F5B",rfid[13];
 IODIR0|=0XFF;
 IOSET0=0XFF;
 keypad_init();
 lcd_init();
 servo_init();
 uart0_init(9600);
 while(1)
 {
 l:
 IOSET0=0xFF;
  uart0_string("\r\nSCAN RFID : ");
  uart0_rx_string(rfid,12);
  uart0_string(rfid);
  if(my_strcmp(rfid,rfid_og)==0)
  {
    IOCLR0=LED1;
    uart0_string("\r\n-----Have a safe ride-----");
    servo_angle(180);
    delay_ms(1000);
    servo_angle(0);
    return;
  }
  else
  {
  uart0_string("\r\nINVALID RFID");
   uart0_string("\r\nENTER THE KEY:  ");
   for(i=0;i<4;i++)
                          {
                          key=keypad_read();
                          password[i]=key;
                          uart0_tx(key);
                          }
                          password[4]='\0' ;
   if(strcmp(pass,password)==0)
   {
    IOCLR0=LED1;
    uart0_string("\r\n-----Have a safe ride-----");
    servo_angle(180);
    delay_ms(1000);
    servo_angle(0);
    return;
   }
   else
   {
   entry++;
    IOCLR0=LED2;
    uart0_string("\r\nNO ENTRY");
    servo_angle(0);
    if(entry<=3)
    goto l;
    else
    {
     uart0_string("\r\nINVALID AUTHORISATION");
     return;
    }
   }
