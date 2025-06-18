#include <SFML/Graphics.hpp>
#include <glm/glm.hpp>
#include <cstdio>
#include "window.hpp"
#include "globals.hpp"

eng::Window main_window(glm::ivec2(200, 150));
float g_ticks = 0.0f;
float g_delta_time;

void loop() {
	main_window.update();
}

int main() {
	std::printf(":) \n");
	
	sf::Clock clock;
	while (main_window.isOpen()) {
		sf::Event event;
        while (main_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                main_window.close();
            }
        }
		g_delta_time = clock.restart().asSeconds();
		g_ticks += g_delta_time;
		loop();
    }
}
