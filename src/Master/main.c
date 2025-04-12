#define MASTER  0x00
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "Modbus_RS485_Lib.h"
#include "LCD_Lib.h"

#define ADDR_SLAVE1    0x01
#define ADDR_SLAVE2    0x02
#define ADDR_SLAVE3    0x03

int main(){
	Uart_Init(BAUD);
	RS485_Init();
	Lcd_Init();
	
	Lcd_Clear();
	Lcd_Set_Cursor(0, 0);
	Lcd_Msg("Master: ");
	Lcd_Set_Cursor(0, 1);
	Lcd_Msg("Data: ");
	
	// Truy?n ký t? cho các slave
	uint8_t Data_Slave1[] = {'H', 'e', 'l','l','o','S','l','a','v','1'};
	uint8_t Data_Slave2[] = {'H', 'e', 'l','l','o','S','l','a','v','2'};
	uint8_t Data_Slave3[] = {'H', 'e', 'l','l','o','S','l','a','v','3'};
	
	while(1){
		// G?i cho Slave 1
		for(uint8_t i = 0; i < 10; i++){
			Modbus_Trans(ADDR_SLAVE1, &Data_Slave1[i], 1);
			_delay_ms(100);
			RS485_EN_Rec();
			Lcd_Set_Cursor(10, 0);
			Lcd_Msg("Trans");
			Lcd_Set_Cursor(10, 1);
			char temp[2] = {Data_Slave1[i], '\0'};
			Lcd_Msg(temp);
		}
		_delay_ms(1000);
		
		// G?i cho Slave 2
		for(uint8_t i = 0; i < 10; i++){
			Modbus_Trans(ADDR_SLAVE2, &Data_Slave2[i], 1);
			_delay_ms(100);
			RS485_EN_Rec();
			Lcd_Set_Cursor(10, 0);
			Lcd_Msg("Trans");
			Lcd_Set_Cursor(10, 1);
			char temp[2] = {Data_Slave2[i], '\0'};
			Lcd_Msg(temp);
		}
		_delay_ms(1000);
		
		// G?i cho Slave 3
		for(uint8_t i = 0; i < 10; i++){
			Modbus_Trans(ADDR_SLAVE3, &Data_Slave3[i], 1);
			_delay_ms(100);
			RS485_EN_Rec();
			Lcd_Set_Cursor(10, 0);
			Lcd_Msg("Trans");
			Lcd_Set_Cursor(10, 1);
			char temp[2] = {Data_Slave3[i], '\0'};
			Lcd_Msg(temp);
		}
		_delay_ms(1000);
	}
}
