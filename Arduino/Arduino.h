//
// Created by MStefan99 on 17.12.19.
//

#ifndef ARDUI_ARDUINO_H
#define ARDUI_ARDUINO_H


#include <iostream>
#include <cstdio>
#include <cstdint>
#include <ctime>
#include <string>
#include <unistd.h>


#define LOOP_ITERATIONS 3
#define DEC 1
#define HEX 2

typedef std::string String;


void delay(int ms);

uint16_t millis();

void setup();

void loop();


class ArduinoSerial {
public:
	void begin(long baud);

	template <class C>
	void print(const C& data, int type = DEC);

	template <class C>
	void println(const C& data, int type = DEC);
};


template <class C>
void ArduinoSerial::print(const C& data, int type) {
	switch (type) {
		case DEC:
		default:
			std::cout << std::dec;
			break;
		case HEX:
			std::cout << std::hex;
			break;
	}
	std::cout << data;
}


template <class C>
void ArduinoSerial::println(const C& data, int type) {
	print(data, type);
	std::cout << std::endl;
}


static ArduinoSerial Serial {};

#endif //ARDUI_ARDUINO_H
