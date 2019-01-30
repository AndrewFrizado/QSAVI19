/* QSAVIArduinoCode*\

#define all pins for voltage reading

/*
* THUMB - FIN_0
* INDEX - FIN_1
* MIDDLE - FIN_2
* RING+PINKY - FIN_3
*/

// I2Cdev and MPU6050 must be installed as libraries, or else the .cpp/.h files
// for both classes must be in the include path of your project
#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"
#include "MPU6050.h" // not necessary if using MotionApps include file

// Arduino Wire library is required if I2Cdev I2CDEV_ARDUINO_WIRE implementation
// is used in I2Cdev.h
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
#include "Wire.h"
#endif

// class default I2C address is 0x68
// specific I2C addresses may be passed as a parameter here
// AD0 low = 0x68 (default for SparkFun breakout and InvenSense evaluation board)
// AD0 high = 0x69
MPU6050 mpus[2]={MPU6050(0x68),MPU6050(0x69)};  // original code said MPU6050 mpu
//MPU6050 mpu2(0x69); // <-- use for AD0 high



/* FIN Pin Call (k-Knuckle, m-middle) */
#define FIN_0K A0
#define FIN_0M A1
#define FIN_1K A2
#define FIN_1M A3
#define FIN_2K A4
#define FIN_2M A5
#define FIN_3K A6
#define FIN_3M A7




/*=========================================
*		ACTUAL ARDUINO CODE 
*==========================================*/

//this is the core of the gyro function

void MPUMath() {


#ifdef OUTPUT_QSAVI_GLOVE

#ifdef WAIT_FOR_REQUEST_BEFORE_SENDING_DATA

    // Wait for request (any 1 byte)
  while (Serial.available() > 0) {      // doesnt like this while or the if  below when viewing through the serial monitor
      if (Serial.read() > 0) {
        
        Serial.print(0); Serial.print(","); // used for calibration
 
     for (int i = 0; i < 2; i++) {
        mpus[i].dmpGetQuaternion(&q, fifoBuffer[i]);
       // Serial.println("Waiting for request");

        Serial.print(q.w); Serial.print(",");
        Serial.print(q.x); Serial.print(",");
        Serial.print(q.y); Serial.print(",");
        Serial.print(q.z); Serial.print(",");
       }
        Serial.print(analogRead(8));Serial.print(","); Serial.print(analogRead(9));Serial.print(","); // thumb
         Serial.print(analogRead(10));Serial.print(","); Serial.print(analogRead(11));Serial.print(","); // index
         Serial.print(analogRead(12));Serial.print(","); Serial.print(analogRead(13));Serial.print(","); // middle
          Serial.print(analogRead(14));Serial.print(","); Serial.println(analogRead(15)); // pinky
          // string length should be 17 now

     
#endif
     
#ifdef WAIT_FOR_REQUEST_BEFORE_SENDING_DATA
     
   } 
  }
#endif

#endif
//{
#ifdef OUTPUT_READABLE_QUATERNION

#ifdef WAIT_FOR_REQUEST_BEFORE_SENDING_DATA
    // Wait for request (any 1 byte)
    while (Serial.available() > 0) {
      if (Serial.read() > 0) {
      #endif
      
    // Setup the buttonState to read the status of the button
    buttonState = digitalRead(BUTTON_PIN);
    // If using button, set if condition buttonstate to LOW
    // If using touch sensor, use HIGH
    if (buttonState == HIGH) // Condition if button is not pressed, LOW for button, HIGH for touch sensor
    {Serial.print("1,");
    }
    else if (buttonState == LOW) // Condition if button is pressed, HIGH for button, LOW for touch sensor
    {Serial.print("2,");
    }
        // display quaternion values in easy matrix form: w, x, y, z
        mpu.dmpGetQuaternion(&q, fifoBuffer);
        //Serial.print("quat\t");
        Serial.print(q.w);
        Serial.print(",");
        Serial.print(q.x);
        Serial.print(",");
        Serial.print(q.y);
        Serial.print(",");
        Serial.print(q.z);
        Serial.print(",");
        Serial.print(0);
        Serial.print(",");
        Serial.print(0);
        Serial.print(",");
        Serial.print(0);
        Serial.print(",");
        Serial.print(0);
        

      #ifdef WAIT_FOR_REQUEST_BEFORE_SENDING_DATA
      }
    }
#endif

#endif
//}
//{
#ifdef OUTPUT_READABLE_EULER
    // display Euler angles in degrees

      mpu.dmpGetQuaternion(&q, fifoBuffer);
      mpu.dmpGetEuler(euler, &q);
      //            Serial.print("euler\t");
      Serial.print(euler[0] * 180 / M_PI);
      Serial.print(",");
      Serial.print(euler[1] * 180 / M_PI);
      Serial.print(",");
      Serial.println(euler[2] * 180 / M_PI);

#endif
//}


#ifdef OUTPUT_READABLE_YAWPITCHROLL
    // Setup the buttonState to read the status of the button
    buttonState = digitalRead(BUTTON_PIN);
    // If using button, set if condition buttonstate to LOW
    // If using touch sensor, use HIGH
    if (buttonState == HIGH) // Condition if button is not pressed, LOW for button, HIGH for touch sensor
    {
      // display Euler angles in degrees
      mpu.dmpGetQuaternion(&q, fifoBuffer);
      mpu.dmpGetGravity(&gravity, &q);
      mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);
      Serial.print("1,");
    }
    else if (buttonState == LOW) // Condition if button is pressed, HIGH for button, LOW for touch sensor
    {
      // display Euler angles in degrees
      mpu.dmpGetQuaternion(&q, fifoBuffer);
      mpu.dmpGetGravity(&gravity, &q);
      mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);
      Serial.print("2,");
    }
    Serial.print(ypr[0] * 180 / M_PI);
    Serial.print(",");
    Serial.print(ypr[1] * 180 / M_PI);
    Serial.print(",");
    Serial.println(ypr[2] * 180 / M_PI);
    delay(SEND_DELAY);
