# 2019_panicAttackBlockchain

## Purpose
The purpose of this project is to use collect different types of data to measure various physiological responses in order to determine if an individual is experiencing a panic attack. The data from these sensors as well as the results will be stored on the blockchain, a secure and decentralized form of data storage. The custom blockchain network can then be accessed by patients and medical professionals in order to see how often a panic attack is occurring as well as to observe some basic medical data, such as heart rate.  Ultimately this information will allow the user to keep track of the frequency and severity of anxiety attacks, which will then aid a primary care physician in the the creation of a customized treatment plan. 

## Implementation
Our implementation involved using a FRDM board running Zephyr OS to read in sensor data and process it and printing that data to a serial terminal. When this data was printed out to the terminal, a new text file was created that contained this data. This data file is monitored by a script written in GO to determine when a new text file is created. When a new text file is created, it pushes it to IPFS (InterPlanetary File System), which in turn returns a file hash. The GO script then pushes this hash value to the blockchain so that other users of the blockchain can also have access to that data.

## Zephyr OS Build
In order to build Zephyr OS for the FRDM-K64F board we followed the instructions on th Getting Started guide on the Zephyr OS website: https://docs.zephyrproject.org/latest/getting_started/getting_started.html. In order to follow these instructions, make sure that you have followed the instructions for setting up your development environment first (this is at the top of the "Getting Started" page linked here.

We were able to successfully build the OS for the FRDM board on both MAC and Windows development environments. We used the GNU Arm Embedded Toolchain. We started out by building the hello world application to ensure that that could run be built and on the FRDM board, before attempting to compile more complicated examples that would be needed for our project. The directions for building the hello world application are in the "Getting Started" link above. 


## Setting up I2C_0 on the FRDM Board Using Zephyr
After cloning the zephyr project repository according to the instructions in the above link,  you will have a folder called zephyrproject/zephyr/samples. In order to build our own application, we added a sample in folder called "temp_sensor" to the this samples folder (the same folder where the hello world sample is located). The contents of the "temp_sensor" folder are located in this repository in the i2c/temp_sensor folder. After creating this example, some changes needed to be made to the configuration files to make sure that the I2C and the random number generator were enabled. These configuration files are also located in this repository in the i2c/zephyr_repo_config/ folder. There are two files in this folder, frdm_k64f_defconfig and kconfig.degconfig. These files need to be replace the existing files with the same names in the zephyrproject/zephyr/boards/arm/frdm_k64f folder. Once all of these files are in the correct place, we ran the command: 'west build -b frdm_k64f --build-dir temp_sensor_build samples\temp_sensor' from the zephyrproject/zephyr folder to build this application. After this application was successfully built, we connected the FRDM board to a laptop via USB, and to the ran the command: 'ninja flash' from the zephyrprokect/zephyr/temp_sensor_build folder to flash the application and Zephyr OS to the board.


## Monitoring Script
Make sure either teraterm or zoc are logging the serial data to a log that matches the file name in teraterm.java. Then run teraterm.java which will save data in the Blockchain's medicalData directory. 

## Blockchain

1. Download GO
	-https://golang.org/dl/

2. Download IPFS 
	- https://docs.ipfs.io/introduction/install/

3. Download LibP2P
	- Setup
	The best way to get your code environment set up is to clone this entire library and write your code within it. You can     develop outside the environment they provide but it requires knowing how to work with gx. We’ll show you the easy way.        Assuming you already have Go installed:

	go get -d github.com/libp2p/go-libp2p/...
	navigate to the cloned directory from above
	make
	make deps
	This gets you all the packages and dependencies you need from this repo through the gx package manager. Again, we don’t     like gx as it breaks a lot of Go convention (besides, why not just stick with go get?) but it’s worth the inconvenience to    use this otherwise nice library.

	We’re going to develop inside the examples subdirectory. So let’s create a directory under examples called p2p with

	mkdir ./examples/p2p
	Then navigate to your new p2p folder and create a main.go file. We will be writing all our code in this file.

3. IPFS Init (Only if you haven't initialized it yet) 

4. IPFS daemon
	- Starts IPFS Node 

5. Start P2P network with terminal command 
	- go run main.go -l 10000 -secio

6. Follow instructions to open additional connections 

You will see that the blockchain now contains all the data from the serial log, in individual textfiles connected to individual blocks. 

