#define ADDR_SLAVE1		0x01
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
	
	uint16_t Length_Data_Slave1 = 1;
	uint8_t Data_Slave1;
	DDRC |= (1 << PORTC0);
	PORTC &= ~(1 << PORTC0);
	
	while(1){
		Modbus_Rec(ADDR_SLAVE1, &Data_Slave1,  Length_Data_Slave1);
		PORTC &= ~(1 << PORTC0);
		_delay_ms(100);
		RS485_EN_Rec();
		Lcd_Set_Cursor(10, 0);
		Lcd_Msg("Rec");
		Lcd_Set_Cursor(10, 1);
		Lcd_Value((float)Data_Slave1);
		if(Data_Slave1 == 0x01 || Data_Slave1 == 0x03 || Data_Slave1 == 0x05){
			PORTC |= (1 << PORTC0);
		}
	}
}