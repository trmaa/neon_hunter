#ifndef GLOBALS_HPP
#define GLOBALS_HPP

#include <fstream>
#include <iostream>
#include <json.hpp>
#include "window.hpp"

namespace eng {
	extern float ticks;
	extern float delta_time;
	extern eng::Window window;

	inline extern eng::json json_read(std::string fpath) {
		std::ifstream file(fpath);
		if (!file.is_open()) {
			std::cerr<<"Json corrupt"<<std::endl;
			return "";
		}
		eng::json data;
		file >> data;
		return data;
	}
};

#endif
