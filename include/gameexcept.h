#pragma once
#include <exception>
#include <filesystem>

class AssetNotFound : public std::exception {
public:
	std::filesystem::path path;

	AssetNotFound(std::filesystem::path& path) : path{ path } {}

	template<class stringType>
	const stringType* what() const throw() {
		return path.c_str();
	}
	
};