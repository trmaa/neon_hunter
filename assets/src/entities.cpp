#include "player.hpp"

Player g_player = Player(glm::vec2(10.0f, 10.0f));

std::vector<eng::Entity*> g_entities {
	&g_player,
	new eng::Entity(glm::vec2(50.0f, 25.0f), "build/bin/sprites/player_idle.png", "build/bin/sprites/player_idle_normalmap.png"),
	new eng::Entity(glm::vec2(50.0f, -25.0f), "build/bin/sprites/player_idle.png", "build/bin/sprites/player_idle_normalmap.png"),
	new eng::Entity(glm::vec2(std::sqrt(50*50 - 25*25) + 50, 0.0f), "build/bin/sprites/player_idle.png", "build/bin/sprites/player_idle_normalmap.png"),
};

std::vector<eng::LightSpot> g_lightspots(100, eng::LightSpot(sf::Vector3f(7389.f, 7389.f, 7389.f), sf::Vector3f(0,0,0), 0));

void g_initialize_entities() {
	g_lightspots[0] = eng::LightSpot(sf::Vector3f(50.f, 25.f, 10.f), sf::Vector3f(1,0,0), 20);
	g_lightspots[1] = eng::LightSpot(sf::Vector3f(50.f, -25.f, 10.f), sf::Vector3f(0,1,0), 20);
	g_lightspots[2] = eng::LightSpot(sf::Vector3f(std::sqrt(50*50 - 25*25) + 50, 0.f, 10.f), sf::Vector3f(1,1,1), 20);
}
