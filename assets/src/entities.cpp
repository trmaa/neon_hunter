#include "player.hpp"

std::vector<eng::Entity*> g_entities {
	new Player(glm::vec2(10.0f, 10.0f)) 
};
