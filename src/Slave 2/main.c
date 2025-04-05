#define ADDR_SLAVE2		0x02
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "Modbus_RS485_Lib.h"
#include "LCD_Lib.h"

int main(){
	Uart_Init(BAUD);
	RS485_Init();
	Lcd_Init();
	
	Lcd_Clear();
	Lcd_Set_Cursor(0, 0);
	Lcd_Msg("Slave1: ");
	Lcd_Set_Cursor(0, 1);
	Lcd_Msg("Data: ");
	
	uint16_t Length_Data_Slave2 = 1;
	uint8_t Data_Slave2;
	
	DDRC |= (1 << PORTC0);
	PORTC &= ~(1 << PORTC0);
	
	while(1){
		Modbus_Rec(ADDR_SLAVE2, &Data_Slave2,  Length_Data_Slave2);
		PORTC &= ~(1 << PORTC0);
		_delay_ms(100);
		RS485_EN_Rec();
		Lcd_Set_Cursor(10, 0);
		Lcd_Msg("Rec");
		Lcd_Set_Cursor(10, 1);
		Lcd_Value((float)Data_Slave2);
		if(Data_Slave2 == 0x02 || Data_Slave2 == 0x04 || Data_Slave2 == 0x06){
			PORTC |= (1 << PORTC0);
		}
	}
}