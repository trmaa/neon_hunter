#include <SFML/Graphics.hpp>
#include <glm/glm.hpp>
#include "globals.hpp"
#include "entities.hpp"

eng::Window eng::window(glm::ivec2(192, 108));
float eng::ticks = 0.0f;
float eng::delta_time;

void start_loop();

void loop() {
	eng::window.update();
	g_player.control();
}

int main() {
	g_summon_entities();
	start_loop();
}

void start_loop() {
	sf::Clock clock;
	while (eng::window.isOpen()) {
		sf::Event event;
        while (eng::window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                eng::window.close();
            }
        }
		eng::delta_time = clock.restart().asMilliseconds();
		eng::ticks += eng::delta_time;
		loop();
    }
}
