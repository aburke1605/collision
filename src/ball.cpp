#include "../include/ball.h"

ball::ball() {
	position = vec<float>(10.0, 0.0);
	velocity = vec<float>(0.0, 0.0);
	radius = 10.0;

	shape = std::make_unique<sf::CircleShape>(radius);
	shape->setFillColor(sf::Color::White);
}

void ball::out_of_bounds(sf::RenderWindow& window, float& px, float& py, float& vx, float& vy) {
	if (px < 0 || px + 2 * radius >= window.getSize().x) {
		vx = -vx;
		px = px < 0 ? -px : -px + 2 * (window.getSize().x - 2 * radius);
	}
	if (py < 0 || py + 2 * radius >= window.getSize().y) {
		vy = -vy;
		py = py < 0 ? -py : -py + 2 * (window.getSize().y - 2 * radius);
	}
}
