## Bitcoin-monitor ESP8266 ARDUINO

![alt text](screenshot/bitcoin-monitor.gif "Bitcoin-monitor")

### used api i made

- [bitcoin-api](https://github.com/csibruce/bitcoin-api)

### library list

- [Adafruit_GFX](https://github.com/adafruit/Adafruit-GFX-Library)

- [Adafruit_SSD1306](https://github.com/adafruit/Adafruit_SSD1306)

- [ESP8266WiFi](https://github.com/esp8266/Arduino)

- [ESP8266HTTPClient](https://github.com/esp8266/Arduino)

- [ArduinoJson](https://github.com/bblanchon/ArduinoJson)

#### changed i2c pins

```arduino
// I2C Init
Wire.begin(0,2); // FIXME changed i2c pins for esp8266 [default => Wire.begin()]
```
