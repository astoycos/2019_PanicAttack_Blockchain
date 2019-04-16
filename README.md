# 2019_panicAttackBlockchain

## Purpose
The purpose of this project is to use a combination of sensors in order to determine if an individual is experiencing a panic attack. The data from these sensors as well as the results will be stored on the blockchain, a secure and decentralized form of data storage. The custom blockchain network can then be accessed by patients and medical professionals in order to see how often a panic attack is occurring as well as to observe some basic medical data, such as heart rate.  Ultimately this information will allow the user to keep track of the frequency and severity of anxiety attacks, which will then aid a primary care physician in the the creation of a customized treatment plan. 

## Things To Do
-Develop functionalities to sense vibration, heartbeat, and temperature via I2C sensors
-Build AnyLedger in the ZephyrOS environment under samples
-Flash the AnyLedger sample to the FRDM board
-Setup networking on FRDM board(?) to connect to blockchain
-Run tests and debugging