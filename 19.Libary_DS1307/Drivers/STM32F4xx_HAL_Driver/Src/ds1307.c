
#include <stdio.h>
#include "DS1307.h"
#define DS1307_ADRESS (0x68<<1)
#define DS1307_REG_TIME (0x00)
DS1307_t DS1307;
 uint8_t RTC_BCD2DEC(uint8_t data) {
	 return (data >> 4)*10 + ( data&0x0f);
 }

 uint8_t RTC_DEC2BCD(uint8_t data) {
	 return (data/10)<<4|(data%10);
 }


 void I2C_WriteBuffer(I2C_HandleTypeDef hi2c1, uint8_t DEV_ADDR, uint8_t sizebuf) {
 	 while(HAL_I2C_Master_Transmit(&hi2c1, (uint16_t)DEV_ADDR, (uint8_t*) &DS1307.I2C_Buffer, (uint16_t)sizebuf, (uint32_t)1000)) {
 		 if(HAL_I2C_GetError(&hi2c1) != HAL_I2C_ERROR_AF) {
 			 printf("Write Buffer Error\r\n");
 		 }
 	 }
  }


 void I2C_ReadBuffer(I2C_HandleTypeDef hi2c1, uint8_t DEV_ADDR, uint8_t sizebuf) {
	 while(HAL_I2C_Master_Receive(&hi2c1, (uint16_t)DEV_ADDR, (uint8_t*)&DS1307.I2C_Buffer, (uint16_t)sizebuf, (uint32_t)1000)) {
	 		 if(HAL_I2C_GetError(&hi2c1) != HAL_I2C_ERROR_AF) {
	 			 printf("Read Buffer Error\r\n");
	 		 }
	 	 }
 }


 void RTC_GetTime(I2C_HandleTypeDef hi2c1) {
	 	 DS1307.I2C_Buffer[0] = 0x00;
	 	 I2C_WriteBuffer(hi2c1, (uint16_t)DS1307_ADRESS, 1);
	 	 while(HAL_I2C_GetState(&hi2c1) != HAL_I2C_STATE_READY) {

	 	 }
		 I2C_ReadBuffer(hi2c1, (uint16_t)DS1307_ADRESS, 8);

		 DS1307.day = RTC_BCD2DEC(DS1307.I2C_Buffer[3]);
		 DS1307.date = RTC_BCD2DEC(DS1307.I2C_Buffer[4]);
		 DS1307.month = RTC_BCD2DEC(DS1307.I2C_Buffer[5]);
		 DS1307.year = RTC_BCD2DEC(DS1307.I2C_Buffer[6]);

		 DS1307.sec = RTC_BCD2DEC(DS1307.I2C_Buffer[0]);
		 DS1307.minute = RTC_BCD2DEC(DS1307.I2C_Buffer[1]);
		 DS1307.hour = RTC_BCD2DEC(DS1307.I2C_Buffer[2]);

 }

 void RTC_SetTime(uint8_t hour, uint8_t minute, uint8_t sec, uint8_t date, uint8_t month, uint8_t year, int day) {
	 DS1307.I2C_Buffer[0] = 0x00;
	 DS1307.I2C_Buffer[1] = RTC_DEC2BCD(sec);
	 DS1307.I2C_Buffer[2] = RTC_DEC2BCD(minute);
	 DS1307.I2C_Buffer[3] = RTC_DEC2BCD(hour);
	 DS1307.I2C_Buffer[4] = RTC_DEC2BCD(day);
	 DS1307.I2C_Buffer[5] = RTC_DEC2BCD(date);
	 DS1307.I2C_Buffer[6] = RTC_DEC2BCD(month);
	 DS1307.I2C_Buffer[7] = RTC_DEC2BCD(year);
	 I2C_WriteBuffer(hi2c1, (uint16_t)DS1307_ADRESS, 8);
	 HAL_Delay(500);
 }
