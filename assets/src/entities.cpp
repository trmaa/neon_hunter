#include "player.hpp"
#include "entities.hpp"

Player g_player = Player(glm::vec3(-50.0f, -50.0f, 0));

std::vector<eng::Entity*> g_entities {
	&g_player,
	new eng::Entity(glm::vec3(0, 0, 18), "star"),
	new eng::Entity(glm::vec3(0, 0, 0), "box"),
	new eng::Entity(glm::vec3(0, -25, 0), "box"),
	new eng::Entity(glm::vec3(0, 25, 0), "box"),
	new eng::Entity(glm::vec3(25, 0, 0), "box"),
	new eng::Entity(glm::vec3(-25, 0, 0), "box"),
	new eng::Entity(glm::vec3(0, -25, 5), "star"),
	new eng::Entity(glm::vec3(0, 25, 5), "star"),
	new eng::Entity(glm::vec3(25, 0, 5), "star"),
	new eng::Entity(glm::vec3(-25, 0, 5), "star"),
	new eng::Entity(glm::vec3(0, -25, 13), "box"),
	new eng::Entity(glm::vec3(0, 25, 13), "box"),
	new eng::Entity(glm::vec3(25, 0, 13), "box"),
	new eng::Entity(glm::vec3(-25, 0, 13), "box"),
};

std::vector<eng::LightSpot> g_lightspots(100, eng::LightSpot(sf::Vector3f(7389.f, 7389.f, 7389.f), sf::Vector3f(0,0,0), 0));

void g_lightspots_init() {
	g_lightspots[0] = eng::LightSpot(sf::Vector3f(0, 0, 18.1), sf::Vector3f(1,1,0.6), 40);
}

void g_lightspots_push(eng::LightSpot lightspot) {
	for (std::size_t i = 0; i < g_lightspots.size(); ++i) {
        if (g_lightspots[i].position != sf::Vector3f(7389.f, 7389.f, 7389.f)) {
			continue;
        }
        g_lightspots[i] = lightspot;
		return;
	}
}
