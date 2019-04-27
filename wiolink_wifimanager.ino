#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino

//needed for library
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>         //https://github.com/tzapu/WiFiManager

#include <Bounce2.h>

#define LED_PIN 14
#define BUTTON_PIN 12

// Instantiate a Bounce object
Bounce debouncer = Bounce(); 

void setup() {
    // put your setup code here, to run once:
    Serial.begin(115200);

    //WiFiManager
    //Local intialization. Once its business is done, there is no need to keep it around
    WiFiManager wifiManager;
    //reset saved settings
    //wifiManager.resetSettings();
    
    //set custom ip for portal
    //wifiManager.setAPStaticIPConfig(IPAddress(10,0,1,1), IPAddress(10,0,1,1), IPAddress(255,255,255,0));

    //fetches ssid and pass from eeprom and tries to connect
    //if it does not connect it starts an access point with the specified name
    //here  "AutoConnectAP"
    //and goes into a blocking loop awaiting configuration
    //or use this for auto generated name ESP + ChipID
    wifiManager.autoConnect();
    
    //if you get here you have connected to the WiFi
    Serial.println("connected...yeey :)");

    // Enable digital pins
    pinMode(15, OUTPUT);
    digitalWrite(15, 1);
  
    // Setup the first button with an internal pull-up :
    pinMode(BUTTON_PIN, INPUT_PULLUP);
    // After setting up the button, setup the Bounce instance :
    debouncer.attach(BUTTON_PIN);
    debouncer.interval(5); // interval in ms
    
    pinMode(LED_PIN, OUTPUT);
    
}

void loop() {
    debouncer.update();
  
    // Get the updated value :
    int value = debouncer.read();

    // Turn on the LED if either button is pressed :
    if ( value == LOW) {
        digitalWrite(LED_PIN, HIGH);
    } else {
        digitalWrite(LED_PIN, LOW);
    }  
}
