#pragma once

#include <stdexcept>
#include <iostream>
#include <sstream>

#define IMC_ERROR(message)\
{\
	std::stringstream sstr;\
	sstr << "IMC Error: " << message << std::endl;\
	throw std::runtime_error(sstr.str());\
}

#define IMC_WARNING(message)\
std::clog << "IMC Warning: " << message << std::endl;

#define IMC_INFO(message)\
std::clog << "IMC Info: " << message << std::endl;
