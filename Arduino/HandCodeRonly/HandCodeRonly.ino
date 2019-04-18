<<<<<<< HEAD
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); //for uno 
  Serial.begin(115200); //for Mega

  i2cSetup();
  
  
}
float readAngle(float[] voltages, const char* const inputs[]){
    /*thumb to pinky, A0 -> A3*/
    short maxInputs = 4;
    float avgValue = 0;
    float avgAngle = 0;
    float temp_tot = 0; 

    for(int i = 0; i < maxInputs; i++){
        voltages[i] = analogRead[i];
    }

    for(i = 0; i < maxInputs; i++){
        avgValue += resistances[i];
    }
    

    for (i = 0; i<maxInputs;i++){
      temp_tot += ratio[i];
    }
  
    avgValue /= 4;
    avgRat = temp_tot/4;
      

    /* Now we need to calculation to convert to angle */
    avgAngle = avgValue * avgRatio;
    return avgAngle;    
}

float readIndAngle(float[] voltages, const char* const inputs[])
{
    short maxInputs = 4; 
    float angleArray = []; 
    float temp = 0; 

    for (int i = 0; i < maxInputs; i++) 
    {
      temp = analogRead[inputs[i]]; 
      voltages[i] = float2Volt(temp); 
    }
   
    for (int i = 0; i < maxInputs, i++)
    {
      angleArray[i] = voltages[i]; 
    } 

    return angleArray[];
    
}

float intToVolt(float val) 
{
  int maxVal = 1023; 
  int maxVolt = 5;

  voltage = float(val/maxVal * maxVolt);
  return voltage;
}

void loop() {
  // put your main code here, to run repeatedly:
      angle = readAngle();
      //if we wish to read each individual finger 
      // 
      
}
=======
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); //for uno 
  Serial.begin(115200); //for Mega

  i2cSetup();
  
  
}
float readAngle(float[] voltages, const char* const inputs[]){
    /*thumb to pinky, A0 -> A3*/
    short maxInputs = 4;
    float avgValue = 0;
    float avgAngle = 0;
    float temp_tot = 0; 

    for(int i = 0; i < maxInputs; i++){
        voltages[i] = analogRead[i];
    }

    for(i = 0; i < maxInputs; i++){
        avgValue += resistances[i];
    }
    

    for (i = 0; i<maxInputs;i++){
      temp_tot += ratio[i];
    }
  
    avgValue /= 4;
    avgRat = temp_tot/4;
      

    /* Now we need to calculation to convert to angle */
    avgAngle = avgValue * avgRatio;
    return avgAngle;    
}

float readIndAngle(float[] voltages, const char* const inputs[])
{
    short maxInputs = 4; 
    float angleArray = []; 
    float temp = 0; 

    for (int i = 0; i < maxInputs; i++) 
    {
      temp = analogRead[inputs[i]]; 
      voltages[i] = float2Volt(temp); 
    }
   
    for (int i = 0; i < maxInputs, i++)
    {
      angleArray[i] = voltages[i]; 
    } 

    return angleArray[];
    
}

float intToVolt(float val) 
{
  int maxVal = 1023; 
  int maxVolt = 5;

  voltage = float(val/maxVal * maxVolt);
  return voltage;
}

void loop() {
  // put your main code here, to run repeatedly:
      angle = readAngle();
      //if we wish to read each individual finger 
      // 
      
}
>>>>>>> 6f0c51ba9ad63f5481a6417ceaf3600e60c2baed
