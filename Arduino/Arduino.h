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
#include <chrono>
#include <ctime>


#ifdef _WIN32

	#include "Windows.h"

#else

	#include <unistd.h>

#endif


#define LOOP_ITERATIONS 3
#define DEC 1
#define HEX 2

typedef std::string String;

#if defined(__EMSCRIPTEN__) && defined(__cplusplus)
extern "C" {
#endif
void setup();

void loop();
#if defined(__EMSCRIPTEN__) && defined(__cplusplus)
}
#endif

void delay(uint32_t ms);

uint32_t millis();


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
static auto ProgramStartupTime {std::chrono::system_clock::now()};

#endif //ARDUI_ARDUINO_H
