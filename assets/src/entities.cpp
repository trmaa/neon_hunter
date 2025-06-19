#include "player.hpp"

Player g_player = Player(glm::vec2(10.0f, 10.0f));

std::vector<eng::Entity*> g_entities {
	&g_player 
};
