#include "Arduino.h"
#include <wiringPi.h>
#include <wiringPiI2C.h>
using namespace std;

Arduino::Arduino(int id) {
	devId = wiringPiI2CSetup(id);
}

void Arduino::configureDigitalPin(int pin, Mode mode) {
	wiringPiI2CWrite(devId,ConfigureCode);
	wiringPiI2CWrite(devId,DigitalCode);
	wiringPiI2CWrite(devId,pin);
	wiringPiI2CWrite(devId,mode);
}

void Arduino::setDigitalPin(int pin, int value) {
	wiringPiI2CWrite(devId,WriteCode);
        wiringPiI2CWrite(devId,DigitalCode);
        wiringPiI2CWrite(devId,pin);
	wiringPiI2CWrite(devId,value);
}

int Arduino::readDigitalPin(int pin) {
	wiringPiI2CWrite(devId,ReadCode);
	wiringPiI2CWrite(devId,DigitalCode);
	wiringPiI2CWrite(devId,pin);
	return wiringPiI2CRead(devId);
}

void Arduino::configureAnalogPin(int pin, Mode mode) {
	wiringPiI2CWrite(devId,ConfigureCode);
	wiringPiI2CWrite(devId,AnalogCode);
	wiringPiI2CWrite(devId,pin);
	wiringPiI2CWrite(devId,mode);
}

void Arduino::setAnalogPin(int pin, int value) {
	wiringPiI2CWrite(devId,WriteCode);
	wiringPiI2CWrite(devId,AnalogCode);
	wiringPiI2CWrite(devId,pin);
	wiringPiI2CWrite(devId,value);
}

int Arduino::readAnalogPin(int pin) {
	wiringPiI2CWrite(devId,ReadCode);
	wiringPiI2CWrite(devId,AnalogCode);
	wiringPiI2CWrite(devId,pin);
	return wiringPiI2CRead(devId);
}

void Arduino::writeSerial(string s) {
	wiringPiI2CWrite(devId,WriteCode);
	wiringPiI2CWrite(devId,SerialCode);
	for (unsigned int i = 0; i<s.size(); ++i) {
		wiringPiI2CWrite(devId,s[i]);
	}
	wiringPiI2CWrite(devId,StringStopCode);
}

string Arduino::readSerial() {
	wiringPiI2CWrite(devId,ReadCode);
	wiringPiI2CWrite(devId,SerialCode);
	string r;
	int c;
	while (true) {
		c = wiringPiI2CRead(devId);
		if (c!=StringStopCode)
			r.push_back(char(c));
		else
			break;
	}
	return r;
}

