#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define BLYNK_TEMPLATE_ID "TMPLpO-fr9E3"
#define BLYNK_TEMPLATE_NAME "Smart Home"
#define BLYNK_AUTH_TOKEN "ULyFtzosDq6dZj8BDvHxvFpk0lY1Fh9F"

char auth[] = "ULyFtzosDq6dZj8BDvHxvFpk0lY1Fh9F";
char ssid[] = "Sonu2005";//Enter your WIFI name
char pass[] = "balaghat";//Enter your WIFI password

bool fetch_blynk_state = true;
#define RelayPin1 5  //D1
#define RelayPin2 4  //D2
#define RelayPin3 0  //D3
#define RelayPin4 2  //D4
#define V_1 V1 //D1
#define V_2 V2 //D2
#define V_3 V3 //D3
#define V_4 V4 //D4
#define V_5 V5
#define V_6 V6
#define V_7 V7
bool toggleState_1 = LOW; //for relay 1
bool toggleState_2 = LOW; //for relay 2
bool toggleState_3 = LOW; //for relay 3
bool toggleState_4 = LOW; //for relay 4

const int trigPin = 12;
const int echoPin = 14;
const int irPin = 13;



//define sound velocity in cm/uS
#define SOUND_VELOCITY 0.034
#define CM_TO_INCH 0.393701

long duration;
float distanceCm;
float distanceInch;
int senON=0;
int irval=1;

BlynkTimer timer;
//int wifiFlag = 1;
void checkBlynkStatus() 
{ // called every 2 seconds by SimpleTimer
  bool isconnected = Blynk.connected();
  if (isconnected == false) 
  {
    //wifiFlag = 1;
    Serial.println("Blynk Not Connected");    
  }
  if (isconnected == true) 
  {
    //wifiFlag = 0;
////////////////////////////////////////////////
    if (!fetch_blynk_state){
    Blynk.virtualWrite(V_1, toggleState_1);
    Blynk.virtualWrite(V_2, toggleState_2);
    Blynk.virtualWrite(V_3, toggleState_3);
    Blynk.virtualWrite(V_4, toggleState_4);
    }
////////////////////////////////////////////////
    Serial.println("Blynk Connected");
    //tym();    
  }
}

/////////////////////////////////////////////
BLYNK_CONNECTED() {
  // Request the latest state from the server
  if (fetch_blynk_state){
    Blynk.syncVirtual(V_1);
    Blynk.syncVirtual(V_2);
    Blynk.syncVirtual(V_3);
    Blynk.syncVirtual(V_4);
  }    
}

BLYNK_WRITE(V_1) {
  
  toggleState_1 = param.asInt();
  digitalWrite(RelayPin1, !toggleState_1);
}

BLYNK_WRITE(V_2) {
  
  toggleState_2 = param.asInt();
  digitalWrite(RelayPin2, !toggleState_2);
}

BLYNK_WRITE(V_3) {
  
  toggleState_3 = param.asInt();
  digitalWrite(RelayPin3, !toggleState_3);
}

BLYNK_WRITE(V_4) {
  
  toggleState_4 = param.asInt();
  digitalWrite(RelayPin4, !toggleState_4);
}

BLYNK_WRITE(V_6) {
  senON = param.asInt();
}

void all_SwitchOff(){
  toggleState_1 = 0; digitalWrite(RelayPin1, HIGH); 
  Blynk.virtualWrite(V_1, toggleState_1); delay(100);

  toggleState_2 = 0; digitalWrite(RelayPin2, HIGH); 
  Blynk.virtualWrite(V_2, toggleState_2); delay(100);

  toggleState_3 = 0; digitalWrite(RelayPin3, HIGH); 
  Blynk.virtualWrite(V_3, toggleState_3); delay(100);

  toggleState_4 = 0; digitalWrite(RelayPin4, HIGH); 
  Blynk.virtualWrite(V_4, toggleState_4); delay(100);
}
////////////////////////////////////////////

BLYNK_WRITE(V0) {
   all_SwitchOff();
}


void setup() {
  // put your setup code here, to run once:
  //Set the LED pin as an output pin
  Serial.begin(9600);
  //Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
  WiFi.begin(ssid, pass);
  timer.setInterval(2000L, checkBlynkStatus);
  // check if Blynk server is connected every 10 seconds  
  Blynk.config(auth);
  //delay(1000);

/////////////////////////////////////////////
  pinMode(RelayPin1, OUTPUT);
  pinMode(RelayPin2, OUTPUT);
  pinMode(RelayPin3, OUTPUT);
  pinMode(RelayPin4, OUTPUT);
  digitalWrite(RelayPin1, !toggleState_1);
  digitalWrite(RelayPin2, !toggleState_2);
  digitalWrite(RelayPin3, !toggleState_3);
  digitalWrite(RelayPin4, !toggleState_4);
  if (!fetch_blynk_state){
    Blynk.virtualWrite(V_1, toggleState_1);
    Blynk.virtualWrite(V_2, toggleState_2);
    Blynk.virtualWrite(V_3, toggleState_3);
    Blynk.virtualWrite(V_4, toggleState_4);
  }

  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT);
  pinMode(irPin, INPUT); 
}

void loop() {
  // put your main code here, to run repeatedly:
  Blynk.run();
  timer.run();
   
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
    irval = digitalRead(irPin);
    Serial.println(irval); 
    Blynk.virtualWrite(V_7,irval);
    duration = pulseIn(echoPin, HIGH);
    distanceCm = duration * SOUND_VELOCITY/2; 
    Serial.println(distanceCm); 
    Blynk.virtualWrite(V_5,distanceCm);
    delay(1000);
  if(senON==1)
  {
   if( irval==0 )
    {
      Serial.println("Theft Detected !!!!!");
      //Blynk.logEvent("theft","Thief In The House !!!");
      //digitalWrite(ledPin,HIGH);
      digitalWrite(RelayPin1, 0);
      Blynk.virtualWrite(V_1,1);
      delay(5000);
    } 

  }
  
}
