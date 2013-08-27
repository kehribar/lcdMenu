/*-----------------------------------------------------------------------------
/ Pure C based pcd8544 library.
/------------------------------------------------------------------------------
/ This library is derived from C++ based Arduino/Maple library for pcd8544 
/ lcd controller. https://github.com/snigelen/pcd8544
/----------------------------------------------------------------------------*/
#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include "digital.h"
#include <stdint.h>
/*---------------------------------------------------------------------------*/
#define PCD8544_FUNCTION_SET (1<<5)
#define PCD8544_FUNCTION_PD  (1<<2)
#define PCD8544_FUNCTION_V   (1<<1)
#define PCD8544_FUNCTION_H   (1<<0)
/*---------------------------------------------------------------------------*/
#define PCD8544_DISPLAY_CONTROL (1<<3)
#define PCD8544_DISPLAY_CONTROL_D (1<<2)
#define PCD8544_DISPLAY_CONTROL_E (1<<0)
#define PCD8544_DISPLAY_CONTROL_BLANK 0
#define PCD8544_DISPLAY_CONTROL_NORMAL_MODE PCD8544_DISPLAY_CONTROL_D
#define PCD8544_DISPLAY_CONTROL_ALL_ON PCD8544_DISPLAY_CONTROL_E
#define PCD8544_DISPLAY_CONTROL_INVERSE (PCD8544_DISPLAY_CONTROL_D|PCD8544_DISPLAY_CONTROL_E)
/*---------------------------------------------------------------------------*/
#define PCD8544_SET_Y_ADDRESS (1<<6)
#define PCD8544_Y_ADRESS_MASK 0b111
#define PCD8544_SET_X_ADDRESS (1<<7)
#define PCD8544_X_ADRESS_MASK 0b01111111
/*---------------------------------------------------------------------------*/
#define PCD8544_TEMP_CONTROL (1<<2)
#define PCD8544_TEMP_TC1     (1<<1)
#define PCD8544_TEMP_TC0     (1<<0)
/*---------------------------------------------------------------------------*/
#define PCD8544_BIAS     (1<<4)
#define PCD8544_BIAS_BS2 (1<<2)
#define PCD8544_BIAS_BS1 (1<<1)
#define PCD8544_BIAS_BS0 (1<<0)
/*---------------------------------------------------------------------------*/
#define PCD8544_VOP (1<<7)
/*---------------------------------------------------------------------------*/
#define PCD8544_LINES 6
#define PCD8544_COLS  14
#define PCD8544_WIDTH  84
#define PCD8544_HEIGHT 48
/*---------------------------------------------------------------------------*/
uint8_t current_row, current_column;
/*---------------------------------------------------------------------------*/
void pcd8544_begin(uint8_t contrast);
/*---------------------------------------------------------------------------*/
void pcd8544_clear(void);
/*---------------------------------------------------------------------------*/
void pcd8544_setCursor(uint8_t column, uint8_t row);
/*---------------------------------------------------------------------------*/
void pcd8544_gotoRc(uint8_t row, uint8_t pixel_column);
/*---------------------------------------------------------------------------*/
void pcd8544_data(uint8_t data);
/*---------------------------------------------------------------------------*/
void pcd8544_smallNum(uint8_t num, uint8_t shift);
/*---------------------------------------------------------------------------*/
void pcd8544_clearRestOfLine(void);
/*---------------------------------------------------------------------------*/
void pcd8544_bitmap(uint8_t *data, uint8_t rows, uint8_t columns);
/*---------------------------------------------------------------------------*/
void pcd8544_send(uint8_t dc, uint8_t data);
/*---------------------------------------------------------------------------*/
void pcd8544_command(uint8_t data);
/*---------------------------------------------------------------------------*/
void pcd8544_write(uint8_t ch);
/*---------------------------------------------------------------------------*/
void pcd8544_inc_row_column(void);
/*---------------------------------------------------------------------------*/
void pcd8544_print(const char* message);
/*---------------------------------------------------------------------------*/
