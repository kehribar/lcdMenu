/*-----------------------------------------------------------------------------
/ Pure C based pcd8544 library.
/------------------------------------------------------------------------------
/ This library is derived from C++ based Arduino/Maple library for pcd8544 
/ lcd controller. https://github.com/snigelen/pcd8544
/----------------------------------------------------------------------------*/
#include "pcd8544.h"
/*---------------------------------------------------------------------------*/
const unsigned char PROGMEM small_num[][4] = {
	{0x0e,0x15,0x0e,0x00}, // 48, zero
	{0x12,0x1f,0x10,0x00}, // 49, one
	{0x12,0x19,0x16,0x00}, // 50, two
	{0x11,0x15,0x0b,0x00}, // 51, three
	{0x07,0x04,0x1f,0x00}, // 52, four
	{0x17,0x15,0x09,0x00}, // 53, five
	{0x0e,0x15,0x09,0x00}, // 54, six
	{0x19,0x05,0x03,0x00}, // 55, seven
	{0x1a,0x15,0x0b,0x00}, // 56, eight
	{0x12,0x15,0x0e,0x00}, // 57, nine
	{0x00,0x10,0x00,0x00}, // 46, period
};
/*---------------------------------------------------------------------------*/
const unsigned char PROGMEM font6x8 [][5]  =  {
	{0x00,0x00,0x00,0x00,0x00,}, // ' ' 32
	{0x00,0x00,0x5F,0x00,0x00,}, // '!' 33
	{0x00,0x07,0x00,0x07,0x00,}, // '"' 34
	{0x14,0x7F,0x14,0x7F,0x14,}, // '#' 35
	{0x24,0x2A,0x7F,0x2A,0x12,}, // '$' 36
	{0x23,0x13,0x08,0x64,0x62,}, // '%' 37
	{0x36,0x49,0x55,0x22,0x50,}, // '&' 38
	{0x00,0x05,0x03,0x00,0x00,}, // ''' 39
	{0x00,0x1C,0x22,0x41,0x00,}, // '(' 40
	{0x00,0x41,0x22,0x1C,0x00,}, // ')' 41
	{0x14,0x08,0x3E,0x08,0x14,}, // '*' 42
	{0x08,0x08,0x3E,0x08,0x08,}, // '+' 43
	{0x00,0x50,0x30,0x00,0x00,}, // ',' 44
	{0x08,0x08,0x08,0x08,0x08,}, // '-' 45
	{0x00,0x60,0x60,0x00,0x00,}, // '.' 46
	{0x20,0x10,0x08,0x04,0x02,}, // '/' 47
	{0x3E,0x51,0x49,0x45,0x3E,}, // '0' 48
	{0x00,0x42,0x7F,0x40,0x00,}, // '1' 49
	{0x42,0x61,0x51,0x49,0x46,}, // '2' 50
	{0x21,0x41,0x45,0x4B,0x31,}, // '3' 51
	{0x18,0x14,0x12,0x7F,0x10,}, // '4' 52
	{0x27,0x45,0x45,0x45,0x39,}, // '5' 53
	{0x3C,0x4A,0x49,0x49,0x30,}, // '6' 54
	{0x03,0x01,0x71,0x09,0x07,}, // '7' 55
	{0x36,0x49,0x49,0x49,0x36,}, // '8' 56
	{0x06,0x49,0x49,0x29,0x16,}, // '9' 57
	{0x00,0x36,0x36,0x00,0x00,}, // ':' 58
	{0x00,0x56,0x36,0x00,0x00,}, // ';' 59
	{0x08,0x14,0x22,0x41,0x00,}, // '<' 60
	{0x14,0x14,0x14,0x14,0x14,}, // '=' 61
	{0x00,0x41,0x22,0x14,0x08,}, // '>' 62
	{0x02,0x01,0x51,0x09,0x06,}, // '?' 63
	{0x32,0x49,0x79,0x41,0x3E,}, // '@' 64
	{0x7E,0x11,0x11,0x11,0x7E,}, // 'A' 65
	{0x7F,0x49,0x49,0x49,0x36,}, // 'B' 66
	{0x3E,0x41,0x41,0x41,0x22,}, // 'C' 67
	{0x7F,0x41,0x41,0x22,0x1C,}, // 'D' 68
	{0x7F,0x49,0x49,0x49,0x41,}, // 'E' 69
	{0x7F,0x09,0x09,0x01,0x01,}, // 'F' 70
	{0x3E,0x41,0x49,0x49,0x3A,}, // 'G' 71
	{0x7F,0x08,0x08,0x08,0x7F,}, // 'H' 72
	{0x00,0x41,0x7F,0x41,0x00,}, // 'I' 73
	{0x20,0x41,0x41,0x3F,0x01,}, // 'J' 74
	{0x7F,0x08,0x14,0x22,0x41,}, // 'K' 75
	{0x7F,0x40,0x40,0x40,0x40,}, // 'L' 76
	{0x7F,0x02,0x0C,0x02,0x7F,}, // 'M' 77
	{0x7F,0x04,0x08,0x10,0x7F,}, // 'N' 78
	{0x3E,0x41,0x41,0x41,0x3E,}, // 'O' 79
	{0x7F,0x09,0x09,0x09,0x06,}, // 'P' 80
	{0x3E,0x41,0x51,0x21,0x5E,}, // 'Q' 81
	{0x7F,0x09,0x19,0x29,0x46,}, // 'R' 82
	{0x26,0x49,0x49,0x49,0x32,}, // 'S' 83
	{0x01,0x01,0x7F,0x01,0x01,}, // 'T' 84
	{0x3F,0x40,0x40,0x40,0x3F,}, // 'U' 85
	{0x1F,0x20,0x40,0x20,0x1F,}, // 'V' 86
	{0x3F,0x40,0x38,0x40,0x3F,}, // 'W' 87
	{0x63,0x14,0x08,0x14,0x63,}, // 'X' 88
	{0x07,0x08,0x70,0x08,0x07,}, // 'Y' 89
	{0x61,0x51,0x49,0x45,0x43,}, // 'Z' 90
	{0x00,0x7F,0x41,0x41,0x00,}, // '[' 91
	{0x02,0x04,0x08,0x10,0x20,}, // '\' 92
	{0x00,0x41,0x41,0x7F,0x00,}, // ']' 93
	{0x04,0x02,0x01,0x02,0x04,}, // '^' 94
	{0x40,0x40,0x40,0x40,0x40,}, // '_' 95
	{0x00,0x01,0x02,0x04,0x00,}, // '`' 96
	{0x20,0x54,0x54,0x54,0x78,}, // 'a' 97
	{0x7F,0x48,0x44,0x44,0x38,}, // 'b' 98
	{0x38,0x44,0x44,0x44,0x20,}, // 'c' 99
	{0x38,0x44,0x44,0x48,0x3F,}, // 'd' 100
	{0x38,0x54,0x54,0x54,0x18,}, // 'e' 101
	{0x08,0x7E,0x09,0x01,0x02,}, // 'f' 102
	{0x0C,0x52,0x52,0x52,0x3E,}, // 'g' 103
	{0x7F,0x08,0x04,0x04,0x78,}, // 'h' 104
	{0x00,0x44,0x7D,0x40,0x00,}, // 'i' 105
	{0x20,0x40,0x45,0x3C,0x00,}, // 'j' 106
	{0x7F,0x10,0x28,0x44,0x00,}, // 'k' 107
	{0x00,0x41,0x7F,0x40,0x00,}, // 'l' 108
	{0x7C,0x04,0x18,0x04,0x78,}, // 'm' 109
	{0x7C,0x08,0x04,0x04,0x78,}, // 'n' 110
	{0x38,0x44,0x44,0x44,0x38,}, // 'o' 111
	{0x7C,0x14,0x14,0x14,0x08,}, // 'p' 112
	{0x08,0x14,0x14,0x18,0x7C,}, // 'q' 113
	{0x7C,0x08,0x04,0x04,0x08,}, // 'r' 114
	{0x48,0x54,0x54,0x54,0x20,}, // 's' 115
	{0x04,0x3F,0x44,0x40,0x20,}, // 't' 116
	{0x3C,0x40,0x40,0x20,0x7C,}, // 'u' 117
	{0x1C,0x20,0x40,0x20,0x1C,}, // 'v' 118
	{0x3C,0x40,0x30,0x40,0x3C,}, // 'w' 119
	{0x44,0x28,0x10,0x28,0x44,}, // 'x' 120
	{0x0C,0x50,0x50,0x50,0x3C,}, // 'y' 121
	{0x44,0x64,0x54,0x4C,0x44,}, // 'z' 122
	{0x00,0x08,0x36,0x41,0x00,}, // '{' 123
	{0x00,0x00,0x7F,0x00,0x00,}, // '|' 124
	{0x00,0x41,0x36,0x08,0x00,}, // '}' 125
	{0x10,0x08,0x08,0x10,0x08,}, // '~' 126
	{0x08,0x1C,0x2A,0x08,0x08,} //  <-  127
};
/*---------------------------------------------------------------------------*/
void pcd8544_begin(uint8_t contrast)
{
	// cs pin
	// pinMode(cs,OUTPUT);

	// reset pin
	pinMode(B,0,OUTPUT);

	// DC pin
	pinMode(B,1,OUTPUT);

	// DATA pin
	pinMode(B,2,OUTPUT);

	// CLK pin
	pinMode(B,3,OUTPUT);

	// set reset low
	digitalWrite(B,0,LOW);	
	// wait a little amount of time
	_delay_ms(1);
	// set reset high
	digitalWrite(B,0,HIGH);
  
	// Extenden instructions and !powerdown
	// and horizontal adressing (autoincrement of x-adress)
	pcd8544_command(PCD8544_FUNCTION_SET | PCD8544_FUNCTION_H);
	// Set Vop to 0x3F
	pcd8544_command(PCD8544_VOP | contrast);
	// Vlcd temp. coeff. 0
	pcd8544_command(PCD8544_TEMP_CONTROL);
	// Bias system 4, 1:48
	pcd8544_command(PCD8544_BIAS | PCD8544_BIAS_BS1 | PCD8544_BIAS_BS0);
	// Set H = 0 for normal instructions
	pcd8544_command(PCD8544_FUNCTION_SET);  
	// Normal mode
	pcd8544_command(PCD8544_DISPLAY_CONTROL | PCD8544_DISPLAY_CONTROL_NORMAL_MODE);
}
/*---------------------------------------------------------------------------*/
void pcd8544_clear(void)
{
	int i;
	for (i = 0; i < PCD8544_WIDTH*PCD8544_LINES; i++)
	{
		pcd8544_data(0);
	}
}
/*---------------------------------------------------------------------------*/
void pcd8544_write(uint8_t ch)
{
	uint8_t i;

	if (ch == '\r')
	{
		pcd8544_gotoRc(current_row, 0);
	}
	if (ch == '\n')
	{
		pcd8544_gotoRc(current_row+1, current_column);
	}
	if (ch >= ' ' && ch <= 127) 
	{
		for (i = 0; i < 5; i++)
		{
			pcd8544_data(pgm_read_byte(&font6x8[ch-' '][i]) <<1);
		}
		pcd8544_data(0);
	}
}
/*---------------------------------------------------------------------------*/
void pcd8544_data(uint8_t data)
{
	pcd8544_send(1, data);
}
/*---------------------------------------------------------------------------*/
void pcd8544_command(uint8_t data)
{
	pcd8544_send(0, data);
}
/*---------------------------------------------------------------------------*/
void pcd8544_send(uint8_t data_or_command, uint8_t data)
{
	uint8_t i = 0;

	// dc pin
	digitalWrite(B,1,data_or_command);
	
	// digitalWrite(cs, LOW);		    

	// sck low
    digitalWrite(B,3,LOW);

    for(i=0;i<8;i++)
    {

        if(data & (1<<(7-i)))
        {
        	// din high
            digitalWrite(B,2,HIGH);
        }
        else
        {
        	// din low
            digitalWrite(B,2,LOW);
        }

        // sck high
        digitalWrite(B,3,HIGH);

        // sck low
        digitalWrite(B,3,LOW);
    }
	
	// digitalWrite(cs, HIGH);
	
	if(data_or_command)
	{
		pcd8544_inc_row_column();
	}
}
/*---------------------------------------------------------------------------*/
void pcd8544_setCursor(uint8_t column, uint8_t row)
{
	pcd8544_gotoRc(row, 6*column);
}
/*---------------------------------------------------------------------------*/
void pcd8544_gotoRc(uint8_t row, uint8_t column)
{
	if (row >= PCD8544_LINES)
	{
		row %= PCD8544_LINES;
	}
	if (column >= PCD8544_WIDTH)
	{
		row %= PCD8544_WIDTH;
	}
	pcd8544_command(PCD8544_SET_X_ADDRESS | column);
	pcd8544_command(PCD8544_SET_Y_ADDRESS | row);
	current_row = row;
	current_column = column;
}
/*---------------------------------------------------------------------------*/
void pcd8544_inc_row_column(void)
{
	if (++current_column >= PCD8544_WIDTH) 
	{
		current_column = 0;
		if (++current_row >= PCD8544_LINES)
		{
			current_row = 0;
		}
	}
}
/*---------------------------------------------------------------------------*/
void pcd8544_smallNum(uint8_t num, uint8_t shift)
{
	uint8_t i;
	for (i = 0; i < 4; i++)
	{
		pcd8544_data(pgm_read_byte(&small_num[num][i])<<shift);
	}
}
/*---------------------------------------------------------------------------*/
void pcd8544_clearRestOfLine(void)
{
	while (current_column != 0)
	{
		pcd8544_data(0);
	}
}
/*---------------------------------------------------------------------------*/
void pcd8544_bitmap(uint8_t bdata[], uint8_t rows, uint8_t columns)
{
	uint8_t row, column, i;
	uint8_t toprow = current_row;
	uint8_t startcolumn = current_column;
	for (row = 0, i = 0; row < rows; row++) 
	{
		pcd8544_gotoRc(row+toprow, startcolumn);
		for (column = 0; column < columns; column++) 
		{
			pcd8544_data(pgm_read_byte(&bdata[i++]));
		}
	}
}
/*---------------------------------------------------------------------------*/
void pcd8544_print(const char* message)
{
	while(*message)
	{
		pcd8544_write(*message++);
	}
}
/*---------------------------------------------------------------------------*/