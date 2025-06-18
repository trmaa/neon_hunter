#include <SFML/Graphics.hpp>
#include "vectors.hpp"
#include "player.hpp"
#include "globals.hpp"

Player::Player()
	: m_position(10.f, 10.f) {
	this->m_texture.loadFromFile(this->m_texture_path);
    this->m_normalmap.loadFromFile(this->m_normalmap_path);
}

sf::Sprite Player::draw() {
	if (!this->m_canvas.create(this->m_texture.getSize().x, this->m_texture.getSize().y))
		return sf::Sprite();

	this->m_canvas.clear(sf::Color::Transparent);

	sf::Shader shader;
	shader.loadFromFile("build/shaders/normal_lighting.glsl", sf::Shader::Fragment);
	shader.setUniform("texture", this->m_texture);
	shader.setUniform("normalmap", this->m_normalmap);
	shader.setUniform("time", g_ticks);

	sf::Sprite sprite;
	sprite.setTexture(this->m_texture);
	this->m_canvas.draw(sprite, &shader);
	this->m_canvas.display();

	sf::Sprite out(this->m_canvas.getTexture());
	out.setPosition(eng::gts(this->m_position));
	return out;
}
