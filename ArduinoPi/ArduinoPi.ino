#include <Wire.h>

const int i2cAddr = 0x04;

enum State {
  WaitMode,
  WaitType,
  WaitPin,
  WaitData,
  SendData
}state;

enum Mode {
  Read = 0,
  Write = 1,
  Configure = 3
}mode;

enum Type {
  DigitalT = 0,
  AnalogT = 1,
  SerialT = 2
}type;

int pin = 0;
char serialBuf[256];
int bufWriteAddr = 0, bufReadAddr = 0;

void setup() {
  Serial.begin(9600);
  state = WaitMode;
  Wire.begin(i2cAddr);
  Wire.onReceive(recData);
  Wire.onRequest(sendData);
}

void loop() {
  delay(100);
}

void recData(int byteCount) {
  while (Wire.available()) {
    int n = Wire.read();
    switch (state) {
      case WaitMode:
        mode = n;
        state = WaitType;
        break;

      case WaitType:
        type = n;
        if (mode==Write && type==SerialT)
          state = WaitData;
        else if (type==SerialT)
          state = SendData;
        else
          state = WaitPin;
        break;

      case WaitPin:
        pin = n;
        if (mode==Write || mode==Configure)
          state = WaitData;
        else
          state = SendData;
        break;

      case WaitData:
        switch (type) {
          case DigitalT:
            if (mode==Write)
              digitalWrite(pin,n);
            else
              pinMode(pin,(n==0)?(INPUT):(OUTPUT));
            state = WaitMode;
            break;
          case AnalogT:
            if (mode==Write)
              analogWrite(pin,n);
            else
              pinMode(pin,(n==0)?(INPUT):(OUTPUT));
            state = WaitMode;
            break;
          case SerialT:
            if (n!=0)
              Serial.write(char(n));
            else
              state = WaitMode;
            break;
        }
        break;

      case SendData:
        Serial.print("Error! Received '");
        Serial.print(n);
        Serial.println("' when I was supposed to be sending data");
        break;

      default:
        Serial.println("Invalid state");
    }
  }
}

void sendData() {
  if (state!=SendData)
    Serial.println("Error! Requested for data when I'm not supposed to send anything");

  switch (type) {
    case DigitalT:
      Wire.write(digitalRead(pin));
      break;

    case AnalogT:
      Wire.write(analogRead(pin));
      break;

    case SerialT:
      if (Serial.available())
        Wire.write(Serial.read());
      else
        Wire.write(0);
      break;

    default:
      Serial.println("Error! Invalid type");
      break;
  }
}

