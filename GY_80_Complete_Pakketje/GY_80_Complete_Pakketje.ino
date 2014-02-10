/* Hacked to gether files and librarys to read out al the gy-80 sensors
*/
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP085_U.h>
#include <Adafruit_ADXL345_U.h>
#include <L3G4200D.h>
L3G4200D gyro;
#define address 0x1E //0011110b, I2C 7bit address of HMC5883
float ground_level1;
float ground_level2;
float ground_level3;
float ground_level4;
float ground_level5;
float ground_level6;
float ground_level7;
float ground_level8;
float ground_level9;
float ground_level10;
float ground_level = 1;

float pressure1;
float pressure2;
float pressure3;
float pressure4;
float pressure5;
float pressure6;
float pressure7;
float pressure8;
float pressure9;
float pressure10;
float pressure;

float temperature;
int x,y,z; //triple axis data

/* This code is based on code from adafruit and kevin-pololu.
 The origial code can be found on github.

 Connections
 ===========
 Connect SCL to analog 5
 Connect SDA to analog 4
 Connect VDD to 3.3V DC
 Connect GROUND to common ground

 */

Adafruit_BMP085_Unified bmp = Adafruit_BMP085_Unified(10085);
/**************************************************************************/
/*
    Displays some basic information on this sensor from the unified
 sensor API sensor_t type (see Adafruit_Sensor for more information)
 */
/**************************************************************************/
void displaySensorDetails1(void)
{
  sensor_t sensor;
  bmp.getSensor(&sensor);
  Serial.println("------------------------------------");
  Serial.print  ("Sensor:       ");
  Serial.println(sensor.name);
  Serial.print  ("Driver Ver:   ");
  Serial.println(sensor.version);
  Serial.print  ("Unique ID:    ");
  Serial.println(sensor.sensor_id);
  Serial.print  ("Max Value:    ");
  Serial.print(sensor.max_value);
  Serial.println(" hPa");
  Serial.print  ("Min Value:    ");
  Serial.print(sensor.min_value);
  Serial.println(" hPa");
  Serial.print  ("Resolution:   ");
  Serial.print(sensor.resolution);
  Serial.println(" hPa");
  Serial.println("------------------------------------");
  Serial.println("");
  delay(10);
}
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);
void displaySensorDetails2(void)
{
  sensor_t sensor;
  accel.getSensor(&sensor);
  Serial.println("------------------------------------");
  Serial.print  ("Sensor:       ");
  Serial.println(sensor.name);
  Serial.print  ("Driver Ver:   ");
  Serial.println(sensor.version);
  Serial.print  ("Unique ID:    ");
  Serial.println(sensor.sensor_id);
  Serial.print  ("Max Value:    ");
  Serial.print(sensor.max_value);
  Serial.println(" hPa");
  Serial.print  ("Min Value:    ");
  Serial.print(sensor.min_value);
  Serial.println(" hPa");
  Serial.print  ("Resolution:   ");
  Serial.print(sensor.resolution);
  Serial.println(" hPa");
  Serial.println("------------------------------------");
  Serial.println("");
  delay(500);
}
void displayDataRate(void)
{
  Serial.print  ("ADXL345 Data Rate:    ");

  switch(accel.getDataRate())
  {
  case ADXL345_DATARATE_3200_HZ:
    Serial.print  ("3200 ");
    break;
  case ADXL345_DATARATE_1600_HZ:
    Serial.print  ("1600 ");
    break;
  case ADXL345_DATARATE_800_HZ:
    Serial.print  ("800 ");
    break;
  case ADXL345_DATARATE_400_HZ:
    Serial.print  ("400 ");
    break;
  case ADXL345_DATARATE_200_HZ:
    Serial.print  ("200 ");
    break;
  case ADXL345_DATARATE_100_HZ:
    Serial.print  ("100 ");
    break;
  case ADXL345_DATARATE_50_HZ:
    Serial.print  ("50 ");
    break;
  case ADXL345_DATARATE_25_HZ:
    Serial.print  ("25 ");
    break;
  case ADXL345_DATARATE_12_5_HZ:
    Serial.print  ("12.5 ");
    break;
  case ADXL345_DATARATE_6_25HZ:
    Serial.print  ("6.25 ");
    break;
  case ADXL345_DATARATE_3_13_HZ:
    Serial.print  ("3.13 ");
    break;
  case ADXL345_DATARATE_1_56_HZ:
    Serial.print  ("1.56 ");
    break;
  case ADXL345_DATARATE_0_78_HZ:
    Serial.print  ("0.78 ");
    break;
  case ADXL345_DATARATE_0_39_HZ:
    Serial.print  ("0.39 ");
    break;
  case ADXL345_DATARATE_0_20_HZ:
    Serial.print  ("0.20 ");
    break;
  case ADXL345_DATARATE_0_10_HZ:
    Serial.print  ("0.10 ");
    break;
  default:
    Serial.print  ("???? ");
    break;
  }
  Serial.println(" Hz");
}

void displayRange(void)
{
  Serial.print  ("ADXL345 Range:         +/- ");

  switch(accel.getRange())
  {
  case ADXL345_RANGE_16_G:
    Serial.print  ("16 ");
    break;
  case ADXL345_RANGE_8_G:
    Serial.print  ("8 ");
    break;
  case ADXL345_RANGE_4_G:
    Serial.print  ("4 ");
    break;
  case ADXL345_RANGE_2_G:
    Serial.print  ("2 ");
    break;
  default:
    Serial.print  ("?? ");
    break;
  }
  Serial.println(" g");
}

