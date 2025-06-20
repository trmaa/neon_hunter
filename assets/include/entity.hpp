#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <SFML/Graphics.hpp>
#include <glm/glm.hpp>
#include <string>

namespace eng {
	class Entity {
		protected:
			glm::vec3 m_position;

			sf::Texture m_texture;
			sf::Texture m_normalmap;

			std::string m_texture_path;
			std::string m_normalmap_path;

			sf::RenderTexture m_canvas;

		public:
			glm::vec3 get_position() { return this->m_position; }

			virtual const sf::Texture& get_texture() {
				if (m_texture.getSize().x == 0)
					m_texture.loadFromFile(m_texture_path);
				return m_texture;
			}

			virtual const sf::Texture& get_normalmap() {
				if (m_normalmap.getSize().x == 0)
					m_normalmap.loadFromFile(m_normalmap_path);
				return m_normalmap;
			}

			Entity(glm::vec3 pos, std::string name);
			virtual ~Entity() = default;

			sf::Sprite draw();
	};

	struct LightSpot {
		sf::Vector3f position;
        sf::Vector3f color;
		float intensity;

		LightSpot(sf::Vector3f position, sf::Vector3f color, float intensity): position(position), color(color), intensity(intensity) {}
	};
};

#endif
