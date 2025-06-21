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

	new eng::Entity(glm::vec3(200+0, 0, 18), "star"),
	new eng::Entity(glm::vec3(200+0, 0, 0), "box"),
	new eng::Entity(glm::vec3(200+0, -25, 0), "box"),
	new eng::Entity(glm::vec3(200+0, 25, 0), "box"),
	new eng::Entity(glm::vec3(200+25, 0, 0), "box"),
	new eng::Entity(glm::vec3(200-25, 0, 0), "box"),
	new eng::Entity(glm::vec3(200+0, -25, 5), "star"),
	new eng::Entity(glm::vec3(200+0, 25, 5), "star"),
	new eng::Entity(glm::vec3(200+25, 0, 5), "star"),
	new eng::Entity(glm::vec3(200-25, 0, 5), "star"),
	new eng::Entity(glm::vec3(200+0, -25, 13), "box"),
	new eng::Entity(glm::vec3(200+0, 25, 13), "box"),
	new eng::Entity(glm::vec3(200+25, 0, 13), "box"),
	new eng::Entity(glm::vec3(200-25, 0, 13), "box"),

	new eng::Entity(glm::vec3(-100, 0, 18), "box"),
	new eng::Entity(glm::vec3(-106, 6, 18), "box"),
	new eng::Entity(glm::vec3(-112, 12, 18), "box"),
	new eng::Entity(glm::vec3(-118, 18, 18), "box"),
	new eng::Entity(glm::vec3(-124, 24, 18), "box"),

	new eng::Entity(glm::vec3(-100, 0, 12), "box"),
	new eng::Entity(glm::vec3(-124, 24, 12), "box"),

	new eng::Entity(glm::vec3(-100, 0, 6), "box"),
	new eng::Entity(glm::vec3(-124, 24, 6), "box"),

	new eng::Entity(glm::vec3(-100, 0, 0), "box"),
	new eng::Entity(glm::vec3(-124, 24, 0), "box"),

	new eng::Entity(glm::vec3(-112, 12, 0), "star"),
};

std::vector<eng::LightSpot> g_lightspots(100, eng::LightSpot(sf::Vector3f(7389.f, 7389.f, 7389.f), sf::Vector3f(0,0,0), 0));

void g_lightspots_init() {
	g_lightspots[0] = eng::LightSpot(sf::Vector3f(0, 0, 18.1), sf::Vector3f(1,1,0), 10);
	g_lightspots[1] = eng::LightSpot(sf::Vector3f(200+0, 0, 18.1), sf::Vector3f(1,0,1), 40);
	g_lightspots[2] = eng::LightSpot(sf::Vector3f(-112, 12, 0.1), sf::Vector3f(0,1,1), 100);
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
