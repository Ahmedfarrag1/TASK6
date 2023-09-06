#include <Wire.h>

//define variables
const int MPU = 0x68; // MPU6050 I2C address
float GyroZ;          // rotational velocity 
float yaw;            // retrieved angle in deg
float GyroErrorZ = 0;     // calculated error from calculate_IMU_error function 
float elapsedTime, currentTime, previousTime;    //time variables
int counter = 0;  //number of trials to get the most accurate error value



void setup(){
  Serial.begin(9600);
  Wire.begin();                      // Initialize comunication
  Wire.beginTransmission(MPU);       // Start communication with MPU6050 // MPU=0x68
  Wire.write(0x6B);                  // Talk to the register 6B
  Wire.write(0x00);                  // Make reset - place a 0 into the 6B register
  Wire.endTransmission(true);        //end the transmission

  // Configure Gyro Sensitivity - Full Scale Range 
  Wire.beginTransmission(MPU);
  Wire.write(0x1B);                   // Talk to the GYRO_CONFIG register (1B hex)
  Wire.write(0x00);                   // Set the register bits as (+-250 deg/s full scale)
  Wire.endTransmission(true);

  // Call this function if you need to get the IMU error values for your module
  calculate_IMU_error();
  delay(20);
}

void loop(){


  // === Read gyroscope data === //
  previousTime = currentTime;        // Previous time is stored before the actual time read
  currentTime = millis();            // Current time actual time read
  elapsedTime = (currentTime - previousTime) / 1000; // Divide by 1000 to get seconds
  Wire.beginTransmission(MPU);
  Wire.write(0x43); // Gyro data first register address 0x43
  Wire.endTransmission(false);
  Wire.requestFrom(MPU, 2, true); // Read the required registers
  GyroZ = (Wire.read() << 8 | Wire.read()) / 131.0; // For a 250 deg/s range we have to divide first the raw value by 131.0, according to the datasheet



  // Correct the outputs with the calculated error values
  GyroZ = GyroZ + 0.79; // GyroErrorZ ~ (-0.8)
  // Currently the raw values are in degrees per seconds, deg/s, so we need to multiply by sendonds (s) to get the angle in degrees
  yaw =  yaw + GyroZ * elapsedTime;

  // Print the values on the serial monitor
  Serial.println(yaw);
}


void calculate_IMU_error() {
  // We can call this funtion in the setup section to calculate the gyro data error. 
  //From here we will get the error values used in the above equations printed on the Serial Monitor.
  // Note that we should place the IMU flat in order to get the proper values, so that we then can the correct values
  counter = 0;
  // Read gyro values 200 times
  while (counter < 200) {
    Wire.beginTransmission(MPU);
    Wire.write(0x43);
    Wire.endTransmission(false);
    Wire.requestFrom(MPU, 2, true);
    GyroZ = Wire.read() << 8 | Wire.read();
    // Sum all readings
    GyroErrorZ = GyroErrorZ + (GyroZ / 131.0);
  }
  //Divide the sum by 200 to get the error value
  GyroErrorZ = GyroErrorZ / 200;
  // Print the error value on the Serial Monitor
  Serial.print("GyroErrorZ: ");
  Serial.println(GyroErrorZ);
}

