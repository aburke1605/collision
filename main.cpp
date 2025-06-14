#include <SFML/Graphics.hpp>



int main() {

	float width, height;
	width = height= 500.0;
	sf::RenderWindow window(sf::VideoMode(width, height), "collision");

	while (window.isOpen()) {
		window.display();
	}

	return 0;
}