/*
 * EC544: i2c interface with temperature sensor
 */

#include <zephyr.h>
#include <misc/printk.h>
#include <i2c.h>
#include <device.h>
#include <stdio.h>
#include <time.h>

//i2c functions we will need to use from i2c.h
// i2c_configure()
// i2c_write()
// i2c_read()
// i2c_write_read()
//west build -b frdm_k64f --build-dir temp_sensor_build samples\temp_sensor --> use this command to build in zephyrproject\zephyr folder

#define I2C_DEV "I2C_0"
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
	//should this be done here?
	//DEVICE_INIT(I2C_DEV, drv_name, init_fn, data, cfg_info, level, prio)
	//init_fn -- address of init function of driver

	struct device *i2c_dev;
	
	//return i2c_transfer(i2c_dev, &msgs[0], 2, FRAM_I2C_ADDR);
	/*
	 * @param dev Pointer to the device structure for the driver instance.
 * @param buf Memory pool that stores the retrieved data.
 * @param num_bytes Number of bytes to read.
 * @param addr Address of the I2C device being read.
 *
 * @retval 0 If successful.
 * @retval -EIO General input / output error.
 
static inline int i2c_read(struct device *dev, u8_t *buf,
			   u32_t num_bytes, u16_t addr)
*/
	//look for i2c device, if one is not found, print a message
	i2c_dev = device_get_binding(I2C_DEV);
	if (!i2c_dev) {
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
		count = i2c_write(i2c_dev, &write_data_1[0], 2, SI7021_ADDR);
		//delay(100);
		u8_t first_byte;
		count = i2c_read(i2c_dev, &first_byte, 1, SI7021_ADDR);
		//printk("count = %d\n", count);
		printk("first byte = %d\n", first_byte);
		
		//second byte
		u8_t write_data_2[2];
		write_data_2[0]= 0xFC;
		write_data_2[1]= 0xC9; 
		count = i2c_write(i2c_dev, &write_data_2[0], 2, SI7021_ADDR);
		//delay(100);
		u8_t second_byte;
		count = i2c_read(i2c_dev, &second_byte, 1, SI7021_ADDR);
		//printk("count = %d\n", count);
		printk("second byte = %d\n", second_byte);
		
		//firmware version
		write_data_1[0]= 0x84;
		write_data_1[1]= 0x89; 
		count = i2c_write(i2c_dev, &write_data_1[0], 2, SI7021_ADDR);
		//delay(100);
		u8_t firmware_version;
		count = i2c_read(i2c_dev, &firmware_version, 1, SI7021_ADDR);
		//printk("count = %d\n", count);
		printk("firmware_version = %d\n", firmware_version);
		
		//Make a measurment reading
		u8_t temp_read_command = 0xF3;
		//temp_read_command[0] = 0xF3;
		count = i2c_write(i2c_dev, &temp_read_command, 1, SI7021_ADDR);
		u8_t temp_msb;
		u8_t temp_lsb;
		//delay(100);
		u16_t temp;
		k_sleep(1);
		count = i2c_read(i2c_dev, &temp_msb, 1, SI7021_ADDR);
		count = i2c_read(i2c_dev, &temp_lsb, 1, SI7021_ADDR);
		temp = temp_msb << 8 | temp_lsb;
		printk("temp = %d\n", temp);
		
		//Make a humidity reading
		u8_t humidity_read_command = 0xE5;
		//temp_read_command[0] = 0xF3;
		count = i2c_write(i2c_dev, &humidity_read_command, 1, SI7021_ADDR);
		u8_t humidity_msb;
		u8_t humidity_lsb;
		//delay(100);
		u16_t humidity;
		k_sleep(1);
		count = i2c_read(i2c_dev, &humidity_msb, 1, SI7021_ADDR);
		count = i2c_read(i2c_dev, &humidity_lsb, 1, SI7021_ADDR);
		humidity = humidity_msb << 8 | humidity_lsb;
		printk("humidity = %d\n", humidity);
		
	}
}
