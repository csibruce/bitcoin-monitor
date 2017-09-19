#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino
#include <ESP8266HTTPClient.h>
#include <ESP8266WebServer.h>
#include <DNSServer.h>
#include <WiFiManager.h>
#include <ArduinoJson.h>

String status = "connecting";
const char* api_url[] = {"http://csibruce.iptime.org/get-price", ""};


int FIRST_LINE = 5;
int SECOND_LINE = 13;
int THIRD_LINE = 21;
int FOURTH_LINE = 23;
int FIFTH_LINE = 32;
int SIXTH_LINE = 41;
int SEVENTH_LINE = 53;

boolean titleFlag = true;

HTTPClient http;
boolean needConfigure = true;

#define OLED_RESET LED_BUILTIN
Adafruit_SSD1306 display(OLED_RESET);

#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.display();
  delay(10);


  delay(1000);
  display.drawRect(1, 1, display.width()-2, 16, WHITE);
  display.drawRect(1, 18, display.width()-2, display.height()-18, WHITE);
  display.display();


  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(4,FIRST_LINE);
  display.println(WiFi.SSID());
  display.display();
  // WiFi.disconnect(true);  // 무조건 처음부터 설정가능하게..
  Serial.println("Starting");
  Serial.println("Checking saved ssid/password");
  if(WiFi.SSID() != "") {
    WiFi.begin();
    int trycount = 0;
    while(trycount < 11) {
      Serial.println("Connecting...");
      if ((trycount%4) == 0) status = "connecting";
      setState(FIRST_LINE, status+=".", false);
      trycount++;
      delay(500);
    }

    if (trycount < 10 || (WiFi.status() == WL_CONNECTED)) {
      Serial.println("connected!!!!!");
      needConfigure = false;

      status = "SSID: ";
      status+=WiFi.SSID();
      displayTitle();
      displayKeys();
    }

    if ((trycount >= 10) || (WiFi.status() != WL_CONNECTED)) {
      status = "CONNECTION FAIL";
      WiFi.disconnect(true);
      needConfigure = true;
      displayTitle();
      delay(1000);
    }
  }

}

void displayKeys() {
  setState(FOURTH_LINE, "bithumb: ", false);
  setState(FIFTH_LINE, "coinone: ", false);
  setState(SIXTH_LINE, "korbit : ", false);
}

void displayTitle() {
  setState(FIRST_LINE, titleFlag ? status : "BITCOIN MORNITOR", false);
  titleFlag=!titleFlag;
}

void clearLine(int line = 100, boolean withDelay = false) {
  if (line == 100) return;
  display.fillRect(3, line, display.width()-6, 8, BLACK);
  if (withDelay) display.display();
}

void refreshPrice(int line, String string) {
  display.fillRect(55, line, display.width()-60, 8, BLACK);
  display.display();
  display.setCursor(55,line);
  display.setTextColor(WHITE);
  display.println(string);
  display.display();
}

void setState(int line, String string, boolean withDelay) {
  clearLine(line, withDelay);
  display.setCursor(4,line);
  display.setTextColor(WHITE);
  display.println(string);
  display.display();
}

void getPrices() {
  http.begin(api_url[0]);
  http.addHeader("Content-Type", "application/json");
  int httpCode = http.GET();
  if (httpCode > 0) {
    String payload = http.getString();
    StaticJsonBuffer<1024> JSONBuffer;
    JsonObject&  parsed= JSONBuffer.parseObject(payload);
    String korbit = parsed["korbit"];
    String bithumb = parsed["bithumb"];
    String coinone = parsed["coinone"];
    String date = parsed["date"];
    setState(SEVENTH_LINE, "      "+date, false);
    refreshPrice(FOURTH_LINE, bithumb.substring(0,8));
    refreshPrice(FIFTH_LINE, coinone.substring(0,8));
    refreshPrice(SIXTH_LINE, korbit.substring(0,8));
    Serial.println(payload);
  }
  http.end();
}


void startConfigPortal() {
    status = "SET SSID/PW";
    setState(FIRST_LINE, status, false);
    setState(FOURTH_LINE, "Find", false);
    setState(FIFTH_LINE, "AwesomeBruce", false);
    setState(SIXTH_LINE, "192.168.4.1", false);
    WiFiManager wifiManager;
    wifiManager.startConfigPortal("AwesomeBruce");
    wifiManager.setTimeout(120);
    WiFi.mode(WIFI_STA);

    //if you get here you have connected to the WiFi
    Serial.println("connected...yeey :)");
    needConfigure = false;
    status = "SSID: ";
    status+=WiFi.SSID();
    displayTitle();
    displayKeys();
}


void loop() {
  if (needConfigure) startConfigPortal();
  Serial.println(WL_CONNECTED);
  displayTitle();
  if (WiFi.status() == WL_CONNECTED) {
    getPrices();
  }
  delay(1000);
}
