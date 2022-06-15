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
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include "CTBot.h"

#include <EEPROM.h>
#include <DNSServer.h>            //Local DNS Server used for redirecting all rs to the configuration portal
#include <ESP8266WebServer.h>     //Local WebServer used to serve the configuration portal
#include <WiFiManager.h> 

#define BOT_TOKEN_LENGTH 50
//String ssid = "mySSID";     // REPLACE mySSID WITH YOUR WIFI SSID
//String pass = "myPassword"; // REPLACE myPassword YOUR WIFI PASSWORD, IF ANY
//String token = "myToken";   // REPLACE myToken WITH YOUR TELEGRAM BOT TOKEN
//uint8_t led = 2;            // the onboard ESP8266 LED.    
                            // If you have a NodeMCU you can use the BUILTIN_LED pin
                            // (replace 2 with BUILTIN_LED)							
//const int ledPin = 2;
const int D1Status = 0;
const int D2Status = 2;
const int D3Status = 4;
const int D4Status = 5;
const int D5Status = 12;
const int D6Status = 13;
const int D7Status = 14;
const int D8Status = 15;
const int resetConfigPin = 16; //When high will reset the wifi manager config

char botToken[BOT_TOKEN_LENGTH] = "";

WiFiClientSecure client;
CTBot myBot;
int Bot_mtbs = 1000; //mean time between scan messages
long Bot_lasttime;   //last time messages' scan has been done
bool Start = false;
//int ledStatus = 0;

//flag for saving data
bool shouldSaveConfig = false;

//callback notifying us of the need to save config
void saveConfigCallback () {
  Serial.println("Should save config");
  shouldSaveConfig = true;
}

void readBotTokenFromEeprom(int offset){
  for(int i = offset; i<BOT_TOKEN_LENGTH; i++ ){
    botToken[i] = EEPROM.read(i);
  }
  EEPROM.commit();

}

void writeBotTokenToEeprom(int offset){
  for(int i = offset; i<BOT_TOKEN_LENGTH; i++ ){
    EEPROM.write(i, botToken[i]);
  }
  EEPROM.commit();
}

void setup() {
	// initialize the Serial
	 EEPROM.begin(BOT_TOKEN_LENGTH);
  pinMode(resetConfigPin, INPUT);
  //pinMode(ledPin, OUTPUT); // initialize digital ledPin as an output.
  pinMode(0, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(14, OUTPUT);
  pinMode(15, OUTPUT);
  delay(10);
  //digitalWrite(ledPin, LOW); // initialize pin as off
  digitalWrite(0, HIGH);
  digitalWrite(2, HIGH);
  digitalWrite(4, HIGH);
  digitalWrite(5, HIGH);
  digitalWrite(12, HIGH);
  digitalWrite(13, HIGH);
  digitalWrite(14, HIGH);
  digitalWrite(15, HIGH);

  Serial.println("read bot token");
  readBotTokenFromEeprom(0);
  Serial.println(botToken);

  WiFiManager wifiManager;
  wifiManager.setSaveConfigCallback(saveConfigCallback);
  //Adding an additional config on the WIFI manager webpage for the bot token
  WiFiManagerParameter custom_bot_id("botid", "Bot Token", botToken, 50);
  wifiManager.addParameter(&custom_bot_id);
  //If it fails to connect it will create a TELEGRAM-BOT access point
  wifiManager.autoConnect("TELEGRAM-BOT");

  strcpy(botToken, custom_bot_id.getValue());
  if (shouldSaveConfig) {
    writeBotTokenToEeprom(0);
    readBotTokenFromEeprom(0);
    
  }
//readBotTokenFromEeprom(0);
  myBot.setTelegramToken(botToken);
  //myBot = new setTelegramToken(botToken);
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  IPAddress ip = WiFi.localIP();
  Serial.println(ip);



	//myBot.wifiConnect(ssid, pass);

	// set the telegram bot token
	//myBot.setTelegramToken(token);

	// check if all things are ok
//	if (myBot.testConnection())
	//	Serial.println("\ntestConnection OK");
	//else
	//	Serial.println("\ntestConnection NOK");

	// set the pin connected to the LED to act as output pin
	//pinMode(ledPin, OUTPUT);
	//digitalWrite(ledPin, HIGH); // turn off the led (inverted logic!)

}

void loop() {
  Serial.begin(115200);
   if ( digitalRead(resetConfigPin) == LOW ) {
    Serial.println("Reset");
    WiFi.disconnect();
    Serial.println("Dq");
    delay(500);
    ESP.reset();
    delay(5000);
  }
	// a variable to store telegram message data
	TBMessage msg;

	// if there is an incoming message...
	if (CTBotMessageText == myBot.getNewMessage(msg)) {

		/*if (msg.text.equalsIgnoreCase("LIGHT ON")) {              // if the received message is "LIGHT ON"...
			digitalWrite(ledPin, LOW);                               // turn on the LED (inverted logic!)
			myBot.sendMessage(msg.sender.id, "Light is now ON");  // notify the sender
		}
		else if (msg.text.equalsIgnoreCase("LIGHT OFF")) {        // if the received message is "LIGHT OFF"...
			digitalWrite(ledPin, HIGH);                              // turn off the led (inverted logic!)
			myBot.sendMessage(msg.sender.id, "Light is now OFF"); // notify the sender
		}
		else {                                                    // otherwise...
			// generate the message for the sender
			String reply;
			reply = (String)"Welcome " + msg.sender.username + (String)". Try LIGHT ON or LIGHT OFF.";
			myBot.sendMessage(msg.sender.id, reply);             // and send it
		}
   */
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
      //digitalWrite(16,LOW);
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
      //digitalWrite(16,HIGH);
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
	// wait 500 milliseconds
	delay(500);
}
