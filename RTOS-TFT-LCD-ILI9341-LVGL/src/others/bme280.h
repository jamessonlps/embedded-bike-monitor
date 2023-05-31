/*
 * bme280.h
 *
 * Created: 19/06/2022 10:27:44
 *  Author: James
 */

#ifndef BME280_H_
#define BME280_H_

// Uncomment the following line to enable software I2C
// You will need to have the SoftwareWire library installed
//#include <SoftwareWire.h> //SoftwareWire by Testato. Installed from library manager.

#define I2C_MODE 0
#define SPI_MODE 1

#define NO_WIRE 0
#define HARD_WIRE 1
#define SOFT_WIRE 2

#define MODE_SLEEP 0b00
#define MODE_FORCED 0b01
#define MODE_NORMAL 0b11

#define TWIHS_MCU6050_ID ID_TWIHS0
#define TWIHS_MCU6050 TWIHS0

/**************************************************************************/
#define BME280_ADDRESS (0x77) // Primary I2C Address
/**************************************************************************/
/*!
    @brief  alternate I2C address
*/
/**************************************************************************/
#define BME280_ADDRESS_ALTERNATE (0x76) // Alternate Address
/*=========================================================================*/

// Register names:
#define BME280_DIG_T1_LSB_REG 0x88
#define BME280_DIG_T1_MSB_REG 0x89
#define BME280_DIG_T2_LSB_REG 0x8A
#define BME280_DIG_T2_MSB_REG 0x8B
#define BME280_DIG_T3_LSB_REG 0x8C
#define BME280_DIG_T3_MSB_REG 0x8D
#define BME280_DIG_P1_LSB_REG 0x8E
#define BME280_DIG_P1_MSB_REG 0x8F
#define BME280_DIG_P2_LSB_REG 0x90
#define BME280_DIG_P2_MSB_REG 0x91
#define BME280_DIG_P3_LSB_REG 0x92
#define BME280_DIG_P3_MSB_REG 0x93
#define BME280_DIG_P4_LSB_REG 0x94
#define BME280_DIG_P4_MSB_REG 0x95
#define BME280_DIG_P5_LSB_REG 0x96
#define BME280_DIG_P5_MSB_REG 0x97
#define BME280_DIG_P6_LSB_REG 0x98
#define BME280_DIG_P6_MSB_REG 0x99
#define BME280_DIG_P7_LSB_REG 0x9A
#define BME280_DIG_P7_MSB_REG 0x9B
#define BME280_DIG_P8_LSB_REG 0x9C
#define BME280_DIG_P8_MSB_REG 0x9D
#define BME280_DIG_P9_LSB_REG 0x9E
#define BME280_DIG_P9_MSB_REG 0x9F
#define BME280_DIG_H1_REG 0xA1
#define BME280_CHIP_ID_REG 0xD0 // Chip ID
#define BME280_RST_REG 0xE0     // Softreset Reg
#define BME280_DIG_H2_LSB_REG 0xE1
#define BME280_DIG_H2_MSB_REG 0xE2
#define BME280_DIG_H3_REG 0xE3
#define BME280_DIG_H4_MSB_REG 0xE4
#define BME280_DIG_H4_LSB_REG 0xE5
#define BME280_DIG_H5_MSB_REG 0xE6
#define BME280_DIG_H6_REG 0xE7
#define BME280_CTRL_HUMIDITY_REG 0xF2    // Ctrl Humidity Reg
#define BME280_STAT_REG 0xF3             // Status Reg
#define BME280_CTRL_MEAS_REG 0xF4        // Ctrl Measure Reg
#define BME280_CONFIG_REG 0xF5           // Configuration Reg
#define BME280_PRESSURE_MSB_REG 0xF7     // Pressure MSB
#define BME280_PRESSURE_LSB_REG 0xF8     // Pressure LSB
#define BME280_PRESSURE_XLSB_REG 0xF9    // Pressure XLSB
#define BME280_TEMPERATURE_MSB_REG 0xFA  // Temperature MSB
#define BME280_TEMPERATURE_LSB_REG 0xFB  // Temperature LSB
#define BME280_TEMPERATURE_XLSB_REG 0xFC // Temperature XLSB
#define BME280_HUMIDITY_MSB_REG 0xFD     // Humidity MSB
#define BME280_HUMIDITY_LSB_REG 0xFE     // Humidity LSB

void bme280_i2c_bus_init(void);
uint8_t bme280_i2c_read_reg(uint CHIP_ADDRESS, uint reg_address, char *value);
int8_t bme280_i2c_config_temp(void);
int8_t bme280_i2c_read_temp(uint *temp);
uint8_t bme280_validate_id(void);
int8_t bme280_i2c_read_compensation_T(ushort *temp, uint reg1, uint reg2);
int32_t BME280_compensate_T_int32(int32_t adc_T, ushort dig_T1, short dig_T2, short dig_T3);
int8_t bme280_i2c_read_press(uint *press);
int8_t bme280_i2c_read_compensation_P(ushort *press, uint reg1, uint reg2);
uint32_t BME280_compensate_P_int64(int32_t adc_P, ushort dig_P1, short dig_P2, short dig_P3, short dig_P4, short dig_P5, short dig_P6, short dig_P7, short dig_P8, short dig_P9);

#endif /* BME280_H_ */