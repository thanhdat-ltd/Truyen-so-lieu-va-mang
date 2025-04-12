#define ADDR_SLAVE1     0x01
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <string.h>

#include "Modbus_RS485_Lib.h"
#include "LCD_Lib.h"

#define DATA_ERROR 0xFF

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
	char buffer[17] = "";
	uint8_t no_data_counter = 0; // đếm thời gian không nhận được dữ liệu

	DDRC |= (1 << PORTC0);
	PORTC &= ~(1 << PORTC0);

	while(1){
		if(Modbus_Rec(ADDR_SLAVE1, &Data_Slave1, Length_Data_Slave1)){
			no_data_counter = 0;  // Reset nếu có dữ liệu

			// Ký tự hợp lệ
			if(Data_Slave1 >= 32 && Data_Slave1 <= 126){
				uint8_t len = strlen(buffer);
				if(len < 16){
					buffer[len] = Data_Slave1;
					buffer[len+1] = '\0';
				}
			}

			// Hiển thị
			Lcd_Set_Cursor(10, 0);
			Lcd_Msg("Rec ");
			Lcd_Set_Cursor(0, 1);
			Lcd_Msg("Data:         ");
			Lcd_Set_Cursor(6, 1);
			Lcd_Msg(buffer);

			// Điều khiển LED
			if(Data_Slave1 == 'H' || Data_Slave1 == 'e' || Data_Slave1 == 'l' || Data_Slave1 == 'o' || Data_Slave1 == 'S' || Data_Slave1 == 'a' || Data_Slave1 == 'v'){
				PORTC |= (1 << PORTC0);
				} else {
				PORTC &= ~(1 << PORTC0);
			}
			} else {
			no_data_counter++;  // tăng nếu không nhận được
			if(no_data_counter >= 10){  // tương đương ~3s
				no_data_counter = 10;   // giới hạn giá trị max

				// Xóa buffer và LCD
				buffer[0] = '\0';
				Lcd_Set_Cursor(10, 0);
				Lcd_Msg("    ");
				Lcd_Set_Cursor(0, 1);
				Lcd_Msg("Data:           ");
			}
		}

		_delay_ms(100);  // mỗi vòng lặp = 100ms
	}
}
