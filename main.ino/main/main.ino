#include <ArduinoIoTCloud.h>
#include <Arduino_ConnectionHandler.h>
#include "thingProperties.h"
float sp, hr, hr_ecg;
int zeroComma = 0, firstComma = 0, secondComma = 0, thirdComma = 0;
String ox, hrate, hrate_ecg, data;
void setup() {
  // Initialize serial and wait for port to open:
  Serial.begin(1152);
  // This delay gives the chance to wait for a Serial Monitor without blocking if none is found
  delay(1500); 

  // Defined in thingProperties.h
  initProperties();

  // Connect to Arduino IoT Cloud
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  
  /*
     The following function allows you to obtain more information
     related to the state of network and IoT Cloud connection and errors
     the higher number the more granular information you’ll get.
     The default is 0 (only errors).
     Maximum is 4
 */
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
}

void loop() {
  ArduinoCloud.update();
  // Your code here 
  if (Serial.available() > 0)
  {
    data = Serial.readStringUntil('\n');
    Serial.println(data);
  }
  //  firstComma = data.indexOf(',');
  zeroComma = data.indexOf('/');         // finding the characters (the check points)
  firstComma = data.indexOf(',');
  secondComma = data.indexOf(':');
  thirdComma = data.indexOf(';');
  /*Serial.println(firstComma);
    Serial.println(secondComma);
    Serial.println(thirdComma);*/
  ox = data.substring((zeroComma+1), firstComma);       // substring to array
  hrate = data.substring((firstComma + 1), (secondComma));
  hrate_ecg = data.substring((secondComma + 1), thirdComma);
  char bufsp[ox.length()];
  char bufhr[hrate.length()];
  char bufhr_ecg[hrate_ecg.length()];
  ox.toCharArray(bufsp, ox.length() + 1);
  hrate.toCharArray(bufhr, hrate.length() + 1);
  hrate_ecg.toCharArray(bufhr_ecg, hrate_ecg.length() + 1);
  sp = atof(bufsp);       // array to float
  hr = atof(bufhr);
  hr_ecg = atof(bufhr_ecg);
  if ((sp != 0))
  {

    spO2 = sp;
  }
  if (hr != 0)
  {
    heart_rate = hr;
  }
  if (hr_ecg != 0)
  {
    heart_rate_ecg = hr_ecg;
  }
  Serial.println(spO2);
  Serial.println(heart_rate);
  Serial.println(heart_rate_ecg);
  Serial.println();
  delay(2000);
}


/*
  Since HrEcg is READ_WRITE variable, onHrEcgChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onHrEcgChange()  {
  // Add your code here to act upon HrEcg change
}