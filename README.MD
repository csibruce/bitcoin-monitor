## Bitcoin-monitor ESP8266 ARDUINO

![alt text](screenshot/bitcoin-monitor.gif "Bitcoin-monitor")

### used api i made

- [bitcoin-api](https://github.com/csibruce/bitcoin-api)

### library list

- Adafruit_GFX

- Adafruit_SSD1306

- ESP8266WiFi

- ESP8266HTTPClient

- ArduinoJson

#### changed i2c pins

```arduino
// I2C Init
Wire.begin(0,2); // FIXME changed i2c pins for esp8266 [default => Wire.begin()]
```
