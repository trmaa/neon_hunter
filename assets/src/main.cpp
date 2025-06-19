#include <SFML/Graphics.hpp>
#include <glm/glm.hpp>
#include <cstdio>
#include "globals.hpp"
#include "entities.hpp"

eng::Window g_window(glm::ivec2(192, 108));
float g_ticks = 0.0f;
float g_delta_time;

void start_loop();

void loop() {
	g_window.update();

	g_player.control();
}

int main() {
	std::printf(":) \n");

	g_initialize_entities();
	start_loop();
}

void start_loop() {
	sf::Clock clock;
	while (g_window.isOpen()) {
		sf::Event event;
        while (g_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                g_window.close();
            }
        }
		g_delta_time = clock.restart().asSeconds();
		g_ticks += g_delta_time;
		loop();
    }
}
