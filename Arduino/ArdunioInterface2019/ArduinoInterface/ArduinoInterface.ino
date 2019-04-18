#include <SoftwareSerial.h>
#include <SerialCommand.h>

SerialCommand sCmd;
const int inputs[4] = {0, 1, 2, 3};
const float ratio[2][4] = {
  {3, 17, 13, 3},
  {11, 55, 50, 17}
};
const float vsupply = 5.00;

void setup() {
  Serial.begin(9600); //for uno
  // Serial.begin(115200); //for Mega

  while (!Serial);
  sCmd.addCommand("PING", pingHandler);
  // Can add handlers for multiple fingers, active is for testing one
  sCmd.addCommand("ACTIVE", unityHandler);
  for (int i = 0; i < 4; i++)
  {
    pinMode(inputs[i], INPUT);
  }
}

void pingHandler() {
  short maxInputs = 4;
  float angleArray[maxInputs];
  float* angle;
  angle = readIndAngle(maxInputs, angleArray);

  //Sends a single arduino input to unity
  Serial.println(angle[0]);

  //Code for sending all 4 inputs to unity in progress
  /*
    strcpy(result, angleArray[1]
    char *combString = malloc((maxInputs * strlen(numBuff)) + 1);

    for (int i = 0; i < maxInputs; i++)
    {
      char numBuff[4];
      itoa(angleArray[i], numBuff, 10);
      strcat(combString, numBuff);
    }
    Serial.println();*/
}

float* readIndAngle(short maxInputs, float angleArray[])
{
  float voltages[maxInputs];
  float temp = 0;

  for (int i = 0; i < maxInputs; i++)
  {
    voltages[i] = analogRead(inputs[i]);
    //voltages[i] = float2theta(temp, i);
  }

  for (int i = 0; i < maxInputs; i++)
  {
    angleArray[i] = voltages[i];
  }

  return angleArray;
}

float float2theta(float val, int ratInd)
{
  int maxVal = 1023;
  int Rmax = ratio[2][ratInd];
  int Rmin = ratio[1][ratInd];
  int theta_min = 0;
  int theta_max = 180;
  float voltage = 0;
  float theta = 0;
  float R = 0;
  float R1 = 5000;

  voltage = float(val * 5 / maxVal);
  R = (voltage * R1) / (vsupply - voltage);
  theta = theta_min + ((theta_max - theta_min) / (Rmax - Rmin)) * (R - Rmin);

  return theta;
}

void unityHandler() {
  char *arg;
  arg = sCmd.next();
  //Get the serial command 
  if (arg != NULL)
    //haptic behaviour goes here
}

void loop() {
  if (Serial.available() > 0) sCmd.readSerial();
  /*pingHandler();
  /*responses = getUnityData();
    for (int i = 0; i < maxInputs; i++)
    {
    if (responses[i] == true)
    {
      hapticResponse(i); //still needs to be written
    }
    }
    //recieve from Unity. */
}
