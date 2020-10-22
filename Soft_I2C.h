#include "stm32f10x.h"
#include "stm32f10x_gpio.h"

#define SCL_Pin				GPIO_Pin_6
#define SDA_Pin				GPIO_Pin_7
#define I2C_Port 			GPIOB

#define SCL_0					GPIO_ResetBits(GPIOB, GPIO_Pin_6)
#define SCL_1					GPIO_SetBits(GPIOB, GPIO_Pin_6)
#define SDA_0					GPIO_ResetBits(GPIOB, GPIO_Pin_7)
#define SDA_1					GPIO_SetBits(GPIOB, GPIO_Pin_7)
#define SDA_VAL				GPIOB->IDR & GPIO_Pin_7

#define Transmit 			0x00
#define Receive 			0x01

void Soft_I2C_Init(void);
void Soft_I2C_Start(void);
void Soft_I2C_Stop(void);
void Soft_I2C_SendData(uint8_t Data);
uint8_t Soft_I2C_ReceiveData(void);
void Soft_I2C_MakeACK(void);
void Soft_I2C_MakeNACK(void);
uint8_t Soft_I2C_WaitACK(void);
void Soft_I2C_SendAddress(uint8_t Address, uint8_t Direction);
void I2C_Write(uint8_t Address, uint8_t Data);
uint8_t I2C_Read(uint8_t Address);