#endif

#ifdef OUTPUT_READABLE_REALACCEL
    // display real acceleration, adjusted to remove gravity
    mpu.dmpGetQuaternion(&q, fifoBuffer);
    mpu.dmpGetAccel(&aa, fifoBuffer);
    mpu.dmpGetGravity(&gravity, &q);
    mpu.dmpGetLinearAccel(&aaReal, &aa, &gravity);
    Serial.print("0,");
    Serial.print(",");
    Serial.print(aaReal.x);
    Serial.print(",");
    Serial.print(aaReal.y);
    Serial.print(",");
    Serial.println(aaReal.z);
    //            delay(20);
#endif

#ifdef OUTPUT_READABLE_WORLDACCEL
    // display initial world-frame acceleration, adjusted to remove gravity
    // and rotated based on known orientation from quaternion
    mpu.dmpGetQuaternion(&q, fifoBuffer);
    mpu.dmpGetAccel(&aa, fifoBuffer);
    mpu.dmpGetGravity(&gravity, &q);
    mpu.dmpGetLinearAccel(&aaReal, &aa, &gravity);
    mpu.dmpGetLinearAccelInWorld(&aaWorld, &aaReal, &q);
    Serial.print("aworld\t");
    Serial.print(aaWorld.x);
    Serial.print("\t");
    Serial.print(aaWorld.y);
    Serial.print("\t");
    Serial.println(aaWorld.z);
    //            delay(20);
#endif

    unsigned long currentMillis =  millis();  //.....................................................

    // Blink "Hearbeat" LED to indicate activity
    if (currentMillis - lastHearbeadLedBlinkTime >= HEARBEAT_LED_BLINK_TIME) {
      lastHearbeadLedBlinkTime = currentMillis;
      blinkState = !blinkState;
      digitalWrite(LED_PIN, blinkState);
      
    }

}

 


void setup() 
{
  Serial.begin(115200);
  while (!Serial);  // Wait for the connection to be established?

  // Run MPU initializations
  i2cSetup();
  MPU6050Connect();
  pinMode(LED_PIN, OUTPUT);
  loop();
}

void loop() 
{
 unsigned long currentMillis = millis();   // Capture the latest value of millis()

  if (mpuInterrupt[0] && mpuInterrupt[1]) { // Wait for MPU interrupt or extra packet(s) available on both MPUs
    GetDMP(); //handles the calls to the gyroscopes
  }
}





