#pragma one

#include <SFML/Graphics.hpp>
#include <glm/glm.hpp>
#include "entity.hpp"

class Player: public eng::Entity {
public:
	Player(glm::vec2 pos);
	~Player() = default;
};
