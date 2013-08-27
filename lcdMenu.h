/*----------------------------------------------------------------------------
/ “THE COFFEEWARE LICENSE” (Revision 1):
/ <ihsan@kehribar.me> wrote this file. As long as you retain this notice you
/ can do whatever you want with this stuff. If we meet some day, and you think
/ this stuff is worth it, you can buy me a coffee in return.
/----------------------------------------------------------------------------*/
#include <stdint.h>
#include <stdio.h>
/*---------------------------------------------------------------------------*/
#define lcdMenu_callFunction(fp) ((*fp)())
/*---------------------------------------------------------------------------*/
typedef struct menustate
{	
	uint8_t top;
	uint8_t MAX_ROWS;
	uint8_t last_top;
	uint8_t currentItem;
	uint8_t last_currentItem;
	struct menu* currentMenu;
};
/*---------------------------------------------------------------------------*/
typedef struct menuitem
{
	const char* name;
	void (*handlerFunc)();
	struct menu* child;
};
/*---------------------------------------------------------------------------*/
typedef struct menu
{	
	uint8_t length;
	struct menu* parent;
	struct menuitem** menuArray;
};
/*---------------------------------------------------------------------------*/
void lcdMenu_goUp(struct menustate* ms);
/*---------------------------------------------------------------------------*/
void lcdMenu_goBack(struct menustate* ms);
/*---------------------------------------------------------------------------*/
void lcdMenu_select(struct menustate* ms);
/*---------------------------------------------------------------------------*/
void lcdMenu_goDown(struct menustate* ms);
/*---------------------------------------------------------------------------*/
void lcdMenu_drawMenu(struct menustate* ms);
/*---------------------------------------------------------------------------*/
extern void lcdMenu_goNextLine();
/*---------------------------------------------------------------------------*/
extern void lcdMenu_clearScreen();
/*---------------------------------------------------------------------------*/
extern void lcdMenu_printNormal(const char* message);
/*---------------------------------------------------------------------------*/
extern void lcdMenu_printSpecial(const char* message);
/*---------------------------------------------------------------------------*/
