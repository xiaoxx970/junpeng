/***************************************************
  Adafruit MQTT Library ESP8266 Example

  Must use ESP8266 Arduino from:
    https://github.com/esp8266/Arduino

  Works great with Adafruit's Huzzah ESP board & Feather
  ----> https://www.adafruit.com/product/2471
  ----> https://www.adafruit.com/products/2821

  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Tony DiCola for Adafruit Industries.
  MIT license, all text above must be included in any redistribution
 ****************************************************/
#include <ESP8266WiFi.h>
//#include <ESP8266WebServer.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

/************************* WiFi Access Point *********************************/

#define WLAN_SSID       "ljp"
#define WLAN_PASS       "18852513496"

/************************* Web Server Define *********************************/
//ESP8266WebServer server(80);

/************************* Adafruit.io Setup *********************************/

#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883                   // use 8883 for SSL
#define AIO_USERNAME    "xiaoxx"
#define AIO_KEY         "eb0927276b254479b700c2d9e94663d0"

/************ Global State (you don't need to change this!) ******************/

// Create an ESP8266 WiFiClient class to connect to the MQTT server.
WiFiClient client;
// or... use WiFiFlientSecure for SSL
//WiFiClientSecure client;

// Setup the MQTT client class by passing in the WiFi client and MQTT server and login details.
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

/****************************** Feeds ***************************************/

// Setup a feed called 'potValue' for publishing.
// Notice MQTT paths for AIO follow the form: <username>/feeds/<feedname>
Adafruit_MQTT_Publish potlight = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/ledBrightness");
Adafruit_MQTT_Publish potStatus = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/ledState");
// Setup a feed called 'ledBrightness' for subscribing to changes.
Adafruit_MQTT_Subscribe ledBrightness = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/ledBrightness");
Adafruit_MQTT_Subscribe ledStatus = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/ledState");
/*************************** Sketch Code ************************************/

// Bug workaround for Arduino 1.6.6, it seems to need a function declaration
// for some reason (only affects ESP8266, likely an arduino-builder bug).
void MQTT_connect();

const int buttonPin = 0;
const int ledPin = 2;
unsigned long duration;
int ledState = 0;
int light = 200;
bool plus = 1;

//uint8_t ledPin = 2;
uint16_t potlightVaule = 0;
uint16_t potledState = 1;


void pwm()
{
  if (digitalRead(buttonPin)) {
    ledState = 0;
    return;
  }
  plus = !plus;
  while (digitalRead(buttonPin) == LOW & light >= 10 & light <= 255) {
    Serial.println("at pwm.while");
    Serial.println(light);
    plus == 1 ? light += 2 : light -= 2;
    if (light > 255) light = 255;
    if (light < 10) light = 10;
    delay(1);
    analogWrite(ledPin, light);
  }
}

void turnOff() {
  ledState = 0;
}

void event ()
{
  delay(10);
  if (digitalRead(buttonPin) == LOW) {
    if (ledState == 1) {
      duration = pulseIn(buttonPin, LOW, 600000);
      duration == 0 ? pwm() : turnOff();
      //      Serial.print("at chenge state:");
      //      Serial.println(ledState);
      Serial.print("duration:");
      Serial.println(duration);
    }
    else {
      ledState = 1;
      //      Serial.print("at chenge state on:");
      //      Serial.println(ledState);
    }
  }

  if (ledState == 1)
    analogWrite(ledPin, light);
  else
    digitalWrite(ledPin, 0);
  while (digitalRead(buttonPin) == LOW);
}

void setup() {
  Serial.begin(9600);
  delay(10);

  Serial.println(F("Adafruit MQTT demo"));

  // Connect to WiFi access point.
  Serial.println(); Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WLAN_SSID);

  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.println("WiFi connected");
  Serial.println("IP address: "); Serial.println(WiFi.localIP());

  // Setup MQTT subscription for ledBrightness feed.
  mqtt.subscribe(&ledBrightness);
  mqtt.subscribe(&ledStatus);
}

void loop() {
  // Ensure the connection to the MQTT server is alive (this will make the first
  // connection and automatically reconnect when disconnected).  See the MQTT_connect
  // function definition further below.
  MQTT_connect();

  // this is our 'wait for incoming subscription packets' busy subloop
  // try to spend your time here

  Adafruit_MQTT_Subscribe *subscription;
  while ((subscription = mqtt.readSubscription(200))) {
    if (subscription == &ledBrightness) {
      Serial.print(F("Got LED Brightness : "));
      light = atoi((char *)ledBrightness.lastread);
      Serial.println(light);
      if (ledState == 1)
        analogWrite(ledPin, light);
    }
    if (subscription == &ledStatus) {
      Serial.print(F("Got LED Status : "));
      ledState = atoi((char *)ledStatus.lastread);
      Serial.println(ledState);
      if (ledState == 1)
        analogWrite(ledPin, light);
      else
        analogWrite(ledPin, 0);
    }
  }
  
  if (!digitalRead(buttonPin))
    event();
  if (light == 0) {
    ledState = 0;
    light = 10;
  }
  // Now we can publish stuff!
  //  uint16_t AdcValue = analogRead(0);
  if ((light > (potlightVaule + 5)) || (light < (potlightVaule - 5))) {
    potlightVaule = light;
    Serial.print(F("Sending pot val "));
    Serial.print(potlightVaule);
    Serial.print("...");
    if (! potlight.publish(potlightVaule)) {
      Serial.println(F("Failed"));
    } else {
      Serial.println(F("OK!"));
    }
  }
  if (ledState == !potledState) {
    potledState = ledState;
    Serial.print(F("Sending switch val "));
    Serial.print(potledState);
    Serial.print("...");
    if (! potStatus.publish(potledState)) {
      Serial.println(F("Failed"));
    } else {
      Serial.println(F("OK!"));
    }
  }
  // ping the server to keep the mqtt connection alive
  // NOT required if you are publishing once every KEEPALIVE seconds
  /*
    if(! mqtt.ping()) {
    mqtt.disconnect();
    }
  */
}

// Function to connect and reconnect as necessary to the MQTT server.
// Should be called in the loop function and it will take care if connecting.
void MQTT_connect() {
  int8_t ret;

  // Stop if already connected.
  if (mqtt.connected()) {
    return;
  }

  Serial.print("Connecting to MQTT... ");

  uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
    Serial.println(mqtt.connectErrorString(ret));
    Serial.println("Retrying MQTT connection in 5 seconds...");
    mqtt.disconnect();
    delay(5000);  // wait 5 seconds
    retries--;
    if (retries == 0) {
      // basically die and wait for WDT to reset me
      while (1);
    }
  }
  Serial.println("MQTT Connected!");
}
