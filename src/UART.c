/*
 * UART.c
 *
 *  Created on: 16 dec. 2020
 *      Author: Michiel
 */

#include "string.h"
#include "UART.h"



void delay(int counter)
{
    volatile int i = 0;
    while (i < counter) {
        i++;
    }
}
int calculateBaudDevider(int baudSpeed)
{
	return  CPU_FREQ/baudSpeed-1;
}
void uartSetup0(int baudSpeed)
{

	baud0 = calculateBaudDevider(baudSpeed);
	TXctrl0=0x01;
	RXctrl0=0x01;
	ie0=0x0;
	ip0=0x02;
	IOF_EN |=(1<<16)|(1<<17);
	delay(1000);

}
void uartSetup0Interupt(int baudSpeed)
{
	baud0 = calculateBaudDevider(baudSpeed);
	TXctrl0=0x01;
	RXctrl0=0x01;
	ie0=0x0;
	ip0=0x02;
	IOF_EN |=(1<<16)|(1<<17);
	delay(1000);
}
void uartSetup1(int baudSpeed)
{

	baud1=calculateBaudDevider(baudSpeed);
	TXctrl1=0x01;
	RXctrl1=0x01;
	ie1=0x0;
	ip1=0x02;
	IOF_EN |=(1<<23)|(1<<18);
	delay(1000);
}
void uartSendASCI0(char teken)
{
	while((txdata0 & (1<<31))!=0x0){}
	txdata0=teken & 0xFFU;
}
void uartSendASCI1(char teken)
{
	while((txdata1 & (1<<31))!=0x0){}
	txdata1=teken & 0xFFU;
}
int uartReceiveASCI0(char *c)
{
	int   rx = rxdata0;
	if (!(rx & (1<<31)))
	{
		*c = rx & 0xFFu;
		return 1;
	}
	return 0;
}
int uartReceiveASCI1(char *c)
{
	int   rx = rxdata1;
	if (!(rx & (1<<31)))
	{
		*c = rx & 0xFFu;
		return 1;
	}
	return 0;
}
void uartSend(int whichUart,char *text)
{
	while(*text !=0x0)
	{
		switch(whichUart)
		{
		case 0:
			uartSendASCI0(*text);
			text++;
		break;
		case 1:
			uartSendASCI1(*text);
			text++;
		break;

		default:
			break;
		}
	}

}
void uartSendNumber(int number)
{
	if(number==0)
	{
		uartSendASCI0('0');
	}
	else
	{
		int unit[10];
			int i=0;
			while(number !=0)
			{
				unit[i]= number %10;
				i++;
				number/=10;
			}
			while(i>0)
			{
				i--;
				uartSendASCI0(unit[i]+'0');

			}
	}
}
void uartSendEnter(int whichUart)
{
	if(whichUart==0)
	{
		uartSend(0,"\r\n");
	}
	if(whichUart==1)
	{
		uartSend(1,"\r\n");
	}
}

void clearArray(char *array)
{
	for(int i=0;i<256;i++)
	{
		*(array+i)=0x0;
	}
}

void uartReceiveWaitForBackSlashN(int whichUart,char *text)
{
	clearArray(text);
	int recievedCHAR =0;
	while(1)
	{	switch(whichUart)
		{
			case 0:
				recievedCHAR=uartReceiveASCI0(text);
				break;
			case 1:
				recievedCHAR=uartReceiveASCI0(text);
				break;
			default:
				return;
		}
		if(recievedCHAR)
		{
			if(*text=='\n')
			{
				return;
			}
			if(*text !=0x0)
			{
				text++;
			}

		}
	}
}
int uartReceiveWithTimeout(int whichUart,char *text)
{
	int timeout =0;
	clearArray(text);
	while(timeout<5000000)
	{
		timeout++;
		switch(whichUart)
		{
		case 0:
			if(uartReceiveASCI0(text))
			{
				if(*text=='\n')
				{
					return 0;
				}
				timeout=0;
				text++;
			}
			break;
		case 1:
			if(uartReceiveASCI1(text))
			{
				if(*text=='\n')
				{
					return 0;
				}
				timeout=0;
				text++;
			}
		break;
		default :
		break;
		}
	}
	return 1;
}

//	waitForUartReceiveASCI(&c);
//	uartSendASCI0(c);
/*	if(uartReceiveASCI0(&c))
	{
		uartSendASCI0(c);
	}*/
//	uartReceive0(tekst);
//	uartSend(0,tekst);

//	uartReceive1(tekst1);
//	uartSend(0,tekst1);*/

//	SendATcommand("AT \r\n");

//	uartReceive(tekst);
//	waitForUartReceiveASCI(&c);
//	uartSendASCI(c);


/*	uartReceiveASCI1(&c);
	uartSendASCI0(c);*/

