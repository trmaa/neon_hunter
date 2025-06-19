#include "player.hpp"

Player g_player = Player(glm::vec2(10.0f, 10.0f));

std::vector<eng::Entity*> g_entities {
	&g_player,
	new eng::Entity(glm::vec2(50.0f, 50.0f), "build/bin/sprites/player_idle.png", "build/bin/sprites/player_idle_normalmap.png")
};
