#pragma one

#include <glm/glm.hpp>
#include <SFML/Graphics.hpp>

namespace eng {
	inline glm::vec2 stg(sf::Vector2f v) {
		return glm::vec2(v.x, v.y);
	}

	inline glm::ivec2 stg(sf::Vector2i v) {
		return glm::ivec2(v.x, v.y);
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
