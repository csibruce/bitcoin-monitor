## Bitcoin-monigor ESP8266 ARDUINO

![alt text](screenshot/bitcoin-monitor.gif "Bitcoin-monitor")

changed i2c pins

```arduino
// I2C Init
Wire.begin(0,2); // FIXME changed i2c pins for esp8266 [default => Wire.begin()]
```
