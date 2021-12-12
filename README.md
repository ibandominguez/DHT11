# DHT11

Easy to use DHT11 Temperature & humidity sensor library.

## Using

```cpp
#include "DHT11.h"

DHT11 dht11(8);

void setup() {
  Serial.begin(9600);
  dht11.begin();
}

void loop() {
  dht11.read();

  Serial.print("Temperature: ");
  Serial.print(dht11.getTemperature());
  Serial.print("\tHumidity: ");
  Serial.print(dht11.getHumidity());
  Serial.print("\n");

  delay(1000);
}
```

## LICENSE

MIT
