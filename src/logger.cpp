#include "../include/constants.hpp"
#include "../include/logger.hpp"

using namespace std;

LOG::LOG(typeLog type, typeColor color, typeStyle style, typeColor background) {
	msglevel = type;
	if(LOGCFG.headers) {
		operator << ("["+getLabel(type)+"] ");
	}
	if(color != NONE || style != DEFAULT || background != NONE) {
		operator << (getColor(color, style, background));
	}
}

LOG::LOG(typeLog type, customLogLine lineposition) {
	if(msglevel < LOGCFG.level) return;
	if (lineposition == BEGIN) {
		keepOpen = true;
	}
	if (lineposition == END) {
		keepOpen = false;
		if (stylized) {
			cout << "\033[0;39;49m";
			stylized = false;
		}
		opened = false;
		cout << '\n';
	}
}

LOG::~LOG() {
	if (stylized) {
		cout << "\033[0;39;49m";
	}
	stylized = false;
	if (keepOpen) return;
	// cout << "...";
	if (opened) {
		cout << '\n';
		opened = false;
	}
}

string LOG::color(typeColor _color, typeStyle _style, typeColor _background) {
	// if (!stylized && (_color != NONE || _style != DEFAULT || _background != NONE)) stylized = true;
	return getColor(_color, _style, _background);
}

inline string LOG::getLabel(typeLog type) {
	string label;
	switch(type) {
		case DEBUG: label = "DEBUG"; break;
		case INFO:  label = "INFO"; break;
		case WARN:  label = "WARN"; break;
		case ERROR: label = "ERROR"; break;
	}
	return label;
}

inline string LOG::getColor(typeColor _color, typeStyle _style, typeColor _background) {
	if (_color == KEEPCOLOR || _style == KEEP || _background == KEEPCOLOR) {
		return "";
	}
	stylized = true;
	string s = "\033[";
	switch(_style) {
		case DEFAULT: s += "0"; break;
		case BOLD: s += "1"; break;
		case ITALIC: s += "3"; break;
		case UNDERLINE: s += "4"; break;
		// case INVERSE: style += "7"; break;
		// case BOLD_OFF: style += "21"; break;
		// case UNDERLINE_OFF: style += "24"; break;
		// case INVERSE_OFF: style += "27"; break;
		case KEEP: break;
	}
	switch(_color) {
		case BLACK: s += ";30"; break;
		case RED: s += ";31"; break;
		case GREEN: s += ";32"; break;
		case YELLOW: s += ";33"; break;
		case BLUE: s += ";34"; break;
		case MAGENTA: s += ";35"; break;
		case CYAN: s += ";36"; break;
		case WHITE: s += ";37"; break;
		case NONE: s += ";39"; break;
		case KEEPCOLOR: break;
	}
	switch(_background) {
		case BLACK: s += ";40"; break;
		case RED: s += ";41"; break;
		case GREEN: s += ";42"; break;
		case YELLOW: s += ";43"; break;
		case BLUE: s += ";44"; break;
		case MAGENTA: s += ";45"; break;
		case CYAN: s += ";46"; break;
		case WHITE: s += ";47"; break;
		case NONE: s += ";49"; break;
		case KEEPCOLOR: break;
	}
	return s + "m"; // for example "\033[0;31;43m" for normal red text on yellow background
}