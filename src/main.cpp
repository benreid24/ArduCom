#include <iostream>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include "PiCam/camera.h"
#include "PiCam/graphics.h"
#include "Arduino.h"
using namespace std;

int main() {
	cout << "Hello world!" << endl;

	if (wiringPiSetup()<0) {
		cout << "Error starting i2c service\n";
		return 1;
	}
	Arduino arduino(0x04);
	
	CCamera* cam = StartCamera(512,512,30,1,true);
	GfxTexture video;
	video.Create(512,512);

	int d;
	while (true) {
		cout << "1. Write pin\n2. Read pin\n3. Write serial\n4. Read serial\n5. Configure pin\n";
		cin >> d;

		if (d==1) {
			cout << "1. Digital\n2. Analog\n";
			cin >> d;
			int p;
			cout << "Enter pin: ";
			cin >> p;
			int v;
			cout << "Enter value: ";
			cin >> v;
			if (d==1)
				arduino.setDigitalPin(p,v);
			else
				arduino.setAnalogPin(p,v);
		}
		else if (d==2) {
			cout << "1. Digital\n2. Analog\n";
			cin >> d;
			int p;
			cout << "Pin: ";
			cin >> p;
			if (d==1)
				cout << "\nValue: " << arduino.readDigitalPin(p) << endl << endl;
			else
				cout << "\nValue: " << arduino.readAnalogPin(p) << endl << endl;
		}
		else if (d==3) {
			cout << "Enter input: ";
			string s;
			while (s.size()<=1)
				getline(cin,s);
			arduino.writeSerial(s);
		}
		else if (d==4)
			cout << "Data: " << arduino.readSerial() << endl << endl;
		else {
			cout << "1. Digital\n2. Analog\n";
			cin >> d;
			int p,m;
			cout << "Pin: ";
			cin >> p;
			cout << "1. Input\n2. Output\n";
			cin >> m;
			if (d==1) {
				if (m==1)
					arduino.configureDigitalPin(p,Arduino::Input);
				else
					arduino.configureDigitalPin(p,Arduino::Output);
			}
			else {
				if (m==1)
					arduino.configureAnalogPin(p,Arduino::Input);
				else
					arduino.configureAnalogPin(p,Arduino::Output);
			}
		}
	}

	return 0;
}