///---///
void setup(void)
{
  Serial.begin(9600);
  Wire.begin();
  gyro.enableDefault();
  //Put the HMC5883 IC into the correct operating mode
  Wire.beginTransmission(address); //open communication with HMC5883
  Wire.write(0x02); //select mode register
  Wire.write(0x00); //continuous measurement mode
  Wire.endTransmission();



  // Initialise the sensors
  if(!bmp.begin())
  {
    // If the sensor can't be found
    Serial.print("Ooops, no BMP085 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }
  if(!accel.begin())
  {
    // If the sensor can't be found
    Serial.println("Ooops, no ADXL345 detected ... Check your wiring!");
    while(1);
  }

  // Set the datarate and range to whatever is appropriate for your project
  // accel.setRange(ADXL345_RANGE_16_G);
  // displaySetRange(ADXL345_RANGE_8_G);
  // displaySetRange(ADXL345_RANGE_4_G);
  // displaySetRange(ADXL345_RANGE_2_G);
  accel.setRange(ADXL345_RANGE_2_G);
  accel.setDataRate(ADXL345_DATARATE_200_HZ);

  // Display some basic information on the sensors
  Serial.println("GY-80");
  displaySensorDetails1();
  displaySensorDetails2();
  displayDataRate();
  displayRange();
  Serial.println("");
}

///---///
void loop(void)
{
  // Get a new sensor events
  sensors_event_t event;
  bmp.getEvent(&event);
  // Calibrate height readings to ground level
  if (ground_level<10)
  {
    delay(25);
    //Trying to make the sensor output more stable, probably going to replace this with a kalman filter
    ground_level1 = event.pressure;
    delay(25);
    ground_level2 = event.pressure;
    delay(25);
    ground_level3 = event.pressure;
    delay(25);
    ground_level4 = event.pressure;
    delay(25);
    ground_level5 = event.pressure;
    delay(25);
    ground_level6 = event.pressure;
    delay(25);
    ground_level7 = event.pressure;
    delay(25);
    ground_level8 = event.pressure;
    delay(25);
    ground_level9 = event.pressure;
    delay(25);
    ground_level10 = event.pressure;
    ground_level = (ground_level1 + ground_level2 + ground_level3 + ground_level4) / 4;
  }

  // Display the results (barometric pressure is measure in hPa)
  if (event.pressure)
  {
    // Trying to make the sensor output more stable, probably going to replace this with a kalman filter
    pressure1 = event.pressure;
    delay(25);
    pressure2 = event.pressure;
    delay(25);
    pressure3 = event.pressure;
    delay(25);
    pressure4 = event.pressure;
    delay(25);
    pressure5 = event.pressure;
    delay(25);
    pressure6 = event.pressure;
    delay(25);
    pressure7 = event.pressure;
    delay(25);
    pressure8 = event.pressure;
    delay(25);
    pressure9 = event.pressure;
    delay(25);
    pressure10 = event.pressure;
    // Display atmospheric pressue in hPa
    pressure = ( pressure1 + pressure2 + pressure3 + pressure4 ) / 4;
    Serial.print("Pressure:    ");
    Serial.print(pressure);
    Serial.println(" hPa");

    // Display current temperature from the BMP085
    bmp.getTemperature(&temperature);
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println(" C");

    /* Heigth calculation 

     ((P0/P)^(1/5.257) - 1) * (T + 273.15)
     h = -------------------------------------
     0.0065

     where: h   = height (in meters)
     P0  = gorund level pressure (in hPa)
     P   = atmospheric pressure (in hPa)
     T   = temperature (in °C)           */
     
     
    float seaLevelPressure = ground_level;
    Serial.print("Altitude:    ");
    Serial.print(bmp.pressureToAltitude(seaLevelPressure,
    event.pressure,
    temperature));
    Serial.println(" m");
  }
  else
  {
    Serial.println("Sensor error");
  }

  accel.getEvent(&event);
  // Display the results (acceleration is measured in m/s^2) 
  Serial.print("Acceleration: X: ");
  Serial.print(event.acceleration.x);
  Serial.print("  ");
  Serial.print("Y: ");
  Serial.print(event.acceleration.y);
  Serial.print("  ");
  Serial.print("Z: ");
  Serial.print(event.acceleration.z);
  Serial.print("  ");
  Serial.println("m/s^2 ");


  /// GYRO CODE ///
  gyro.read();
  Serial.print("Gyroscoop: ");
  Serial.print("X: ");
  Serial.print((int)gyro.g.x);
  Serial.print(" Y: ");
  Serial.print((int)gyro.g.y);
  Serial.print(" Z: ");
  Serial.println((int)gyro.g.z);


  /// COMPASS CODE ///
  //Tell the HMC5883 where to begin reading data
  Wire.beginTransmission(address);
  Wire.write(0x03); //select register 3, X MSB register
  Wire.endTransmission();


  //Read data from each axis, 2 registers per axis
  Wire.requestFrom(address, 6);
  if(6<=Wire.available()){
    x = Wire.read()<<8; //X msb
    x |= Wire.read(); //X lsb
    z = Wire.read()<<8; //Z msb
    z |= Wire.read(); //Z lsb
    y = Wire.read()<<8; //Y msb
    y |= Wire.read(); //Y lsb
  }

  //Print out values of each axis
  Serial.print("Compass: x: ");
  Serial.print(x);
  Serial.print("  y: ");
  Serial.print(y);
  Serial.print("  z: ");
  Serial.println(z);
  Serial.println("");
  Serial.println("");

  delay(500);
}








