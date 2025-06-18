#pragma one

#include <SFML/Graphics.hpp>
#include <glm/glm.hpp>
#include <string>

namespace eng {
	class Entity {
		private:
			glm::vec2 m_position;

			sf::Texture m_texture;
			sf::Texture m_normalmap;

			std::string m_texture_path;
			std::string m_normalmap_path;

			sf::RenderTexture m_canvas;

		public:
			glm::vec2 get_position() { return this->m_position; }

			const sf::Texture& get_texture() {
				if (m_texture.getSize().x == 0)
					m_texture.loadFromFile(m_texture_path);
				return m_texture;
			}

			const sf::Texture& get_normalmap() {
				if (m_normalmap.getSize().x == 0)
					m_normalmap.loadFromFile(m_normalmap_path);
				return m_normalmap;
			}

			Entity(glm::vec2 pos, const std::string& texture_path, const std::string& normalmap_path);
			~Entity() = default;

			sf::Sprite draw();
	};
};
