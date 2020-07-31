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


#define LOOP_ITERATIONS 1


typedef std::string String;


void delay(int delay);

void setup();

void loop();


class arduinoSerial {
public:
	static void begin(long baud);

	template<class C>
	void print(const C &data);

	template<class C>
	void println(const C &data);
};


template<class C>
void arduinoSerial::print(const C &data) {
	std::cout << data;
}


template<class C>
void arduinoSerial::println(const C &data) {
	std::cout << data << std::endl;
}


static arduinoSerial Serial{};

#endif //ARDUI_ARDUINO_H
