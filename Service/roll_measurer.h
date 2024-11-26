#ifndef __IMU_H__
#define __IMU_H__
#include "stm32f10x.h"

#define ADXL_POWER_CTL 0x2D
#define ADXL_POWER_CTL_MEASURE 1<<3
#define ADXL_POWER_CTL_DEFAULT 0
// Shouldn't be needed for now since default is 100hz
#define ADXL_BW_RATE 0x2C
#define ADXL_BW_RATE_RATE 0b1111
#define ADXL_DATA_FORMAT 0x31
#define ADXL_DATA_FORMAT_JUSTIFY 1<<2
#define ADXL_DATA_FORMAT_FULL_RES 1<<3
#define ADXL_DATA_FORMAT_RANGE_0 1
#define ADXL_DATA_FORMAT_RANGE_1 1<<1
#define ADXL_DATA_FORMAT_RANGE 0b11
#define ADXL_DATA_FORMAT_DEFAULT 0
#define ADXL_DATAX0 0x32
#define ADXL_DATAX1 0x33

/**
 * @brief 'constructor', initialise le service roll_measurer
 * @param SPIO_TypeDef * spi : module spi utilisé par le service roll_measurer
 */
void roll_measurer_init(SPI_TypeDef * spi);

/**
 * @brief récupère l'angle de roulie fournis par le service
 * @pre le service roll_measurer doit avoir été initialisé avec la fonction @ref roll_measurer_init()
 * @return un entier représentant l'angle en degrés
 */
uint16_t roll_measurer_get_angle();

#endif