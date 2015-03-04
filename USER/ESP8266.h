#ifndef __ESP8266_DRIVER_H
#define __ESP8266_DRIVER_H
#include "stm32f10x.h"

#define RX_BUFFER_SIZE 2048
//extern u8 ESP8266_RX_BUF[RX_BUFFER_SIZE];     //���ջ���,��255���ֽ�.ĩ�ֽ�Ϊ���з� 
//extern u8 ESP8266_RX_STA;         //����״̬���	

static volatile u16 rx_buffer_head;
static volatile u16 rx_buffer_tail;

static volatile uint8_t rx_buffer[RX_BUFFER_SIZE];

void wifi_init(u32 bound);
int esp_write(u8 *str);
int read(void);
int peek(void);
int available(void);

#endif
