#include "../include/box.h"

box::box() {
	position = vec<float>(30.0, 0.0);
	velocity = vec<float>(100.0, 0.0);
	length = 20.0;

	shape = std::make_unique<sf::RectangleShape>(sf::Vector2f(length, length));
	shape->setFillColor(sf::Color::Red);
}

void box::out_of_bounds(sf::RenderWindow& window, float& px, float& py, float& vx, float& vy) {
	if (px < 0 || px + length >= window.getSize().x) {
		vx = -vx;
		px = px < 0 ? -px : -px + 2 * (window.getSize().x - length);
	}
	if (py < 0 || py + length >= window.getSize().y) {
		vy = -vy;
		py = py < 0 ? -py : -py + 2 * (window.getSize().y - length);
	}
}
