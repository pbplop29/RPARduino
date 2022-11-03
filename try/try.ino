//
// Copyright 2015 Google Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

// FirebaseDemo_ESP8266 is a sample that demo the different functions
// of the FirebaseArduino API.

#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

// Set these to run example.
#define FIREBASE_HOST "nodetest-66e6e-default-rtdb.asia-southeast1.firebasedatabase.app"
#define FIREBASE_AUTH "eWojpmCZJD4nLK6P8B9pHlSUrA55d3tXwkAWLUT5"
#define WIFI_SSID "pillow-share"
#define WIFI_PASSWORD "lollollollol"


// SPO2 stuff
  float heart_rate;
  float heart_rate_ecg;
  float spO2,received;
  int ir;
float sp, hr, hr_ecg;
int zeroComma = 0, firstComma = 0, secondComma = 0, thirdComma = 0;
String ox, hrate, hrate_ecg, data;



void setup() {
  Serial.begin(115200);

  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
 // Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
   // Serial.print(".");
    delay(500);
  }
 // Serial.println();
 // Serial.print("connected: ");
 // Serial.println(WiFi.localIP());
  
  Firebase.begin(FIREBASE_HOST,FIREBASE_AUTH);
}

int check_count = 0;

void loop() {

// Spo2 Stuff
if (Serial.available())
  {
    data = Serial.readStringUntil('\n');
    Serial.println(data);
  }
  //  firstComma = data.indexOf(',');
  zeroComma = data.indexOf('/');
  firstComma = data.indexOf(',');
  secondComma = data.indexOf(':');
  thirdComma = data.indexOf(';');
  /*Serial.println(firstComma);
   // Serial.println(secondComma);
   // Serial.println(thirdComma);*/
  ox = data.substring((zeroComma+1), firstComma);
  hrate = data.substring((firstComma + 1), (secondComma));
  hrate_ecg = data.substring((secondComma + 1), thirdComma);
  /*Serial.println("The first reading of " + data + " is " + ox);
   // Serial.println("The second reading of " + data + " is " + hrate);
   // Serial.println("The third reading of " + data + " is " + hrate_ecg);*/
  char bufsp[ox.length()];
  char bufhr[hrate.length()];
  char bufhr_ecg[hrate_ecg.length()];
  ox.toCharArray(bufsp, ox.length() + 1);
  hrate.toCharArray(bufhr, hrate.length() + 1);
  hrate_ecg.toCharArray(bufhr_ecg, hrate_ecg.length() + 1);
  sp = atof(bufsp);
  hr = atof(bufhr);
  hr_ecg = atof(bufhr_ecg);
  /*Serial.println(sp);
   // Serial.println(hr);
   // Serial.println(hr_ecg);*/
  if ((sp > 0))
  {

    spO2 = sp;
  }
  if (hr > 0)
  {
    heart_rate = hr;
  }
  if (hr_ecg > 0)
  {
    heart_rate_ecg = hr_ecg;
  }


  // FIREBASE STUFF





  Firebase.setString("message", "Measuring");
  // handle error
  if (Firebase.failed()) {
     // Serial.print("setting /message failed:");
     // Serial.println(Firebase.error());  
      return;
  }
  
  
  


  // set value
  Firebase.setFloat("SpO2", spO2);
  // handle error
  if (Firebase.failed()) {
     // Serial.print("setting /number failed:");
     // Serial.println(Firebase.error());  
      return;
  }
  Firebase.setFloat("Heart Rate", heart_rate);
  // handle error
  if (Firebase.failed()) {
     // Serial.print("setting /number failed:");
     // Serial.println(Firebase.error());  
      return;
  }
  Firebase.setFloat("Heart Rate ECG", heart_rate_ecg);
  // handle error
  if (Firebase.failed()) {
     // Serial.print("setting /number failed:");
     // Serial.println(Firebase.error());  
      return;
  }
  
  
  

  // get value 
  //Serial.print("SpO2: ");
  //Serial.println(Firebase.getFloat("SpO2"));
  //delay(1000);

  // update value
  //Firebase.setFloat("SpO2", spO2);
  // handle error
    //if (Firebase.failed()) {
     // Serial.print("Connection to firebase failed");
     // Serial.println(Firebase.error());  
      //return;
  //}
//  delay(2000);

  // remove value
  //Firebase.remove("number");
  //delay(1000);


  // set bool value
  //Firebase.setBool("truth", false);
  // handle error
  //if (Firebase.failed()) {
  //   // Serial.print("setting /truth failed:");
  //   // Serial.println(Firebase.error());  
  //    return;
  //}
  //delay(1000);

  // append a new value to /logs
  if (spO2>0) {
  String name = Firebase.pushFloat("SpO2 values", spO2);
  
 


  if (Firebase.failed()) {
     // Serial.print("pushing /SpO2 values failed:");
     // Serial.println(Firebase.error());  
      return;
  }
  }
 // Serial.print("pushed: /SpO2 values/");
 // Serial.println(name);
 // delay(1000);
 delay(2000);
}
