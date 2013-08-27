![image](../m328p_example.png)

#m328p_example

This example is written to demonstrate the lcdMenu library. PCD8544 based GLCD is used as a LCD in this example. Code works perfectly on an Arduino board. But be careful with the voltage level shifting. PCD8544 requires 3v3 supply and control signals.

##Wiring

###Buttons

	Select button -> PC0 -> Analog 0
	Up button     -> PC1 -> Analog 1
	Back button   -> PC2 -> Analog 2
	Down button   -> PC3 -> Analog 3
	
**Note:** Atmega328p's internal pullups are used for the buttons.

##PCD8544 LCD

	GND -> GND
	VCC -> 3v3
	CE  -> GND
	RST -> PB0 -> Digital 8
	DC  -> PB1 -> Digital 9
	DIN -> PB2 -> Digital 10
	CLK -> PB3 -> Digital 11
