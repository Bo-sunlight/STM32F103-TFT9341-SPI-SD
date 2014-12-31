#include "stm32f10x.h"
#include "TFT_Driver.h"
#include "delay.h"
#include "usart.h"
#include "MMC_SD.h"
#include "spi.h"

GPIO_InitTypeDef GPIO_InitStructure;

//void Delayms(__IO uint32_t nCount);
int SDTest(void);
unsigned char Num[10]={0,1,2,3,4,5,6,7,8,9};

void Redraw_Mainmenu(void)
{
	TFT_Clear(GRAY0);
	TFT_DrawFont_GBK16(16,0,BLUE,GRAY0,"ȫ�����Ӽ���");
	TFT_DrawFont_GBK16(16,20,RED,GRAY0,"Һ�����Գ���");
	DisplayButtonDown(15,38,113,58); //x1,y1,x2,y2
	TFT_DrawFont_GBK16(16,40,YELLOW,GRAY0,"��ɫ������");
	DisplayButtonUp(15,68,113,88); //x1,y1,x2,y2
	TFT_DrawFont_GBK16(16,70,BLUE,GRAY0,"������ʾ����");
	DisplayButtonUp(15,98,113,118); //x1,y1,x2,y2
	TFT_DrawFont_GBK16(16,100,RED,GRAY0,"ͼƬ��ʾ����");

	TFT_DrawFont_GBK16(16,120,BLUE,GRAY0,"S1:Move.    ");
	TFT_DrawFont_GBK16(16,140,RED,GRAY0, "S2:Sellect  ");
	//delay_ms(1000);
	//delay_ms(1000);

	TFT_DrawFont_Num32(100,125,RED,GRAY0,Num[5]);
	delay_ms(1000);
	TFT_DrawFont_Num32(100,125,RED,GRAY0,Num[4]);
	delay_ms(1000);
	TFT_DrawFont_Num32(100,125,RED,GRAY0,Num[3]);
	delay_ms(1000);
	TFT_DrawFont_Num32(100,125,RED,GRAY0,Num[2]);
	delay_ms(1000);
	TFT_DrawFont_Num32(100,125,RED,GRAY0,Num[1]);
	delay_ms(1000);
	TFT_DrawFont_Num32(100,125,RED,GRAY0,Num[0]);	
}

void Num_Test(void)
{
	u8 i=0;
	TFT_Clear(GRAY0);
	TFT_DrawFont_GBK16(16,20,RED,GRAY0,"Num Test");
	delay_ms(1000);
	TFT_Clear(GRAY0);

	for(i=0;i<10;i++)
	{
	TFT_DrawFont_Num32((i%3)*40,32*(i/3)+30,RED,GRAY0,Num[i+1]);
	delay_ms(100);
	}
	delay_ms(1000);
	
}
//������ʾ����ȫ�����Ӽ����̳���Ϊרע����רҵ
void Font_Test(void)
{
	u8 x_offset;
#ifdef H_VIEW  //��������˺�����ʾ
	x_offset=40;
#else
	x_offset=0;
#endif
	TFT_Clear(GRAY0);
	TFT_DrawFont_GBK16(16,10,BLUE,GRAY0,  "   ������ʾ����   ");

	delay_ms(1000);
	TFT_Clear(WHITE);
	TFT_DrawFont_GBK16(x_offset,10,RED,WHITE,  "     ȫ�����Ӽ������޹�˾      ");
	TFT_DrawFont_GBK16(x_offset,30,RED,WHITE,  "         QDtech .,LTD         ");
	TFT_DrawFont_GBK24(x_offset,50,BLUE,WHITE, "           ��ӭ��            ");
	TFT_DrawFont_GBK16(x_offset,100,GREEN,WHITE,   "     ȫ�̼���֧��     ");	
	TFT_DrawFont_GBK16(x_offset,120,RED,YELLOW,   "http://qdtech.taobao.com");
	TFT_DrawFont_GBK16(x_offset,140,RED,YELLOW,   "E-Mail:QDtech2008@gmail.com");
	TFT_DrawFont_GBK16(x_offset,160,RED,YELLOW,   "��������Ⱥ:324828016");	
	TFT_DrawFont_GBK16(x_offset,180,BLUE,WHITE,   "Tel:15989313508 ");
	delay_ms(3000);	
	

}

