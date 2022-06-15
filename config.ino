void saveConfigCallback () {
  Serial.println(F("Should save config"));
  shouldSaveConfig = true;
}
/*
void readBotTokenFromEeprom(int offset){
  for(int i = offset; i<BOT_TOKEN_LENGTH; i++ ){
    telegram_token[i] = EEPROM.read(i);
  }
  EEPROM.commit();
}

void writeBotTokenToEeprom(int offset){
  for(int i = offset; i<BOT_TOKEN_LENGTH; i++ ){
    EEPROM.write(i, telegram_token[i]);
  }
  EEPROM.commit();
}
*/

void initSPIFFS() {
  //read token from FS
  Serial.println(F("mounting FS..."));
  if (SPIFFS.begin()) {
    Serial.println(F("mounted file system"));
    if (SPIFFS.exists("/token.txt")) {
      //file exists, reading and loading
      Serial.println(F("reading config file"));
      File configFile = SPIFFS.open("/token.txt", "r");
      if (configFile) {
        Serial.print(F("opened config file")); 
        while(configFile.available()) 
        {
          //read line by line from the file
          String line = configFile.readStringUntil('\n');
        
          strcpy(telegram_token, line.c_str());
          //myBot.setTelegramToken(telegram_token);
          Serial.println(F(" success"));
        } 
      } else {
         Serial.println(F("failed to load token"));
      }

      configFile.close();
    }
  }
   else {
    Serial.println(F("failed to mount FS"));
  }
}

void saveToken() {
    Serial.println("saving config");
    File configFile = SPIFFS.open("/token.txt", "w");
    if (!configFile) 
    {
      Serial.println("file creation failed");
     
    } else {
      Serial.println("File Created!");
      configFile.println(telegram_token);  
        
    }
    configFile.close();
}

void initialize(){
  
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println();
  
  //clean FS, for testing
  SPIFFS.format();

initSPIFFS();
 
 // saveConfigCallback ()

 
 WiFiManager wifiManager;
 wifiManager.setSaveConfigCallback(saveConfigCallback);
 WiFiManagerParameter custom_telegram_token("telegram", "telegram token", telegram_token, 50);
   
  
  wifiManager.addParameter(&custom_telegram_token);

    //if (!wifiManager.autoConnect("AutoConnectAP","password")) {
      //if (!wifiManager.startConfigPortal("AutoConnectAP")) {
    if (!wifiManager.autoConnect("AutoConnectAP")) {
  
  //saveToken();
  //saveConfigCallback ();  
   
    Serial.println("failed to connect and hit timeout");
    delay(3000);
    //reset and try again, or maybe put it to deep sleep
    ESP.reset();
    delay(5000);
    
  }

  Serial.println("anda Tersambung...yeey :)");
  strcpy(telegram_token, custom_telegram_token.getValue());

  //save the custom parameters to FS
  if (shouldSaveConfig) {
    saveToken();

    
    
  }
  
}
