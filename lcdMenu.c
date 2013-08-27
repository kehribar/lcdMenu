/*----------------------------------------------------------------------------
/ “THE COFFEEWARE LICENSE” (Revision 1):
/ <ihsan@kehribar.me> wrote this file. As long as you retain this notice you
/ can do whatever you want with this stuff. If we meet some day, and you think
/ this stuff is worth it, you can buy me a coffee in return.
/----------------------------------------------------------------------------*/
#include "lcdMenu.h"
/*---------------------------------------------------------------------------*/
void lcdMenu_goBack(struct menustate* ms)
{
	if(ms->currentMenu->parent != NULL)
	{
		ms->currentMenu = ms->currentMenu->parent;		
		ms->top = ms->last_top;
		ms->currentItem = ms->last_currentItem;		
	}
}
/*---------------------------------------------------------------------------*/
void lcdMenu_select(struct menustate* ms)
{
	if(ms->currentMenu->menuArray[ms->currentItem]->child != NULL)
	{
		ms->currentMenu = ms->currentMenu->menuArray[ms->currentItem]->child;
		ms->last_top = ms->top;
		ms->last_currentItem = ms->currentItem;
		ms->top = 0;
		ms->currentItem = 0;
	}
	else if(ms->currentMenu->menuArray[ms->currentItem]->handlerFunc != NULL)
	{
		lcdMenu_callFunction(ms->currentMenu->menuArray[ms->currentItem]->handlerFunc);
	}
}
/*---------------------------------------------------------------------------*/
void lcdMenu_goDown(struct menustate* ms)
{
	if(ms->top != ms->currentMenu->length)
	{
		if(ms->currentItem != (ms->currentMenu->length-1))
		{
			ms->currentItem += 1;
			if(((ms->currentItem)-(ms->top))==ms->MAX_ROWS)
			{
				ms->top += 1;
			}
		}
	}	
}
/*---------------------------------------------------------------------------*/
void lcdMenu_goUp(struct menustate* ms)
{
	if(!((ms->top==0)&(ms->currentItem==0)))
	{
		ms->currentItem = ms->currentItem - 1;
		if((ms->top > ms->currentItem))
		{
			ms->top = ms->top -1;
		}
	}	
}
/*---------------------------------------------------------------------------*/
void lcdMenu_drawMenu(struct menustate* ms)
{
	uint8_t i;

	lcdMenu_clearScreen();
	
	for (i = ms->top; i < ms->top+ms->MAX_ROWS; ++i)
	{
		if(i<ms->currentMenu->length)
		{
			if (ms->currentItem==i)
			{
				lcdMenu_printSpecial(ms->currentMenu->menuArray[i]->name);
				lcdMenu_goNextLine();
			}
			else
			{
				lcdMenu_printNormal(ms->currentMenu->menuArray[i]->name);
				lcdMenu_goNextLine();
			}
		}
		else
		{
			lcdMenu_goNextLine();
		}
	}	
}
/*---------------------------------------------------------------------------*/