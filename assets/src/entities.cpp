#include <future>
#include <iostream>
#include "player.hpp"
#include "entity.hpp"
#include "entities.hpp"
#include "vectors.hpp"
#include "globals.hpp"

Player g_player = Player(glm::vec3(-50.0f, -50.0f, 0));

std::vector<eng::Entity*> g_entities {
	&g_player,
};

std::vector<eng::LightSpot> g_lightspots(100, eng::LightSpot(sf::Vector3f(7389.f, 7389.f, 7389.f), sf::Vector3f(0,0,0), 0));

void g_lightspots_push(eng::LightSpot lightspot) {
	for (std::size_t i = 0; i < g_lightspots.size(); ++i) {
        if (g_lightspots[i].position != sf::Vector3f(7389.f, 7389.f, 7389.f)) {
			continue;
        }
        g_lightspots[i] = lightspot;
		return;
	}
}

void g_summon_entities() {
	std::future<eng::json> raw_entities = std::async(std::launch::async, eng::json_read, "build/bin/entities/entities.json");
	eng::json entities = raw_entities.get();

	for (auto entity : entities) {
		glm::vec3 position(
			entity["position"].value("x", 0.0f),
			entity["position"].value("y", 0.0f),
			entity["position"].value("z", 0.0f)
		);

		std::string name = entity.value("name", "unnamed_entity");

		g_entities.push_back(new eng::Entity(position, name));
	}

	std::future<eng::json> raw_lightspots = std::async(std::launch::async, eng::json_read, "build/bin/entities/lightspots.json");
    eng::json lightspots = raw_lightspots.get();

	for (auto lightspot : lightspots) {
		if (!lightspot.contains("position") || !lightspot.contains("color") || !lightspot.contains("intensity")) {
			std::cerr << "Skipping invalid lightspot: missing required field" << std::endl;
			continue;
		}

		glm::vec3 position(
			lightspot["position"].value("x", 0.0f),
			lightspot["position"].value("y", 0.0f),
			lightspot["position"].value("z", 0.0f)
		);

		glm::vec3 color(
			lightspot["color"].value("r", 1.0f),  
			lightspot["color"].value("g", 1.0f),
			lightspot["color"].value("b", 1.0f)
		);

		float intensity = lightspot.value("intensity", 1.0f);

		g_lightspots_push(eng::LightSpot(eng::gts(position), eng::gts(color), intensity));
		g_entities.push_back(new eng::Entity(position * 0.999f, "star"));
	}

	eng::window.reload_pipeline();
}

void g_save_entities_to_json() {
    eng::json entities;
    for (auto* entity : g_entities) {
		if (entity->get_name() == "player") {
            continue;
		}
        entities.push_back({
            {"name", "box"},
            {"position", {
                {"x", entity->get_position().x},
                {"y", entity->get_position().y},
                {"z", entity->get_position().z}
            }}
        });
    }
    std::ofstream("build/bin/entities/entities.json") << entities.dump(4);
} 
