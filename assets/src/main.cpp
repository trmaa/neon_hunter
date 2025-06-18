#include <SFML/Graphics.hpp>
#include <glm/glm.hpp>
#include <cstdio>
#include "window.hpp"
#include "player.hpp"
#include "globals.hpp"

eng::Window main_window(glm::ivec2(200, 150));
float ticks = 0.0f;

void loop() {
	main_window.update();
}

int main() {
	std::printf(":) \n");
	
	while (main_window.isOpen()) {
		sf::Event event;
        while (main_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                main_window.close();
            }
        }
		ticks += 0.001f;
		loop();
    }
}
