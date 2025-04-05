#define MASTER	0x00
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "Modbus_RS485_Lib.h"
#include "LCD_Lib.h"

#define ADDR_SLAVE1	0x01
#define ADDR_SLAVE2	0x02
#define ADDR_SLAVE3	0x03

int main(){
	Uart_Init(BAUD);
	RS485_Init();
	Lcd_Init();
	
	Lcd_Clear();
	Lcd_Set_Cursor(0, 0);
	Lcd_Msg("Master: ");
	Lcd_Set_Cursor(0, 1);
	Lcd_Msg("Data: ");
	
	//uint16_t Length_Data_Slave1 = 3;
	uint8_t Data_Slave1[] = {0x01, 0x03, 0x05};
	
	//uint16_t Length_Data_Slave2 = 3;
	uint8_t Data_Slave2[] = {0x02, 0x04, 0x06};
		
	uint8_t Data_Slave3[] = {0x01, 0x03, 0x05};
	
	while(1){
		// Truyen Slave 1 tr??c
		for(uint16_t i = 0; i < 3; i ++){
			Modbus_Trans(ADDR_SLAVE1, &Data_Slave1[i], 1);
			_delay_ms(100);
			RS485_EN_Rec();
			Lcd_Set_Cursor(10, 0);
			Lcd_Msg("Trans");
			Lcd_Set_Cursor(10, 1);
			Lcd_Value((float)Data_Slave1[i]);
		}
		_delay_ms(1000);
		for(uint16_t i = 0; i < 3; i ++){
			Modbus_Trans(ADDR_SLAVE2, &Data_Slave2[i], 1);
			_delay_ms(100);
			RS485_EN_Rec();
			Lcd_Set_Cursor(10, 0);
			Lcd_Msg("Trans");
			Lcd_Set_Cursor(10, 1);
			Lcd_Value((float)Data_Slave2[i]);
		}
		_delay_ms(1000);
		for(uint16_t i = 0; i < 3; i ++){
			Modbus_Trans(ADDR_SLAVE3, &Data_Slave3[i], 1);
			_delay_ms(100);
			RS485_EN_Rec();
			Lcd_Set_Cursor(10, 0);
			Lcd_Msg("Trans");
			Lcd_Set_Cursor(10, 1);
			Lcd_Value((float)Data_Slave3[i]);
		}
		_delay_ms(1000);
	}
}