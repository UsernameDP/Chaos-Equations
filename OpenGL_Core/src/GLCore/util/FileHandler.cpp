#include "pch.hpp"
#include "FileHandler.hpp"

#include <fstream>
#include <filesystem>

namespace GLCore::util {
	std::string FileHandler::readFile(const std::string& path) {
		std::ifstream file(path);

		if (!file.is_open()) {
			file.close();
			LOG_ERROR("{0} does not exist", path);
		}

		std::string buffer = "";
		std::string line;
		while ( std::getline(file, line)) {
			buffer += line + "\n";
		}		

		file.close();

		return buffer;
	}
}