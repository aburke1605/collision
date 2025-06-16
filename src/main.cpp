#include <SFML/Graphics.hpp>

#include "../include/scene.h"

int main() {
	uint width, height;
	width = height= 500;
	sf::RenderWindow window(sf::VideoMode(width, height), "collision");

	scene scene;
	while (window.isOpen()) {
		window.clear();
		scene.update(window);
		window.display();
	}

	return 0;
}