#ifndef ARDUINO_H
#define ARDUINO_H

#include <string>

/*
 * Format of i2c communication:
 *  -Send read/write/config code
 *  -Indicate what type to read/writ/config with code
 *  -(If applicable) send pin number
 *  -Send state or string if serial
 *
 * String format:
 *  -Send chars as bytes
 *  -Send stop code when done
 *
 * Future: Define custom instruction codes to utilize the arduino processor
 */

class Arduino {
	int devId;

	const int ReadCode = 0, WriteCode = 1, ConfigureCode = 3;
	const int DigitalCode = 0, AnalogCode = 1, SerialCode = 2;
	const int InputCode = 0, OutputCode = 1;
	const int StringStopCode = 0;

public:
	Arduino(int id);

	enum Mode {
		Input = 0,
		Output = 1
	};

	void configureDigitalPin(int pin, Mode mode);
	void setDigitalPin(int pin, int value);
	int readDigitalPin(int pin);

	void configureAnalogPin(int pin, Mode mode);
	void setAnalogPin(int pin, int value);
	int readAnalogPin(int pin);

	void writeSerial(std::string s);
	std::string readSerial();
};

#endif
