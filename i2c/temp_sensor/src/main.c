/*
 * EC544: i2c interface with temperature sensor
 */

#include <zephyr.h>
#include <misc/printk.h>
#include <i2c.h>
#include <device.h>

//i2c functions we will need to use from i2c.h
// i2c_configure()
// i2c_write()
// i2c_read()
// i2c_write_read()
//west build -b frdm_k64f --build-dir temp_sensor_build samples\temp_sensor --> use this command to build in zephyrproject\zephyr folder

#define I2C_DEV "I2C_0"

void main(void)
{
	//printk("Hello World! %s\n", CONFIG_BOARD);
	//printk("New Test! %s\n", CONFIG_BOARD);
	struct device *i2c_dev;
	
	//look for i2c device, if one is not found, print a message
	i2c_dev = device_get_binding(I2C_DEV);
	if (!i2c_dev) {
		printk("I2C: Device driver not found.\n");
		return;
	}

	
}
