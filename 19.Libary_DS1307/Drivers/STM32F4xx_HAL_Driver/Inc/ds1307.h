
#ifndef I2C_DS1307_H
#define I2C_DS1307_H
#include "stm32f4xx_hal.h"

extern I2C_HandleTypeDef hi2c1;

typedef struct {
	uint8_t sec;
	uint8_t minute;
	uint8_t hour;
	uint8_t day;
	uint8_t date;
	uint8_t month;
	uint8_t year;

	uint8_t I2C_Buffer[8];
}DS1307_t;


extern DS1307_t DS1307;

void RTC_GetTime(I2C_HandleTypeDef hi2c1);
void RTC_SetTime(uint8_t hour, uint8_t minute, uint8_t sec, uint8_t date, uint8_t month, uint8_t year, int day);



#endif
