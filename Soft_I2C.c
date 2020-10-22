#include "Soft_I2C.h"
#include "delay.h"


void Soft_I2C_Init (void)
{
	RCC_APB2PeriphClockCmd (RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO_InitTypeDef Soft_I2C;
	Soft_I2C.GPIO_Mode = GPIO_Mode_Out_OD;
	Soft_I2C.GPIO_Pin = SCL_Pin | SDA_Pin;
	Soft_I2C.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init (GPIOB, &Soft_I2C);
	
	SDA_1;
	SCL_1;
	
}

void Soft_I2C_Start (void)
{
	SDA_1;
	delay_ms(4);
	SCL_1;
	delay_us(4);
	SDA_0;
	delay_us(4);
	SCL_0;
	delay_us(4);
}

void Soft_I2C_Stop (void)
{
	SDA_0;
	delay_us(4);
	SCL_1;
	delay_us(4);
	SDA_1;
	delay_us(4);
}

void Soft_I2C_SendData (uint8_t Data)
{
	uint8_t i;
	
	for(i = 0; i < 8 ; i++) {
		if (Data & 0x80) {
			SDA_1;
		}
		else {
		SDA_0;
		}
		
		delay_us(4);
		Data <<= 1;
		delay_us(4);
		SCL_1;
		delay_us(4);
		SCL_0;
		delay_us(4);
	}
	
}

uint8_t Soft_I2C_ReceiveData (void)
{
	uint8_t i;
	uint8_t Received_Data = 0;
	
	SDA_1;
	delay_us(4);
	
	for (i = 0; i < 8; i++) {
		Received_Data <<= 1;
		
		SCL_1;
		delay_us(4);
		
		if (SDA_VAL) {
			Received_Data |= 0x01;
		}
		
		delay_us(4);
		SCL_0;
		delay_us(4);
	}
	
	return Received_Data;
	
}

void Soft_I2C_MakeACK (void)
{
	SCL_0;
	delay_us(4);
	SDA_0;
	delay_us(4);
	SCL_1;
	delay_us(4);
	SCL_0;
	delay_us(4);
}

void Soft_I2C_MakeNACK (void)
{
	SCL_0;
	delay_us(4);
	SDA_1;
	delay_us(4);
	SCL_1;
	delay_us(4);
	SCL_0;
	delay_us(4);
}

uint8_t Soft_I2C_WaitACK (void)
{
	SCL_1;
	delay_us(4);
	
	if (SDA_VAL) {
		SCL_0;
		delay_us(4);
		return 0;
	}
	
	else {
		SCL_0;
		delay_us(4);
		return 1;
	}
}

void Soft_I2C_SendAddress (uint8_t Address, uint8_t Direction)
{
	if (Direction) {
		Soft_I2C_SendData (Address << 1 | Direction);
	}
	else {
		Soft_I2C_SendData (Address << 1 | Direction);
	}
}

void I2C_Write (uint8_t Address, uint8_t Data)
{
	
	Soft_I2C_Start ();
	Soft_I2C_SendAddress (Address, Transmit);
	while (!Soft_I2C_WaitACK ());
	Soft_I2C_SendData (Data);
	while (!Soft_I2C_WaitACK ());
	Soft_I2C_Stop ();
	
}

uint8_t I2C_Read (uint8_t Address)
{
	uint8_t Received_Data;
	
	Soft_I2C_Start ();
	Soft_I2C_SendAddress (Address, Receive);
	while (!Soft_I2C_WaitACK ());
	Received_Data = Soft_I2C_ReceiveData ();
	Soft_I2C_MakeNACK ();
	Soft_I2C_Stop ();
	
	return Received_Data;
	
}

