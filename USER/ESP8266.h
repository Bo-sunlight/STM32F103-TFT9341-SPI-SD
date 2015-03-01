#ifndef __ESP8266_DRIVER_H
#define __ESP8266_DRIVER_H
#include "stm32f10x.h"

extern u8 ESP8266_RX_BUF[255];     //���ջ���,��255���ֽ�.ĩ�ֽ�Ϊ���з� 
extern u8 ESP8266_RX_STA;         //����״̬���	

void wifi_init(u32 bound);
int esp_write(u8 *str);

#endif
