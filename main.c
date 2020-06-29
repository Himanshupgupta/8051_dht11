#include<reg51.h>
#include<dht.h>
#include<stdio.h>

//LCD Module Connections
sbit RS = P0^0;                                                                   
sbit EN = P0^1;                            
sbit D0 = P2^0;
sbit D1 = P2^1;
sbit D2 = P2^2;
sbit D3 = P2^3;
sbit D4 = P2^4;
sbit D5 = P2^5;
sbit D6 = P2^6;
sbit D7 = P2^7;

//dht11 connection
sbit dht=P3^0;

int hum_l,hum_h,temp_l,temp_h;

void delay()    //delay by timer function
{
	TMOD=0x01;    //select timer 0 mode 1
	TH0=0xFC;     //load FC67 for 1000 Count
	TL0=0x67;
	TCON=0x10;    //start timer 0
	
	while(!(TCON & 0x20));
	{
		TCON &=~0x10;    //stop timer 0
		TCON &=~0x20;    //clear overflow flag
	}
}

void timer_delay(int ms)
{
	int i;
	for(i=0;i<ms;i++)
		delay();
}


//8051 requset function
void request()
{
	dht=0;
	timer_delay(20);
	dht=1;
}

//dht response 010
void response()
{
	while(dht==1);
	while(dht==0);
	while(dht==1);
}

timer_delay_30us()
{
	TMOD=0x01;    //select timer 0 mode 1
	TH0=0xFF;     //load FC67 for 1000 Count
	TL0=0xE5;
	TCON=0x10;    //start timer 0
	
	while(!(TCON & 0x20));
	{
		TCON &=~0x10;    //stop timer 0
		TCON &=~0x20;    //clear overflow flag
}
}
//Check received bit is 0 or 1
int receive_data()
{
	int i,c=0;
	for(i=0;i<8;i++)
	{
		while(dht==0);
		{
			timer_delay_30us();
			if(dht==1)
				c=(c<<1)|(0x01);
			else
				c=c<<1;
			while(dht==1);
	}}
	return c;
}


void main()
{
	int i,hum=80;
	float temp=28.6;
	unsigned char humidity[20],temperature[20];
	                                  
  //sprintf(humidity,"HUMIDITY:%d",hum);
	//sprintf(temperature,"TEMP.:%0.2f",temp);
	
	Lcd8_init();   //Init lcd
	
	while(1)
  {  
		request();
		response();
		hum_l=receive_data();
		hum_h=receive_data();
		temp_l=receive_data();
		temp_h=receive_data();
		sprintf(humidity,"HUMIDITY:%d.%d",hum_l,hum_h);
		sprintf(temperature,"TEMP.:%d.%d",temp_l,temp_h);
		Lcd8_Set_Cursor(1,1);
	  Lcd8_Write_String(temperature);
		Lcd8_Set_Cursor(2,1);
		Lcd8_Write_String(humidity);
		timer_delay(3000);
  }
}