/*
 * bme280.c
 *
 * Created: 19/06/2022 10:27:58
 *  Author: James
 */

#include "asf.h"
#include "bme280.h"

void bme280_i2c_bus_init(void)
{
  twihs_options_t bno055_option;
  pmc_enable_periph_clk(TWIHS_MCU6050_ID);

  /* Configure the options of TWI driver */
  bno055_option.master_clk = sysclk_get_cpu_hz();
  bno055_option.speed = 10000;
  twihs_master_init(TWIHS_MCU6050, &bno055_option);
}

uint8_t bme280_i2c_read_reg(uint CHIP_ADDRESS, uint reg_address, char *value)
{
  uint i = 1;

  twihs_packet_t p_packet;
  p_packet.chip = CHIP_ADDRESS; // BME280_ADDRESS;
  p_packet.addr_length = 0;

  char data = reg_address; // BME280_CHIP_ID_REG;
  p_packet.buffer = &data;
  p_packet.length = 1;

  if (twihs_master_write(TWIHS_MCU6050, &p_packet) != TWIHS_SUCCESS)
    return 1;

  p_packet.addr_length = 0;
  p_packet.length = 1;
  p_packet.buffer = value;

  if (twihs_master_read(TWIHS_MCU6050, &p_packet) != TWIHS_SUCCESS)
    return 1;

  return 0;
}

int8_t bme280_i2c_config_temp(void)
{
  int32_t ierror = 0x00;

  twihs_packet_t p_packet;
  p_packet.chip = BME280_ADDRESS; // BME280_ADDRESS;
  p_packet.addr[0] = BME280_CTRL_MEAS_REG;
  p_packet.addr_length = 1;

  char data = 0b00100111; // BME280_CHIP_ID_REG;
  p_packet.buffer = &data;
  p_packet.length = 1;

  if (twihs_master_write(TWIHS_MCU6050, &p_packet) != TWIHS_SUCCESS)
    return 1;

  twihs_packet_t p_packet2;
  p_packet2.chip = BME280_ADDRESS; // BME280_ADDRESS;
  p_packet2.addr[0] = BME280_CTRL_HUMIDITY_REG;
  p_packet2.addr_length = 1;

  char data2 = 0b00000001; // BME280_CHIP_ID_REG;
  p_packet2.buffer = &data2;
  p_packet2.length = 1;

  if (twihs_master_write(TWIHS_MCU6050, &p_packet2) != TWIHS_SUCCESS)
  {
    return 1;
  }

  return 0;
}

int8_t bme280_i2c_read_temp(uint *temp)
{
  int32_t ierror = 0x00;
  char tmp[3];

  bme280_i2c_read_reg(BME280_ADDRESS, BME280_TEMPERATURE_MSB_REG, &tmp[2]);
  bme280_i2c_read_reg(BME280_ADDRESS, BME280_TEMPERATURE_MSB_REG, &tmp[2]);

  bme280_i2c_read_reg(BME280_ADDRESS, BME280_TEMPERATURE_LSB_REG, &tmp[1]);
  bme280_i2c_read_reg(BME280_ADDRESS, BME280_TEMPERATURE_LSB_REG, &tmp[1]);

  *temp = tmp[2] << 8 | tmp[1];
  return 0;
}

uint8_t bme280_validate_id(void)
{
  char id;
  bme280_i2c_read_reg(BME280_ADDRESS, BME280_CHIP_ID_REG, &id);
  if (bme280_i2c_read_reg(BME280_ADDRESS, BME280_CHIP_ID_REG, &id))
    return 1;
  if (id != 0x60)
    return 1;
  return 0;
}

int8_t bme280_i2c_read_compensation_T(ushort *temp, uint reg1, uint reg2)
{
  int32_t ierror = 0x00;
  char tmp[3];

  bme280_i2c_read_reg(BME280_ADDRESS, reg2, &tmp[2]);
  bme280_i2c_read_reg(BME280_ADDRESS, reg2, &tmp[2]);

  bme280_i2c_read_reg(BME280_ADDRESS, reg1, &tmp[1]);
  bme280_i2c_read_reg(BME280_ADDRESS, reg1, &tmp[1]);

  *temp = tmp[2] << 8 | tmp[1];
  return 0;
}

volatile int32_t t_fine;

int32_t BME280_compensate_T_int32(int32_t adc_T, ushort dig_T1, short dig_T2, short dig_T3)
{
  int32_t var1, var2, T;
  var1 = ((((adc_T >> 3) - ((int32_t)dig_T1 << 1))) * ((int32_t)dig_T2)) >> 11;
  var2 = (((((adc_T >> 4) - ((int32_t)dig_T1)) * ((adc_T >> 4) - ((int32_t)dig_T1))) >> 12) *
          ((int32_t)dig_T3)) >>
         14;
  t_fine = var1 + var2;
  T = (t_fine * 5 + 128) >> 8;
  return T;
}

/************************************************************************/
/* BME280 PRESS                                                         */
/************************************************************************/
int8_t bme280_i2c_read_press(uint *press)
{
  int32_t ierror = 0x00;
  char tmp[3];

  bme280_i2c_read_reg(BME280_ADDRESS, BME280_PRESSURE_MSB_REG, &tmp[2]);
  bme280_i2c_read_reg(BME280_ADDRESS, BME280_PRESSURE_MSB_REG, &tmp[2]);

  bme280_i2c_read_reg(BME280_ADDRESS, BME280_PRESSURE_LSB_REG, &tmp[1]);
  bme280_i2c_read_reg(BME280_ADDRESS, BME280_PRESSURE_LSB_REG, &tmp[1]);

  *press = tmp[2] << 8 | tmp[1];
  return 0;
}

int8_t bme280_i2c_read_compensation_P(ushort *press, uint reg1, uint reg2)
{

  int32_t ierror = 0x00;
  char tmp[3];

  bme280_i2c_read_reg(BME280_ADDRESS, reg2, &tmp[2]);
  bme280_i2c_read_reg(BME280_ADDRESS, reg2, &tmp[2]);

  bme280_i2c_read_reg(BME280_ADDRESS, reg1, &tmp[1]);
  bme280_i2c_read_reg(BME280_ADDRESS, reg1, &tmp[1]);

  *press = tmp[2] << 8 | tmp[1];
  return 0;
}

uint32_t BME280_compensate_P_int64(int32_t adc_P, ushort dig_P1, short dig_P2, short dig_P3, short dig_P4, short dig_P5, short dig_P6, short dig_P7, short dig_P8, short dig_P9)
{
  int64_t var1, var2, p;
  var1 = ((int64_t)t_fine) - 128000;
  var2 = var1 * var1 * (int64_t)dig_P6;
  var2 = var2 + ((var1 * (int64_t)dig_P5) << 17);
  var2 = var2 + (((int64_t)dig_P4) << 35);
  var1 = ((var1 * var1 * (int64_t)dig_P3) >> 8) + ((var1 * (int64_t)dig_P2) << 12);
  var1 = (((((int64_t)1) << 47) + var1)) * ((int64_t)dig_P1) >> 33;
  if (var1 == 0)
  {
    return 0; // avoid exception caused by division by zero
  }
  p = 1048576 - adc_P;
  p = (((p << 31) - var2) * 3125) / var1;
  var1 = (((int64_t)dig_P9) * (p >> 13) * (p >> 13)) >> 25;
  var2 = (((int64_t)dig_P8) * p) >> 19;
  p = ((p + var1 + var2) >> 8) + (((int64_t)dig_P7) << 4);
  return (uint32_t)p;
}