#define ADDR_SLAVE3     0x03
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
	
	uint16_t Length_Data_Slave3 = 1;
	uint8_t Data_Slave3;
	DDRC |= (1 << PORTC0);
	PORTC &= ~(1 << PORTC0);
	
	while(1){
		Modbus_Rec(ADDR_SLAVE3, &Data_Slave3, Length_Data_Slave3);
		_delay_ms(100);
		RS485_EN_Rec();
		Lcd_Set_Cursor(10, 0);
		Lcd_Msg("Rec");
		Lcd_Set_Cursor(10, 1);
		char temp[2] = {Data_Slave3, '\0'};
		Lcd_Msg(temp);
		
		// So sánh v?i ký t?, thay ??i tùy m?c ?ích
		if(Data_Slave3 == 'G' || Data_Slave3 == 'H' || Data_Slave3 == 'I'){
			PORTC |= (1 << PORTC0);
			} else {
			PORTC &= ~(1 << PORTC0);
		}
	}
}
