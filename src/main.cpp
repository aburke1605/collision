#include <SFML/Graphics.hpp>

#include "../include/scene.h"

void parse_user_input(sf::RenderWindow& window) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
				window.close();
		}
}

int main() {
	uint width, height;
	width = height= 500;
	sf::RenderWindow window(sf::VideoMode(width, height), "collision");

	scene scene;
	while (window.isOpen()) {
		window.clear();
		parse_user_input(window);
		scene.update(window);
		window.display();
	}

	return 0;
}