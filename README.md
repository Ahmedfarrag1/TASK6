# Noise elimination

 ****When dealing with a noisy environment and sensor data from the MPU-6050, 
you can employ a filter to mitigate the noise and improve the accuracy of the readings. 
One commonly used filter for this purpose is the **low-pass filter.**

the mpu-6050 sensor provides an embedded low-pas filter that can be configured to eliminate noise, 
from invensense datasheet: register_26  can be configured to control the digital low pass filter for bot gyroscopes and accelerometers, 
the gyroscope **cutoff frequency** ranges from  5 to 256 HZ,