/* 
 * File:   Log.h
 * Author: Alberto Lepe <dev@alepe.com>
 * Created on December 1, 2015, 6:00 PM
 * This code has been copied from [https://stackoverflow.com/a/32262143/11305417]
 * Licence: CC 3.0 (as of stackoverflows terms of services [https://stackoverflow.com/help/licensing]) 
 * It has been modified to enable the use of colored and/or bold, italic and underlined text with colored background.
 */
#pragma once

#include <iostream>
#include <string>

using namespace std;

enum typeLog {
	DEBUG,
	INFO,
	WARN,
	ERROR
};

enum typeColor {
	BLACK,
	RED,
	GREEN,
	YELLOW,
	BLUE,
	MAGENTA,
	CYAN,
	WHITE,
	NONE,
	KEEPCOLOR,
};

enum typeStyle {
	DEFAULT,
	BOLD,
	ITALIC,
	UNDERLINE,
	// INVERSE,
	// BOLD_OFF,
	// UNDERLINE_OFF,
	// INVERSE_OFF
	KEEP,
};

enum customLogLine {
	BEGIN,
	END,
};

struct structlog {
	bool headers = false;
	bool stylized = false;
	typeLog level = WARN;
};

extern structlog LOGCFG;

class LOG {
public:
	LOG() {};
	LOG(typeLog type, typeColor color = NONE, typeStyle style = DEFAULT, typeColor background = NONE);
	LOG(typeLog type, customLogLine lineposition);
	~LOG();

	template <typename T>
	LOG &operator<<(const T &msg) { // how to forward-declare this? what do I put in the .cpp file???
		if(msglevel >= LOGCFG.level) {
			cout << msg;
			opened = true;
		}
		return *this;	
	}

	string color(typeColor _color = NONE, typeStyle _style = DEFAULT, typeColor _background = NONE);
	string printline(string _character = "-", uint _num = 80);

private:
	bool opened = false;
	bool keepOpen = false;
	bool stylized = false;
	typeLog msglevel = DEBUG;
	typeColor msgcolor = WHITE;
	typeColor background = NONE;
	typeStyle style = DEFAULT;
	inline string getLabel(typeLog type);
	inline string getColor(typeColor _color, typeStyle _style, typeColor _background);
};