#define ADDR_SLAVE3     0x03
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
	Lcd_Msg("Slave3: ");
	Lcd_Set_Cursor(0, 1);
	Lcd_Msg("Data: ");

	uint16_t Length_Data_Slave3 = 1;
	uint8_t Data_Slave3;
	char buffer[17] = "";
	uint8_t no_data_counter = 0; // ??m th?i gian không nh?n ???c d? li?u

	DDRC |= (1 << PORTC0);
	PORTC &= ~(1 << PORTC0);

	while(1){
		if(Modbus_Rec(ADDR_SLAVE3, &Data_Slave3, Length_Data_Slave3)){
			no_data_counter = 0;  // Reset n?u có d? li?u

			// Ký t? h?p l?
			if(Data_Slave3 >= 32 && Data_Slave3 <= 126){
				uint8_t len = strlen(buffer);
				if(len < 16){
					buffer[len] = Data_Slave3;
					buffer[len+1] = '\0';
				}
			}

			// Hien thi
			Lcd_Set_Cursor(10, 0);
			Lcd_Msg("Rec ");
			Lcd_Set_Cursor(0, 1);
			Lcd_Msg("Data:         ");
			Lcd_Set_Cursor(6, 1);
			Lcd_Msg(buffer);

			// LED control
			if(Data_Slave3 == 'H' || Data_Slave3 == 'e' || Data_Slave3 == 'l' || Data_Slave3 == 'o' || Data_Slave3 == 'S' || Data_Slave3 == 'a' || Data_Slave3 == 'v'){
				PORTC |= (1 << PORTC0);
				} else {
				PORTC &= ~(1 << PORTC0);
			}
			} else {
			no_data_counter++;  
			if(no_data_counter >= 10){  //timer cho lcd xoa man hinh
				no_data_counter = 10;   

				// Xóa buffer và LCD
				buffer[0] = '\0';
				Lcd_Set_Cursor(10, 0);
				Lcd_Msg("    ");
				Lcd_Set_Cursor(0, 1);
				Lcd_Msg("Data:           ");
			}
		}

		_delay_ms(100);  // m?i vòng l?p = 100ms
	}
}
