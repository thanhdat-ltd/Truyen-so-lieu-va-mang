#include "LCD_Lib.h"

void Lcd_Enable() {
	sbi(LCD_PORT_CONT, E);
	_delay_us(1);
	cbi(LCD_PORT_CONT, E);
	_delay_us(100);
}

void Lcd_Send_Nibble(uint8_t Data) {
	LCD_PORT_DATA = (LCD_PORT_DATA & 0x0F) | (Data << LCD_DATA_0);
	Lcd_Enable();
}

void Lcd_Send_Byte(uint8_t Data, uint8_t isData) {
	if (isData) {
		sbi(LCD_PORT_CONT, RS);
		} else {
		cbi(LCD_PORT_CONT, RS);
	}
	cbi(LCD_PORT_CONT, RW);
	
	Lcd_Send_Nibble(Data >> 4);  // G?i 4 bit cao
	Lcd_Send_Nibble(Data & 0x0F);  // G?i 4 bit th?p
}

void Lcd_Clear() {
	Lcd_Send_Byte(0x01, 0);
	_delay_ms(2);
}

void Lcd_Init() {
	LCD_DDR_DATA |= (0xF0);  // Ch? c?u hình 4 bit cao làm output
	LCD_DDR_CONT |= (1 << RS) | (1 << RW) | (1 << E);

	_delay_ms(20);
	Lcd_Send_Nibble(0x03);
	_delay_ms(5);
	Lcd_Send_Nibble(0x03);
	_delay_us(150);
	Lcd_Send_Nibble(0x03);
	Lcd_Send_Nibble(0x02);
	
	Lcd_Send_Byte(0x28, 0);  // Ch? ?? 4-bit, 2 dòng, font 5x8
	Lcd_Send_Byte(0x0C, 0);  // B?t màn hình, t?t con tr?
	Lcd_Send_Byte(0x06, 0);  // T?ng ??a ch?, không d?ch màn hình
	Lcd_Clear();
}

void Lcd_Set_Cursor(uint8_t Col, uint8_t Row) {
	uint8_t pos = (Row == 0) ? 0x80 : 0xC0;
	pos += Col;
	Lcd_Send_Byte(pos, 0);
}

void Lcd_Msg(const char *Msg) {
	while (*Msg) {
		Lcd_Send_Byte(*Msg++, 1);
	}
}

void Lcd_Value(float Data) {
	char buffer[10];
	snprintf(buffer, sizeof(buffer), "%.2f", Data);
	Lcd_Msg(buffer);
}
void Lcd_Char(char ch){
	
}