#include "Modbus_RS485_Lib.h"

void Uart_Init(uint16_t Baud){
	uint16_t MyUBRR =  (F_CPU / (16 * Baud)) - 1;
	UBRR0H = (uint8_t)(MyUBRR >> 8);
	UBRR0L = (uint8_t)(MyUBRR);
	
	UCSR0B = (1 << TXEN0) | (1 << RXEN0);
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}
void Uart_TransByte(uint8_t Data){
	while(!(UCSR0A & (1 << UDRE0)));
	UDR0 = Data;
}
uint8_t Uart_RecByte(void){
	while(!(UCSR0A & (1 << RXC0)));
	return UDR0;
}
void Uart_TransArray(uint8_t *Data, uint16_t Length_Data){
	for(uint16_t i = 0; i < Length_Data; i ++){
		Uart_TransByte(Data[i]);
	}
}
void Uart_RecArray(uint8_t *Data, uint16_t Length_Data){
	for(uint16_t i = 0; i < Length_Data; i ++){
		Data[i] = Uart_RecByte();
	}
}
void Uart_TransAddr(uint8_t Addr){
	Uart_TransByte(Addr);
}
uint8_t Uart_RecAddr(){
	uint8_t Addr_Temp = Uart_RecByte();
	return Addr_Temp;
}

void RS485_Init(){
	RS485_DDR |= (1 << RS485_DE_PIN);
	RS485_PORT &= ~(1 << RS485_DE_PIN);
}
void RS485_EN_Trans(){
	RS485_PORT |= (1 << RS485_DE_PIN);
	_delay_ms(10);
}
void RS485_EN_Rec(){
	RS485_PORT &= ~(1 << RS485_DE_PIN);
	_delay_ms(10);
}
uint16_t Cal_CRC_16(uint8_t *Frame, uint16_t Length_Frame){
	uint16_t Crc_16 = 0xFFFF;
	for(uint16_t i = 0; i < Length_Frame; i ++){
		Crc_16 ^= Frame[i];
		for(uint8_t j = 0; j < 8; j ++){
			if(Crc_16 & 0x0001) Crc_16 = (Crc_16 >> 1) ^ 0xA001;
			else Crc_16 >>= 1;
		}
	}
	return Crc_16;
}
uint8_t Check_CRC_16(uint8_t *Frame, uint16_t Length_Frame){
	if(Length_Frame < 2) return 0;
	uint16_t Cal_CRC16 = Cal_CRC_16(Frame, Length_Frame - 2);
	uint16_t Rec_CRC_16 = (Frame[Length_Frame - 1] << 8) | Frame[Length_Frame - 2];
	
	return (Cal_CRC16 == Rec_CRC_16);
}
void Modbus_Trans(uint8_t Addr, uint8_t *Data, uint16_t Length_Data){
	RS485_EN_Trans();
	uint8_t Frame[SIZE_OF_BUF];
	uint16_t Length_Frame = 0;
	Frame[Length_Frame ++] = Addr;
	for(uint16_t i = 0; i < Length_Data; i ++){
		Frame[Length_Frame ++] = Data[i];
	}
	uint16_t CRC_16 = Cal_CRC_16(Frame, Length_Frame);
	Frame[Length_Frame ++] = (uint8_t) CRC_16;       // Low Byte tr??c
	Frame[Length_Frame ++] = (uint8_t) (CRC_16 >> 8); // High Byte sau
	Uart_TransArray(Frame, Length_Frame);
}
void Modbus_Rec(uint8_t Addr, uint8_t *Data, uint16_t Length_Data){
	RS485_EN_Rec();
	uint8_t Frame[SIZE_OF_BUF];
	uint16_t Length_Frame = Length_Data + 3;
	
	Uart_RecArray(Frame, Length_Frame);
	if ((Frame[0] == Addr) && (Check_CRC_16(Frame, Length_Frame))) {
		for(uint16_t i = 0; i < Length_Frame - 3; i ++){
			Data[i] = Frame[i + 1];
		}
		return;
		} else{
		*Data = DATA_ERROR;
		return;
	}
}