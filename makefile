VCPATH = /opt/vc/lib
VCLIBS = $(VCPATH)/libmmal_core.so $(VCPATH)/libmmal.so $(VCPATH)/libmmal_util.so $(VCPATH)/libmmal_vc_client.so $(VCPATH)/libvcos.so $(VCPATH)/libbcm_host.so $(VCPATH)/libGLESv2.so $(VCPATH)/libEGL.so
INCLDIRS = -I/opt/vc/include
OBJFILES = obj/main.o obj/camera.o obj/cameracontrol.o obj/graphics.o obj/Arduino.o
WIRELIB = -lwiringPi
FLAGS = -std=c++11
CMDBEG = g++ $(FLAGS) $(INCLDIRS) -c

.PHONY: clean

build: $(OBJFILES)
	g++ -g $(FLAGS) -o bin/arducom $(OBJFILES) $(VCLIBS) $(WIRELIB)

clean:
	rm -f obj/*.o

obj/main.o: src/main.cpp
	$(CMDBEG) src/main.cpp -o obj/main.o

obj/camera.o: src/PiCam/camera.cpp
	$(CMDBEG) src/PiCam/camera.cpp -o obj/camera.o

obj/cameracontrol.o: src/PiCam/cameracontrol.cpp
	$(CMDBEG) src/PiCam/cameracontrol.cpp -o obj/cameracontrol.o

obj/graphics.o: src/PiCam/graphics.cpp
	$(CMDBEG) src/PiCam/graphics.cpp -o obj/graphics.o

obj/Arduino.o: src/Arduino.cpp src/Arduino.h
	$(CMDBEG) src/Arduino.cpp -o obj/Arduino.o