void Color_Test(void)
{
	//u8 i=2;
	TFT_Clear(GRAY0);
	
	TFT_DrawFont_GBK16(20,10,BLUE,GRAY0,"Color Test");
	delay_ms(1000);

	//while(i--)
	//{
	  TFT_Clear(WHITE);
	  TFT_Clear(BLACK);
	  TFT_Clear(RED);
  	TFT_Clear(GREEN);
  	TFT_Clear(BLUE);
	//}		
}

//u16 ID=0;
u8 rdata = 255;
int main(void)
{
  //uint16_t a;
  /* System Clocks Configuration **********************************************/
  SystemInit();
  delay_init(8);//��ʱ��ʼ�� 
	uart_init(9600);
  while(1) 
  {
		TFT_Init();			
		TFT_Clear(BLACK);
		TFT_LED_SET;
		
		printf("Test SD\r\n");
		SDTest();
		rdata = PAin(3);
		printf("Get PA3 Data %d\r\n",rdata);
		PAout(3)=1;
		rdata = PAin(3);
		printf("Get PA3 After set 1 Data %d\r\n",rdata);
		PAout(3)=0;
		rdata = PAin(3);
		printf("Get PA3 After reset 0 Data %d\r\n",rdata);
		TFT_Clear(BLUE);  
		//delay_ms(1000);
		delay_ms(1000);
		//TFT_Clear(BLACK); 
		TFT_Clear(WHITE);	

		Redraw_Mainmenu();//�򵥲˵�����
		Color_Test();//��ˢ������
		Num_Test();//�����������ʾ
		Font_Test();//��Ӣ�Ĳ���  
			
		TFT_Clear(BLACK);  
		//delay_ms(1000);
		delay_ms(1000);
		TFT_Clear(BLACK); 
		//TFT_Clear(WHITE);		
		TFT_DrawFont_GBK16(10,50,BLUE,GRAY0,"���Գɹ�.");
		delay_ms(1000);
  }
 
}

u8 buf[512];//SD�����ݻ�����
int SDTest(void)
{	
	u32 sd_size;
	u8 t=0;					    
//  	Stm32_Clock_Init(9);//ϵͳʱ������
//	delay_init(72);		//��ʱ��ʼ��
//	uart_init(72,9600); //����1��ʼ��  	  
//	LCD_Init();			//��ʼ��Һ�� 
//	LED_Init();         //LED��ʼ��		  													    
//					   
// 	POINT_COLOR=RED;//��������Ϊ��ɫ	   
//	LCD_ShowString(60,50,"Mini STM32");	
//	LCD_ShowString(60,70,"SD Card TEST");	
//	LCD_ShowString(60,90,"ATOM@ALIENTEK");
//	LCD_ShowString(60,110,"2011/1/1");
	u8 retry = 3;	
	while(SD_Init()!=0 && retry-->0) //��ⲻ��SD��
	{
		printf("SD Card Failed!\r\n");
		delay_ms(500);
		printf("Please Check!      \r\n");
		delay_ms(500);
//		LED0=!LED0;//DS0��˸
	}
	if(retry == 255)return 1;
	//���SD���ɹ� 											    
	printf("SD Card Checked OK \r\n");
	printf("SD Card Size:    Mb\r\n");
	sd_size=SD_GetCapacity();	
	printf("%i",sd_size);
	//printf(itoa(sd_size));//��ʾSD������
	while(1)
	{
		if(t==30)//ÿ6s��ִ��һ��
		{
			if(SD_ReadSingleBlock(0,buf)==0)//��ȡMBR����
			{	
				printf("USART1 Sending Data...");
				printf("SECTOR 0 DATA:\n");
				for(sd_size=0;sd_size<512;sd_size++)printf("%x ",buf[sd_size]);//��ӡMBR��������    	   
				printf("\nDATA ENDED\n");
				printf("USART1 Send Data Over!");
			}
			t=0;
		}   
		t++;
		delay_ms(200);
		//LED0=!LED0;
	}
}





