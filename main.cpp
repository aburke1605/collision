#include <SFML/Graphics.hpp>


class ball {
	private:
		sf::CircleShape circle;

	public:
		ball() {
			circle = sf::CircleShape(10.0);
			circle.setPosition(5.0, 5.0);
			circle.setFillColor(sf::Color::White);
		}
		const sf::Shape& get_shape_handle() {
			return circle;
		}
		void render(sf::RenderWindow& window) {
			window.draw(circle);
		}
};

class scene {
	private:
		ball b;
	public:
		scene() {}
		void update(sf::RenderWindow& window) {
			b.render(window);
		}

};

int main() {

	float width, height;
	width = height= 500.0;
	sf::RenderWindow window(sf::VideoMode(width, height), "collision");

	scene scene;
	while (window.isOpen()) {
		scene.update(window);
		window.display();
	}

	return 0;
}