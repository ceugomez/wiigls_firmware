//#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL375.h>
#include <Adafruit_LSM6DSOX.h>

#define ADXL375_SCK 24
#define ADXL375_MISO 22
#define ADXL375_MOSI 23
#define ADXL375_CS 12

#define LSM_CS 13
#define LSM_SCK 24
#define LSM_MISO 22
#define LSM_MOSI 23

Adafruit_ADXL375 acc = Adafruit_ADXL375(ADXL375_CS, &SPI, 12345);
Adafruit_LSM6DSOX sox;
File myFile;


void setup() {
  // put your setup code here, to run once:
   Serial.begin(115200);
   sox.begin_SPI(LSM_CS);
   acc.begin();
   
   SD.begin(4);
   myFile = SD.open("Moving.csv", FILE_WRITE);
   


   sox.setAccelRange(LSM6DS_ACCEL_RANGE_2_G);
   sox.setGyroRange(LSM6DS_GYRO_RANGE_250_DPS);
   sox.setAccelDataRate(LSM6DS_RATE_6_66K_HZ);
   sox.setGyroDataRate(LSM6DS_RATE_6_66K_HZ);
   acc.setDataRate(ADXL343_DATARATE_3200_HZ);




}

void loop() {
  // put your main code here, to run repeatedly:
  int i = 0;
for(i; i<100;i++)
{
  sensors_event_t accel;
  sensors_event_t gyro;
  sensors_event_t temp;   
  sensors_event_t event;
  
  sox.getEvent(&accel, &gyro, &temp);
  acc.getEvent(&event);  
  
  Serial.print("\t\tTemperature ");
  Serial.print(temp.temperature);
  Serial.println(" deg C");

  /* Display the results (acceleration is measured in m/s^2) */
  Serial.print("\t\tAccel X: ");
  Serial.print(accel.acceleration.x);
  Serial.print(" \tY: ");
  Serial.print(accel.acceleration.y);
  Serial.print(" \tZ: ");
  Serial.print(accel.acceleration.z);
  Serial.println(" m/s^2 ");

  /* Display the results (rotation is measured in rad/s) */
  Serial.print("\t\tGyro X: ");
  Serial.print(gyro.gyro.x);
  Serial.print(" \tY: ");
  Serial.print(gyro.gyro.y);
  Serial.print(" \tZ: ");
  Serial.print(gyro.gyro.z);
  Serial.println(" radians/s ");
  Serial.println();


   /* Display the results (acceleration is measured in m/s^2) */
  Serial.print("X: "); Serial.print(event.acceleration.x); Serial.print("  ");
  Serial.print("Y: "); Serial.print(event.acceleration.y); Serial.print("  ");
  Serial.print("Z: "); Serial.print(event.acceleration.z); Serial.print("  ");Serial.println("m/s^2 ");
  delay(100);

 
  //SD.begin(4);
  //if(myFile)
  //{
//myFile;
    myFile.print(accel.acceleration.x); myFile.print(",");
    myFile.print(accel.acceleration.y); myFile.print(",");
    myFile.print(accel.acceleration.z); myFile.print(",");
    myFile.print(gyro.gyro.x); myFile.print(",");
    myFile.print(gyro.gyro.y); myFile.print(",");
    myFile.print(gyro.gyro.z); myFile.print(",");
    myFile.print(event.acceleration.x); myFile.print(",");
    myFile.print(event.acceleration.y); myFile.print(",");
    myFile.print(event.acceleration.z); myFile.print(",");
    myFile.println();

}
Serial.println("Saving data to SD card");
myFile.close();

}
