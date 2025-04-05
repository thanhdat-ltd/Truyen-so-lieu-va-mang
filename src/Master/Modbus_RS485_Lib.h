#ifndef MODBUS_RS485_LIB_H_
#define MODBUS_RS485_LIB_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

/* Cac dinh nghia thong so cho protocol*/
#define BAUD				9600
#define SIZE_OF_BUF			256
#define MAX_NUMBER_SLAVE	256
#define TIMEOUT_MIN_MS		3	// (ms)
#define TIMEFRAME_MAX_MS	1	// (ms)
#define DATA_ERROR			0xFF

/* Cac dinh nghia cua DDR, PORT, PIN*/
// RS485
#define RS485_DDR			DDRD
#define RS485_PORT			PORTD
#define RS485_PIN			PIND
#define RS485_DE_PIN	    2

void Uart_Init(uint16_t Baud);
void RS485_Init();
void RS485_EN_Trans();
void RS485_EN_Rec();
void Modbus_Trans(uint8_t Addr, uint8_t *Data, uint16_t Length_Data);
void Modbus_Rec(uint8_t Addr, uint8_t *Data, uint16_t Length_Data);


#endif /* MODBUS_RS485_LIB_H_ */