#include "roll_measurer.h"
#include "MySPI.h"
#include <stdint.h>
#include <math.h>

SPI_TypeDef * selected_spi;

#define PI 3.14159
#define IMU_MAX_VALUE 1740

void adxl_write(char addr, char data) {
	MySPI_Clear_NSS();
	MySPI_Send((char)addr);
	MySPI_Send((char)data);
	MySPI_Set_NSS();
}

char adxl_read(char addr) {
	MySPI_Clear_NSS();
	MySPI_Send((char)1<<7|addr);
	//MySPI_Send(1<<7|0);
	char result = MySPI_Read();
	MySPI_Set_NSS();
	return result;
}

void adxl_multi_read(char addr, char* buffer, int n) {
	MySPI_Clear_NSS();
	MySPI_Send((char)0b11<<6|addr);
	int i;
	for (i=0; i<n; i++) {
		buffer[i] = MySPI_Read();
	}
	MySPI_Set_NSS();
}

void roll_measurer_init(SPI_TypeDef * spi) {
	selected_spi = spi;
	MySPI_Init(spi);
	
	// Set power ctl measure to 1
	adxl_write(ADXL_POWER_CTL, ADXL_POWER_CTL_DEFAULT | ADXL_POWER_CTL_MEASURE);

	// Set data format to full res and justify, 16g
	adxl_write(
		ADXL_DATA_FORMAT,
		ADXL_DATA_FORMAT_DEFAULT
		| ADXL_DATA_FORMAT_FULL_RES
		| ADXL_DATA_FORMAT_JUSTIFY
		| ADXL_DATA_FORMAT_RANGE
	);
}

uint16_t roll_measurer_get_angle() {
	char buffer[6];
	adxl_multi_read(ADXL_DATAX0, buffer, 6);
	char z0 = buffer[4];
	char z1 = buffer[5];
	
	int16_t z_16 = (int16_t)((z1<<8) | z0);
	int z = (int)z_16;
	// Z ranges from 1728 at 0 degrees to 0 at 90 degrees
	double normalized_value = (double)z / IMU_MAX_VALUE;
	double angle_radians = acos(normalized_value);
	uint16_t angle_degrees = (uint16_t)(angle_radians * 180 / PI);
	
	return angle_degrees;
}
