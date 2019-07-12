/*----------------------------------------------------------------------------
 *      Name:    DEMO.C
 *      Purpose: USB HID Demo
 *      Version: V1.10
 *----------------------------------------------------------------------------
 *      This software is supplied "AS IS" without any warranties, express,
 *      implied or statutory, including but not limited to the implied
 *      warranties of fitness for purpose, satisfactory quality and
 *      noninfringement. Keil extends you a royalty-free right to reproduce
 *      and distribute executable files created using this software for use
 *      on Philips LPC2xxx microcontroller devices only. Nothing else gives
 *      you the right to use this software.
 *
 *      Copyright (c) 2005-2006 Keil Software.
 *---------------------------------------------------------------------------*/

#include <LPC214X.H>                        /* LPC214x definitions */
#include "type.h"
#include "usb.h"
#include "usbcfg.h"
#include "usbhw.h"
#include "usbcore.h"
#include "demo.h"

BYTE InReport[8];                           /* HID Input Report of size 8 bytes*/
                                           
BYTE OutReport;                             /* HID Out Report */
                                           

keyboard_st key;							/*key is declared as the structured*/
BYTE last_data;								/*keep a record of the last data received*/

int toggle=1;								/*used to switch between slide show on/off*/

/*
 *  Get HID Input Report -> InReport
*/

void GetInReport (void) { //This is for Device(LPC2148) to Host PC reporting

    unsigned int current_data=0;
	unsigned int hidcurrent_data=0;

    if ((IOPIN0 & (1<<12)))		  //depending in the push button pressed,current_data is set
	{
		current_data|=1;
	}
	else if((IOPIN0 & (1<<10)))
	{
		current_data|=2;
	}
	else if((IOPIN0 & (1<<8))) 
	{              
      current_data|=4;
	}    
  
    if(last_data==0)				   //to avoid multiple slide changes in a single button press
		hidcurrent_data=current_data;

	switch(hidcurrent_data)
	{
		case 0x01:
			key.modifier=0;
			key.keycode[0]=0x52;		//up key
			break;
		case 0x02:
			key.modifier=0;
			key.keycode[0]=0x51;	    //down key
			break;
		case 0x04:
			
			if(toggle==1){
			key.modifier=0;
			key.keycode[0]=0x29;        //escape key
			toggle=0;
			}else {
			key.modifier=0x02;	        //L-shift
			key.keycode[0]=0x3e;        //F5
			toggle=1;}
			break;
		default:						//default
			key.modifier=0;
			key.keycode[0]=0;
			key.keycode[1]=0;
			key.keycode[2]=0;
			key.keycode[3]=0;
			key.keycode[4]=0;
			key.keycode[5]=0;
			break;
	}

	last_data=current_data;
	memcpy(InReport,&key,sizeof key);
}

void SetOutReport (void) { //This is for Host PC to Device(LPC2148) reporting
}

/* Main Program */
int main (void) {
	 
	IO0DIR= IO0DIR & !((1<<12)); 	/*GPIO ports receiving data from decoder*/
	IO0DIR= IO0DIR & !((1<<10));
	IO0DIR= IO0DIR & !((1<<8)); 
	IO0DIR|=0x000E0000;
    
	key.modifier=0;					/*default configuration*/
	key.reserved=0;
	key.keycode[0]=0;
	key.keycode[1]=0;
	key.keycode[2]=0;
	key.keycode[3]=0;
	key.keycode[4]=0;
	key.keycode[5]=0;

  	USB_Init();                               /* USB Initialization */
  	USB_Connect(TRUE);                        /* USB Connect */

  	while (1);                               /* Loop forever */
}
