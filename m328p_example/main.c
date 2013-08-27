/*-----------------------------------------------------------------------------
/
/
/
/
/
/
/
/
/----------------------------------------------------------------------------*/
#include <stdio.h>
#include <avr/io.h>
#include <avr/delay.h>
/*---------------------------------------------------------------------------*/
#include "./digital.h"
#include "./pcd8544.h"
#include "../lcdMenu.h"
#include "./serial_lib/xitoa.h"
/*---------------------------------------------------------------------------*/
#define BUTTON_DEBUG 1
/*---------------------------------------------------------------------------*/
void init_serial();
void send_char(char c);
/*---------------------------------------------------------------------------*/
void initButtons();
uint8_t handleButtons();
uint8_t upButton_clicked();
uint8_t downButton_clicked();
uint8_t backButton_clicked();
uint8_t selectButton_clicked();
/*---------------------------------------------------------------------------*/
void callback()
{
	xprintf(PSTR("callback from mainmenu!\r\n"));
}
/*---------------------------------------------------------------------------*/
void scallback()
{
	xprintf(PSTR("callback from submenu!\r\n"));
}
/*---------------------------------------------------------------------------*/
struct menu subMenu;
/*---------------------------------------------------------------------------*/
struct menuitem node1 = {"menu1",callback,NULL};
struct menuitem node2 = {"menu2",NULL,&subMenu};
struct menuitem node3 = {"menu3",NULL,&subMenu};
struct menuitem node4 = {"menu4",NULL,&subMenu};
struct menuitem node5 = {"menu5",NULL,&subMenu};
struct menuitem node6 = {"menu6",NULL,&subMenu};
struct menuitem node7 = {"menu7",NULL,&subMenu};
struct menuitem node8 = {"menu8",NULL,&subMenu};
struct menuitem* mainElements[] = {&node1,&node2,&node3,&node4,&node5,&node6,&node7,&node8};
/*---------------------------------------------------------------------------*/
struct menuitem snode1 = {"submenu1",scallback,NULL};
struct menuitem snode2 = {"submenu2",scallback,NULL};
struct menuitem snode3 = {"submenu3",scallback,NULL};
struct menuitem snode4 = {"submenu4",scallback,NULL};
struct menuitem snode5 = {"submenu5",scallback,NULL};
struct menuitem* subElements[] = {&snode1,&snode2,&snode3,&snode4,&snode5};
/*---------------------------------------------------------------------------*/
struct menu mainMenu = {8,NULL,mainElements};
struct menu subMenu = {5,&mainMenu,subElements};
/*---------------------------------------------------------------------------*/
struct menustate myMenuState;
/*---------------------------------------------------------------------------*/
int main()
{
	init_serial();
	initButtons();
	pcd8544_begin(0x29);	

	myMenuState.top = 0;	
	myMenuState.MAX_ROWS = 6;
	myMenuState.last_top = 0;
	myMenuState.currentItem = 0;
	myMenuState.last_currentItem = 0;
	myMenuState.currentMenu = &mainMenu;

	lcdMenu_drawMenu(&myMenuState);

	while(1)
	{
		if(handleButtons(&myMenuState))
		{
			lcdMenu_drawMenu(&myMenuState);
		}
	}
}
/*---------------------------------------------------------------------------*/
void init_serial()
{
	/* 19200 baud rate with 16 MHz Xtal ... */
	const uint8_t ubrr = 51;

	pinMode(D,0,INPUT);
	pinMode(D,1,OUTPUT);

	/* Set baud rate */ 
	UBRR0H = (unsigned char)(ubrr>>8); 
	UBRR0L = (unsigned char)ubrr; 

	/* Enable receiver and transmitter and Receive interupt */ 
	UCSR0B = (1<<RXEN0)|(1<<TXEN0)|(1<<RXCIE0); 

	/* Set frame format: 8data, 1stop bit no parity */ 
	UCSR0C = (1<<UCSZ01)|(1<<UCSZ00); 

	/* Set the library ... */
	xfunc_out = send_char;
}
/*---------------------------------------------------------------------------*/
void send_char(char c)
{
    /* Wait for empty transmit buffer ... */
    while(!(UCSR0A & (1<<UDRE0)));

    /* Start sending the data! */
    UDR0 = c;

    /* Wait until the transmission is over ... */
    while(!(UCSR0A & (1<<TXC0)));
}
/*---------------------------------------------------------------------------*/
void initButtons()
{
	/* select button */
	pinMode(C,0,INPUT);
	internalPullup(C,0,ENABLE);
	
	/* up button */
	pinMode(C,1,INPUT);
	internalPullup(C,1,ENABLE);
	
	/* back button */
	pinMode(C,2,INPUT);
	internalPullup(C,2,ENABLE);
	
	/* down button */
	pinMode(C,3,INPUT);
	internalPullup(C,3,ENABLE);
}
/*---------------------------------------------------------------------------*/
uint8_t upButton_clicked()
{
	if(digitalRead(C,1)==LOW)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
/*---------------------------------------------------------------------------*/
uint8_t downButton_clicked()
{
	if(digitalRead(C,3)==LOW)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
/*---------------------------------------------------------------------------*/
uint8_t backButton_clicked()
{
	if(digitalRead(C,2)==LOW)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
/*---------------------------------------------------------------------------*/
uint8_t selectButton_clicked()
{
	if(digitalRead(C,0)==LOW)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
/*---------------------------------------------------------------------------*/
uint8_t handleButtons(struct menustate* ms)
{
	uint8_t activity = 0;
	if(backButton_clicked())
	{
		while(backButton_clicked());
		activity = 1;
		lcdMenu_goBack(ms);
		#if BUTTON_DEBUG
			xprintf(PSTR("> Back!\r\n"));
		#endif
	}
	else if(selectButton_clicked())
	{
		while(selectButton_clicked());
		activity = 1;
		lcdMenu_select(ms);
		#if BUTTON_DEBUG
			xprintf(PSTR("> Select!\r\n"));
		#endif
	}
	else if(downButton_clicked())
	{
		while(downButton_clicked());
		activity = 1;
		lcdMenu_goDown(ms);
		#if BUTTON_DEBUG
			xprintf(PSTR("> Down!\r\n"));
		#endif
	}
	else if(upButton_clicked())
	{
		while(upButton_clicked());
		activity = 1;
		lcdMenu_goUp(ms);
		#if BUTTON_DEBUG
			xprintf(PSTR("> Up!\r\n"));
		#endif
	}
	return activity;
}
/*---------------------------------------------------------------------------*/
void lcdMenu_clearScreen()
{
	pcd8544_clear();
	pcd8544_gotoRc(0,0);
}
/*---------------------------------------------------------------------------*/
void lcdMenu_printNormal(const char* message)
{
	pcd8544_print(" ");
	pcd8544_print(message);
}
/*---------------------------------------------------------------------------*/
void lcdMenu_printSpecial(const char* message)
{	
	pcd8544_print(">");
	pcd8544_print(message);
}
/*---------------------------------------------------------------------------*/
void lcdMenu_goNextLine()
{
	pcd8544_print("\r\n");
}
/*---------------------------------------------------------------------------*/