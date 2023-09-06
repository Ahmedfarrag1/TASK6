her we ar going to describe the arduino code:

we first need to include wire.h library to generate I2C communication between the sensor and the arduino.

in the setup section, we need to reset the sensor through the power management register, in order to do that
we needed to look at the datasheet to get the register address, then we selected the full-scale range according to the 
extracted information from the datasheet

in the loop section, we start by reading the gyroscope data, the axis data is stored in two bytes or registers 
tha we can get their addresses from the datasheet.

then we read the accelerometer data, and using the requetfrom function we requested to read 2 bytes from the register 

since the reading can include a huge margin of error, we attempted to eliminate this error usni the CALCULATE_IMU_ERROR()
function to get the optimal error value, we implemented this through getting 200 different readings then summing them and dividing them by their number
to get the mean reading and subtract this value from the readings from the sensor, then we printed the error value on the serial monitor.


