#include "../include/ball.h"

ball::ball() {
	position = vec<float>(250.0, 0.0);
	velocity = vec<float>(-1000.0, 0.0);
	radius = 25.0;

	shape = std::make_unique<sf::CircleShape>(radius);
	shape->setFillColor(sf::Color::White);
}

float ball::get_dimension() {
	return 2 * radius;
}
