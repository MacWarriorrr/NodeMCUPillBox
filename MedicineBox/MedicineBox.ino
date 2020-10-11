#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
#include <Servo.h> //Servo library
//Include Firebase ESP8266 library
#include "FirebaseESP8266.h"
//Include ESP8266WiFi.h
#include <ESP8266WiFi.h>

SoftwareSerial mySoftwareSerial(10, 11); // RX, TX
DFRobotDFPlayerMini myDFPlayer;

FirebaseData firebaseData;
Servo myservo; // servo object to control a servo

int pos=90; // variable to store the servo position
int rotate=10 //variable to store the servo rotation time

const int buttonPin = 2; // the number of the pushbutton pin
int buttonState = 0; //variable for reading the pushbutton status

void begin(const String &host, const String &auth = "")
String pushInt(const String &path, int value)

void setup() {
  //Setup Firebase credential in setup:
  Firebase.begin(".firebase.com","");

  //Setup of music:
  mySoftwareSerial.begin(9600);
  
  if (!myDFPlayer.begin(mySoftwareSerial)) {  //Use softwareSerial to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while(true);
  }
  myDFPlayer.volume(15);
  
  // initialize serial communication:
  Serial.begin(115200);
  
  // attaches the servo on pin 8 to the servo object
  myservo.attach(8);
  
  //initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);

}

void loop() {
  
  // Check value from database to see if medicine needs to be taken
  if (Firebase.getInt(firebaseData, )){
    if (firebaseData.dataType() == "int"){
      med = firebase.intData();
    }
  } else {
    Serial.println(firebaseData.errorReason());
  }
  // read value from app database to know if medicine needs to be taken and play music.
  if (med=1) {
    myDFPlayer.play(1)
  }


  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);


  //Activate motor when button is pressed and app gives a signal to
  if (buttonState == HIGH and med == 1) {
    myservo.write(pos);           // tell servo to go to rotate at speed written in variable 'pos'
    delay(rotate);                // the servo will continue to rotate at this speed for 'rotate' seconds
    
  }



  delay(5);                //delay in between for stability
}
