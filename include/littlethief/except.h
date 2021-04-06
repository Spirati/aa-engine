#pragma once
#include <exception>
#include <filesystem>
#include <iostream>

#define FILE_NOT_FOUND std::string("File not found")

class SDLResourceFailure : public std::exception {
public:
	
	const char* SDLerror;

	SDLResourceFailure(const char* SDLerror) : SDLerror{ SDLerror } {}

	const char* what() const throw() {
		std::cout << SDLerror << std::endl;
		return SDLerror;
	}
};