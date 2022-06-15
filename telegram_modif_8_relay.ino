/*
Name:        logic solution
Created:     15/06/2022
Author:      Stefano Ledda <shurillu@tiscalinet.it>
Description: a simple example that do:
             1) parse incoming messages
             2) if "LIGHT ON" message is received, turn on the onboard LED
             3) if "LIGHT OFF" message is received, turn off the onboard LED
             4) otherwise, reply to sender with a welcome message

*/
#include <WiFiManager.h>
#include <ArduinoJson.h>
#include <EEPROM.h>

//#define TRIGGER_PIN 16


#include "CTBot.h"
CTBot myBot;
 
//String ssid  = "WiFi_ESP_Project"; 
// pass  = "logicsolution"; 
//String token = "isi token telegram";

 char telegram_token[50] = "YOUR_TELEGRAM_TOKEN";
 
 bool Start = false;
 
 bool shouldSaveConfig= false;
     
//int D1Status = 0;
//int D2Status = 2;
//int D3Status = 4;
//int D4Status = 5;
//int D5Status = 12;
//int D6Status = 13;
//int D7Status = 14;
//int D8Status = 15;
  
const int resetConfigPin = 16;                
 
void setup() {
  // initialize the Serial
  WiFi.mode(WIFI_STA);
  Serial.begin(115200);
  
  Serial.println("Starting TelegramBot...");
  initialize();
 
  // connect the ESP8266 to the desired access point
  myBot.wifiConnect(WiFi.SSID().c_str(), WiFi.psk().c_str()); 
  myBot.setTelegramToken(telegram_token);
 
  // check if all things are ok
  if (myBot.testConnection())
   Serial.println("\ntestConnection OK");
   else
   Serial.println("\ntestConnection Not.OK");
  
  pinMode(0, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(14, OUTPUT);
  pinMode(15, OUTPUT);
  
pinMode(resetConfigPin, INPUT);

  digitalWrite(0, HIGH);
  digitalWrite(2, HIGH);
  digitalWrite(4, HIGH);
  digitalWrite(5, HIGH);
  digitalWrite(12, HIGH);
  digitalWrite(13, HIGH);
  digitalWrite(14, HIGH);
  digitalWrite(15, HIGH);
      
}
 
void loop() {

  if ( digitalRead(resetConfigPin) == LOW ) {
    Serial.println("Reset");
    WiFi.disconnect();
    Serial.println("Masuk Mode AP");
    delay(500);
    ESP.reset();
    delay(5000);
  }
     Serial.begin(115200);
  
  
  // a variable to store telegram message data
  TBMessage msg;

  // if there is an incoming message...
if (myBot.getNewMessage(msg)) {
      ///////////D1//////////
     if (msg.text.equalsIgnoreCase("/D1ON")){                    //Perintah dari telegram ke perangkat
      //D1Status = 1;
      digitalWrite(0, LOW);                              
      myBot.sendMessage(msg.sender.id, "D1 is HIGH");
      }
      else if (msg.text.equalsIgnoreCase("/D1OFF")){               //Perintah dari telegram ke perangkat
      //D1Status = ;
      digitalWrite(0, HIGH);                              
      myBot.sendMessage(msg.sender.id, "D1 is LOW");
      }
      
      ///////////D2//////////
       if (msg.text.equalsIgnoreCase("/D2ON")){                    //Perintah dari telegram ke perangkat
      digitalWrite(2, LOW);                              
      myBot.sendMessage(msg.sender.id, "D2 is HIGH");
      }
       else if (msg.text.equalsIgnoreCase("/D1OFF")){               //Perintah dari telegram ke perangkat
      digitalWrite(2, HIGH);                              
      myBot.sendMessage(msg.sender.id, "D2 is LOW");
      }


       ///////////D3//////////
       if (msg.text.equalsIgnoreCase("/D3ON")){                    //Perintah dari telegram ke perangkat
      digitalWrite(4, LOW);                              
      myBot.sendMessage(msg.sender.id, "D3 is HIGH");
      }
       else if (msg.text.equalsIgnoreCase("/D3OFF")){               //Perintah dari telegram ke perangkat
      digitalWrite(4, HIGH);                              
      myBot.sendMessage(msg.sender.id, "D3 is LOW");
      }

       ///////////D4//////////
       if (msg.text.equalsIgnoreCase("/D4ON")){                    //Perintah dari telegram ke perangkat
      digitalWrite(5, LOW);                              
      myBot.sendMessage(msg.sender.id, "D4 is HIGH");
      }
       else if (msg.text.equalsIgnoreCase("/D4OFF")){               //Perintah dari telegram ke perangkat
      digitalWrite(5, HIGH);                              
      myBot.sendMessage(msg.sender.id, "D4 is LOW");
      }

       ///////////D5//////////
       if (msg.text.equalsIgnoreCase("/D5ON")){                    //Perintah dari telegram ke perangkat
      digitalWrite(12, LOW);                              
      myBot.sendMessage(msg.sender.id, "D5 is HIGH");
      }
       else if (msg.text.equalsIgnoreCase("/D5OFF")){               //Perintah dari telegram ke perangkat
      digitalWrite(12, HIGH);                              
      myBot.sendMessage(msg.sender.id, "D5 is LOW");
      }

       ///////////D6//////////
       if (msg.text.equalsIgnoreCase("/D6ON")){                    //Perintah dari telegram ke perangkat
      digitalWrite(13, LOW);                              
      myBot.sendMessage(msg.sender.id, "D6 is HIGH");
      }
       else if (msg.text.equalsIgnoreCase("/D6OFF")){               //Perintah dari telegram ke perangkat
      digitalWrite(13, HIGH);                              
      myBot.sendMessage(msg.sender.id, "D6 is LOW");
      }

       ///////////D7//////////
       if (msg.text.equalsIgnoreCase("/D7ON")){                    //Perintah dari telegram ke perangkat
      digitalWrite(14, LOW);                              
      myBot.sendMessage(msg.sender.id, "D7 is HIGH");
      }
       else if (msg.text.equalsIgnoreCase("/D7OFF")){               //Perintah dari telegram ke perangkat
      digitalWrite(14, HIGH);                              
      myBot.sendMessage(msg.sender.id, "D7 is LOW");
      }

       ///////////D8//////////
       if (msg.text.equalsIgnoreCase("/D8ON")){                    //Perintah dari telegram ke perangkat
      digitalWrite(15, LOW);                              
      myBot.sendMessage(msg.sender.id, "D8 is HIGH");
      }
       else if (msg.text.equalsIgnoreCase("/D8OFF")){               //Perintah dari telegram ke perangkat
      digitalWrite(15, HIGH);                              
      myBot.sendMessage(msg.sender.id, "D8 is LOW");
      }
///////////Perintah menyalakan semua//////////

      if (msg.text.equalsIgnoreCase ("/AllON")) {
      digitalWrite(0,LOW);
      digitalWrite(2,LOW);
        digitalWrite(4,LOW);
          digitalWrite(5,LOW);
            digitalWrite(12,LOW);
              digitalWrite(13,LOW);
                digitalWrite(14,LOW);
                  digitalWrite(15,LOW);
      
      myBot.sendMessage(msg.sender.id, "AllON is HIGH", "");
    }
///////////Perintah mematikan semua//////////
    if (msg.text.equalsIgnoreCase("/AllOFF")) {     
      digitalWrite(0,HIGH);
      digitalWrite(2,HIGH);
        digitalWrite(4,HIGH);
          digitalWrite(5,HIGH);
            digitalWrite(12,HIGH);
              digitalWrite(13,HIGH);
                digitalWrite(14,HIGH);
                digitalWrite(15,HIGH);
      myBot.sendMessage(msg.sender.id, "AllOFF is LOW", "");
    }

 if ( msg.text.equalsIgnoreCase ("/start")) {
      ///String welcome = "ESP8266 controller, " + msg.sender.username + ".\n";
      myBot.sendMessage(msg.sender.id, "Kondisi ON = /D1ON,/D2ON,/D3ON,/D4ON,/D5ON,/D6ON,/D7ON,/D8ON,/AllON", "");
      myBot.sendMessage(msg.sender.id, "Kondisi OFF = /D1OFF,/D2OFF,/D3OFF,/D4OFF,/D5OFF,/D6OFF,/D7OFF,/D8OFF,/AllOFF", "");
      
     }
      else {                                                    
      // generate the message for the sender
      String reply;
      reply = (String)"Welcome " + msg.sender.username + (String)". Cek Printah Ketik:/start .";
      myBot.sendMessage(msg.sender.id, reply); 
      }
      }
      delay(500);               
    }
 
