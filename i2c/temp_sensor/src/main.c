/*
 * EC544: i2c interface with temperature sensor
 */

#include <zephyr.h>
#include <misc/printk.h>
#include <i2c.h>
#include <device.h>
#include <stdio.h>
#include <time.h>
//#include <adc.h>

//west build -b frdm_k64f --build-dir temp_sensor_build samples\temp_sensor --> use this command to build in zephyrproject\zephyr folder

#define I2C_DEV1 "I2C_0"

//Si7021 Commands
//Measure Relative Humidity, Hold Master Mode
#define MEAS_RH_HOLD 0xE5
//Measure Relative Humidity, No Hold Master Mode
#define MEAS_RH_NO_HOLD 0xF5
//Measure Temperature, Hold Master Mode
#define MEAS_TEMP_HOLD 0xE3
//Measure Temperature, No Hold Master Mode
#define MEAS_TEMP_NO_HOLD 0xF3
//Read Temperature Value from Previous RH Measurement
#define MEAS_TEMP_FROM_PREV_RH 0xE0
//Reset
#define RESET 0xFE
//Write RH/T User Register 1
#define WRITE_RH_T_USR_1 0xE6
//Read RH/T User Register 1
#define READ_RH_T_USR_1 0xE7
//Write Heater Control Register
#define WRITE_HTR_CTRL_REG 0x51
//Read Heater Control Register
#define READ_HTR_CTRL_REG 0x11
//Read Electronic ID 1st Byte
#define READ_ELEC_ID_BYTE_1 0xFA0F
//Read Electronic ID 2nd Byte
#define READ_ELEC_ID_BYTE_2 0xFCC9
//Read Firmware Revision
#define READ_FIRMWARE_V 0x8489

#define SI7021_ADDR 0x40

void main(void)
{		
	//TEMP SENSOR
	//look for i2c device, if one is not found, print a message
	
	struct device *i2c_dev1;

	i2c_dev1 = device_get_binding(I2C_DEV1);
	if (!i2c_dev1) {
		printk("I2C: Device driver not found.\n");
		return;
	} else {
		printk("I2C: Device driver found!\n");
		//write to device
		int count = 0;
		
		struct i2c_msg msgs[2];
		//first byte
		u8_t write_data_1[2];
		write_data_1[0]= 0xFA;
		write_data_1[1]= 0x0F; 
		count = i2c_write(i2c_dev1, &write_data_1[0], 2, SI7021_ADDR);
		//delay(100);
		u8_t first_byte;
		count = i2c_read(i2c_dev1, &first_byte, 1, SI7021_ADDR);
		//printk("count = %d\n", count);
		printk("first byte = %d\n", first_byte);
		
		//second byte
		u8_t write_data_2[2];
		write_data_2[0]= 0xFC;
		write_data_2[1]= 0xC9; 
		count = i2c_write(i2c_dev1, &write_data_2[0], 2, SI7021_ADDR);
		//delay(100);
		u8_t second_byte;
		count = i2c_read(i2c_dev1, &second_byte, 1, SI7021_ADDR);
		//printk("count = %d\n", count);
		printk("second byte = %d\n", second_byte);
		
		//firmware version
		write_data_1[0]= 0x84;
		write_data_1[1]= 0x89; 
		count = i2c_write(i2c_dev1, &write_data_1[0], 2, SI7021_ADDR);
		//delay(100);
		u8_t firmware_version;
		count = i2c_read(i2c_dev1, &firmware_version, 1, SI7021_ADDR);
		//printk("count = %d\n", count);
		printk("firmware_version = %d\n", firmware_version);
		
		u8_t temp_read_command = MEAS_TEMP_NO_HOLD;
		u8_t humidity_read_command = MEAS_RH_HOLD;
		u8_t temp_msb;
		u8_t temp_lsb;
		u8_t humidity_msb;
		u8_t humidity_lsb;
		u16_t temp;
		u16_t humidity;

		
		//Make a temperature reading
		while (1) {
			count = i2c_write(i2c_dev1, &temp_read_command, 1, SI7021_ADDR);
			k_sleep(1);
			count = i2c_read(i2c_dev1, &temp_msb, 1, SI7021_ADDR);
			count = i2c_read(i2c_dev1, &temp_lsb, 1, SI7021_ADDR);
			temp = temp_msb << 8 | temp_lsb;
			temp = (((175.72 * temp)/65536) - 46.85)*1.8 + 32; //Fahrenheit
			printk("%d, ", temp);
			
			//Make a humidity reading
			count = i2c_write(i2c_dev1, &humidity_read_command, 1, SI7021_ADDR);
			k_sleep(1);
			count = i2c_read(i2c_dev1, &humidity_msb, 1, SI7021_ADDR);
			count = i2c_read(i2c_dev1, &humidity_lsb, 1, SI7021_ADDR);
			humidity = humidity_msb << 8 | humidity_lsb;
			humidity = ((125*humidity)/65536) - 6;
			printk("%d\n", humidity);
			
			k_sleep(5000);
		}
		
	}
}
