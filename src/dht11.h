#include "Arduino.h"

#ifndef DHT11_h
#define DHT11_h

class DHT11 {
  public:
    /**
     * @param int
     * @return DHT11
     */
    DHT11(int configPin)  {
      pin = configPin;
    }

    /**
     * @return void
     */
    void begin() {
      pinMode(pin, OUTPUT);
    }

    /**
     * @return void
     */
    void read() {
      digitalWrite(pin, LOW); //Pull down the bus to send the start signal
      delay(30); //The delay is greater than 18 ms so that DHT 11 can detect the start signal
      digitalWrite(pin, HIGH);
      delayMicroseconds(40); //Wait for DHT11 to respond
      pinMode(pin, INPUT);
      while (digitalRead(pin) == HIGH);
      delayMicroseconds(80); //The DHT11 responds by pulling the bus low for 80us;

      // DHT11 pulled up after the bus 80us to start sending data;
      if (digitalRead(pin) == LOW) {
        delayMicroseconds(80);
      }

      // Receiving temperature and humidity data, check bits are not considered;
      for (int dataIndex = 0; dataIndex < 5; dataIndex++) {
        byte bit = 0;
        byte result = 0;

        for (bit = 0; bit < 8; bit++) {
          while (digitalRead(pin) == LOW); // wait 50us
          delayMicroseconds(30); // The duration of the high level is judged to determine whether the data is '0' or '1'
          if (digitalRead(pin) == HIGH) result |= (1 << (8 - bit)); // High in the former, low in the post
          while (digitalRead(pin) == HIGH); //Data '1', waiting for the next bit of reception
        }

        data[dataIndex] = result;
      }

      pinMode(pin, OUTPUT);
      digitalWrite(pin, HIGH); //After the completion of a release of data bus, waiting for the host to start the next signal
    }

    /**
     * @return float
     */
    float getTemperature() {
      String integerPart = String(data[2], DEC);
      String decimalPart = String(data[3], DEC);
      return String(integerPart + "." + decimalPart).toFloat();
    }

    /**
     * @return float
     */
    float getHumidity() {
      String integerPart = String(data[0], DEC);
      String decimalPart = String(data[1], DEC);
      return String(integerPart + "." + decimalPart).toFloat();
    }

  private:
    int pin;
    byte data[5];
};

#endif
