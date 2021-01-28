/*
 * UART.h
 *
 *  Created on: 16 dec. 2020
 *      Author: Michiel
 */

#ifndef UART_H_
#define UART_H_

#define PLLR_I        0U
#define PLLF_I        4U
#define PLLQ_I        10U
#define PLLSEL_I      16U
#define PLLREFSEL_I   17U
#define PLLBYPASS_I   18U
#define PLLLOCK_I     31U

#define PLIC      0x0C000000
#define UART1priority *(int*) (PLIC+0x04)
#define InteruptEnable *(int*) (PLIC+0x2000)

#define CPU_FREQ 16000000

#define baseAdressUart0 0x10013000
#define baseAdressUart1 0x10023000

#define txdata0 *(int*) (baseAdressUart0)
#define rxdata0 *(int*) (baseAdressUart0+0x04)
#define TXctrl0 *(int*) (baseAdressUart0+0x08)
#define RXctrl0 *(int*) (baseAdressUart0+0x0C)
#define ie0 	*(int*) (baseAdressUart0+0x10)
#define ip0	    *(int*) (baseAdressUart0+0x14)
#define baud0   *(int*) (baseAdressUart0+0x18)

#define txdata1 *(int*) (baseAdressUart1)
#define rxdata1 *(int*) (baseAdressUart1+0x04)
#define TXctrl1 *(int*) (baseAdressUart1+0x08)
#define RXctrl1 *(int*) (baseAdressUart1+0x0C)
#define ie1 	*(int*) (baseAdressUart1+0x10)
#define ip1 	*(int*) (baseAdressUart1+0x14)
#define baud1   *(int*) (baseAdressUart1+0x18)

#define baseAdressGPIO 0x10012000

#define PinModeIOF 0x38
#define PinModeSEL 0x3C

#define IOF_EN       *(int*)(baseAdressGPIO+PinModeIOF)
#define IOF_SEL		 *(int*)(baseAdressGPIO+PinModeSEL)

void clearArray(char *array);
int calculateBaudDevider(int baudSpeed);
void delay(int counter);

void uartSetup0(int baudSpeed);
void uartSetup0Interupt(int baudSpeed);
void uartSetup1(int baudSpeed);
void uartSendASCI0(char teken);
void uartSendASCI1(char teken);
int uartReceiveASCI0(char *c);
int uartReceiveASCI1(char *c);



void uartReceiveWaitForBackSlashN(int whichUart,char *text);
int uartReceiveWithTimeout(int whichUart,char *text);


void uartSend(int whichUart, char *text);
void uartSendNumber(int number);
void uartSendEnter(int whichUart);

#endif /* UART_H_ */
