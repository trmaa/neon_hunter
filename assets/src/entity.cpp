#include <SFML/Graphics.hpp>
#include <glm/glm.hpp>
#include "vectors.hpp"
#include "globals.hpp"
#include "entities.hpp"

eng::Entity::Entity(glm::vec3 pos, std::string name)
	: m_position(pos),
	  m_texture_path("build/bin/sprites/"+name+".png"),
	  m_normalmap_path("build/bin/sprites/"+name+"_normalmap.png") {
	this->m_texture.loadFromFile(this->m_texture_path);
	this->m_normalmap.loadFromFile(this->m_normalmap_path);
}

sf::Sprite eng::Entity::draw() {
	if (!this->m_canvas.create(this->get_texture().getSize().x, this->get_texture().getSize().y))
		return sf::Sprite();

	this->m_canvas.clear(sf::Color::Transparent);

	sf::Shader shader;
	shader.loadFromFile("build/shaders/normal_lighting.glsl", sf::Shader::Fragment);
	shader.setUniform("texture", this->get_texture());
	shader.setUniform("normalmap", this->get_normalmap());
	shader.setUniform("entity_position", eng::gts(this->m_position));
	for (std::size_t i = 0; i < g_lightspots.size(); ++i) {
		shader.setUniform("lightspots_pos[" + std::to_string(i) + "]", g_lightspots[i].position);
		shader.setUniform("lightspots_col[" + std::to_string(i) + "]", g_lightspots[i].color);
		shader.setUniform("lightspots_int[" + std::to_string(i) + "]", g_lightspots[i].intensity);
	}

	sf::Sprite sprite;
	sprite.setTexture(this->get_texture());
	this->m_canvas.draw(sprite, &shader);
	this->m_canvas.display();

	sf::Sprite out(this->m_canvas.getTexture());

    float sprite_radius = 8.f;
	glm::vec3 position = 
		this->m_position 
		- g_player.get_position() 
		+ glm::vec3(
			g_window.get_resolution().x, 
			g_window.get_resolution().y, 
			0
		) / 2.f 
		- glm::vec3(sprite_radius);
	position -= glm::vec3(0, this->m_position.z, 0);

	glm::vec2 position_2d = glm::vec2(position.x, position.y);
	out.setPosition(eng::gts(position_2d));
	return out;
}
