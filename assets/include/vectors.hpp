#ifndef VECTORS_HPP
#define VECTORS_HPP

#include <glm/glm.hpp>
#include <SFML/Graphics.hpp>

namespace eng {
	inline glm::vec3 stg(sf::Vector2f v) {
		return glm::vec3(v.x, v.y, 0);
	}

	inline glm::ivec3 stg(sf::Vector2i v) {
		return glm::ivec3(v.x, v.y, 0);
	}

	inline glm::vec3 stg(sf::Vector3f v) {
		return glm::vec3(v.x, v.y, v.z);
	}

	inline sf::Vector2f gts(glm::vec2 v) {
		return sf::Vector2f(v.x, v.y);
	}

	inline sf::Vector2i gts(glm::ivec2 v) {
		return sf::Vector2i(v.x, v.y);
	}

	inline sf::Vector3f gts(glm::vec3 v) {
		return sf::Vector3f(v.x, v.y, v.z);
	}
};

#endif
