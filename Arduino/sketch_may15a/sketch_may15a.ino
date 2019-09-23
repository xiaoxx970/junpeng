#include "SSD1306Wire.h"
#include "EEPROM.h"
#define SDA 2
#define SCL 15

#define EEPROM_SIZE 64
SSD1306Wire display(0x3c, SDA, SCL);

int address = 0;
void setup() {
  Serial.begin(115200);
  Serial.println("start...");
  if (!EEPROM.begin(EEPROM_SIZE))
  {
    Serial.println("failed to initialise EEPROM"); delay(1000000);
  }
  Serial.println(" bytes read from Flash . Values are:");
  for (int i = 0; i < EEPROM_SIZE; i++)
  {
    Serial.print(EEPROM.read(i)); Serial.print(" ");
  }
  Serial.println();
  //  Serial.println("writing 0. in memory");
  //  int val = byte(0);
  //  for (int i = 0; i < EEPROM_SIZE; i++)
  //  {
  //    EEPROM.write(i, val);
  //    Serial.print(val); Serial.print(" ");
  //  }
  display.init();
  display.flipScreenVertically();
  display.setContrast(255);
  display.clear();
  display.setLogBuffer(5, 30);
  // Some test data
  const char* test[] = {
    "Hello",
    "World" ,
    "----",
    "Show off",
    "how",
    "the log buffer",
    "is",
    "working.",
    "Even",
    "scrolling is",
    "working"
  };
  char ssid[] = "ljp";
  //EEPROM.writeString(address, ssid);
  char pwd[] = "18852513496";
  //EEPROM.writeString(address + sizeof(ssid), pwd);
  //EEPROM.commit();
  Serial.println(sizeof(ssid));
  Serial.println(sizeof(pwd));
  uint16_t len;
  char ssid_r[sizeof(ssid)];
  for (len = 0; len < sizeof(ssid); len++)
    ssid_r[len] = char(EEPROM.readChar(len));

  //String ssid_r = String(EEPROM.read(address));
  String pwd_r = EEPROM.readString(address + sizeof(ssid));
  //Serial.println(EEPROM.readString(sizeof(ssid)));
  Serial.println(ssid_r);
  Serial.println(pwd_r);
  display.clear();
  // Print to the screen
  display.println(ssid_r);
  display.println(pwd_r);
  // Draw it to the internal screen buffer
  display.drawLogBuffer(0, 0);
  // Display it on the screen
  display.display();
  delay(500);


}

void loop() {
  // put your main code here, to run repeatedly:

}
