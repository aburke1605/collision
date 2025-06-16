#include "../include/ball.h"

ball::ball() {
	position = vec<float>(10.0, 0.0);
	velocity = vec<float>(-500.0, 700.0);
	radius = 10.0;

	shape = std::make_unique<sf::CircleShape>(radius);
	shape->setFillColor(sf::Color::White);
}

float ball::get_dimension() {
	return 2 * radius;
}
