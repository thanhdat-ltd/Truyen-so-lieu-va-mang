#ifndef LCD_LIB_H_
#define LCD_LIB_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

#define LCD_DDR_DATA     DDRD
#define LCD_DDR_CONT	 DDRB
#define LCD_PORT_DATA    PORTD
#define LCD_PORT_CONT	 PORTB
#define RS          0
#define RW          1
#define E           2
// Mode 4bit
#define LCD_DATA_0	4
#define LCD_DATA_1	5
#define LCD_DATA_2	6
#define LCD_DATA_3	7

#define sbi(reg, bit)	reg |= (1 << bit)
#define cbi(reg, bit)	reg &= ~(1 << bit)

void Lcd_Enable();
void Lcd_Send_Nibble(uint8_t Data);
void Lcd_Send_Byte(uint8_t Data, uint8_t isData);
void Lcd_Clear();
void Lcd_Char(char ch);

void Lcd_Init();
void Lcd_Set_Cursor(uint8_t Col, uint8_t Row);
void Lcd_Msg(const char *Msg);
void Lcd_Value(float Data);

#endif /* LCD_LIB_H_ */