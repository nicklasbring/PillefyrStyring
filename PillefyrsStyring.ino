/********************************************************************/
//Inkluder biblioteker
#include <OneWire.h>
#include <DallasTemperature.h>
#include <SoftwareSerial.h>
/********************************************************************/
//Temperatur sensor er tilsuttet port 9
#define ONE_WIRE_BUS 9
//TX og RX til gsm modul er tilsuttet port 7 0g 8
SoftwareSerial SIM900(7, 8);
/********************************************************************/
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensor(&oneWire);
int relay = 6;
/********************************************************************/
//String som indeholder text beskeden
String textMessage;

//boolean til at vide om fyret har genstartet siden sidst det var under 30 grader
bool hasRestarted = false;

void setup(){
  Serial.begin(19200);
  SIM900.begin(19200);
  sensor.begin();
  pinMode(relay, OUTPUT);
  digitalWrite(relay, HIGH);
  Serial.println("Pilefyr Styring 1.0");
  //delay inden opkoblingen på gsm netværket
  delay(10000);

  Serial.print("GSM modul er klart...");

  // AT kommando der sætter modulet til sms mode
  SIM900.print("AT+CMGF=1\r"); 
  delay(100); 
  SIM900.print("AT+CNMI=2,2,0,0,0\r");
  delay(100);
}

void loop(void){
  //Kører processen som læser inkommende beskeder
  modtagSms();

  //Kommando for at modtage temperaturmålinger og udskrive dem
  sensor.requestTemperatures(); 
  double temp = sensor.getTempCByIndex(0);
  Serial.print(String("\nTempereatur = ") + temp);

    // tjekker om fyret har været genstarted siden det var under 30 grader
    if(temp >= 40 && hasRestarted == true){
      hasRestarted = false;
    }

    //If statement som skal sende en besked når fyret går ud. 
    //Temperaturen vil blive ændret. Mere så jeg har noget at teste med
    if (temp <= 40 && hasRestarted == false) {
      sendSms("Fyret er slukket! \nTast 'genstart' for at genstarte");
      Serial.println("\nSMS er sendt!");
      hasRestarted = true; // retter bool så systemet ved at fyret er blevet genstartet
    }
  delay(5000);
}


//Metode til at modtage en sms
void modtagSms (){
if(SIM900.available()>0){
    textMessage = SIM900.readString();
    Serial.print(textMessage);    
    delay(10);
  }

  //Hvis komandoen "genstart" bliver skrevet, starter den servoen
  if(textMessage.indexOf("genstart")>=0){
    Serial.println("Genstarter fyret");  
    sendSms("Fyret Genstarter");
    digitalWrite(relay, LOW);
    delay(10000);
    digitalWrite(relay, HIGH);
    textMessage = "";   
  }

  //Hvis komandoen "status" bliver skrevet, sender den temperaturen på sms
  if(textMessage.indexOf("status")>=0){
    Serial.println("Status Sendt");  
    double temp = sensor.getTempCByIndex(0);
    Serial.print(String("\nTempereatur = ") + temp);
    sendSms(String("Temperatur = ") + temp);      
    textMessage = "";   
  }
}

//Metode der sender besked tilbage
void sendSms(String message){
  SIM900.print("AT+CMGF=1\r"); 
  delay(100);

  SIM900.println("AT+CMGS=\"25726666\""); 
  delay(100);
  // Send the SMS
  SIM900.println(message); 
  delay(100);

  SIM900.println((char)26); 
  delay(100);
  SIM900.println();
  // Give module time to send SMS
  delay(5000);
}
