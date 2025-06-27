#include "../include/ball.h"

ball::ball() {
	position = vec<float>(250.0, 0.0);
	velocity = vec<float>(0.0, 0.0);
	radius = 25.0;

	shape = std::make_unique<sf::CircleShape>(radius);
	shape->setFillColor(sf::Color::White);
}

ball::ball(vec<float> p, vec<float> v, float r): ball() {
	position = p;
	velocity = v;
	radius = r;
}

ball::ball(vec<float> p, vec<float> v, float r, sf::Color c) {
	position = p;
	velocity = v;
	radius = r;

	shape = std::make_unique<sf::CircleShape>(radius);
	shape->setFillColor(c);
}

float ball::get_dimension() {
	return 2 * radius;
}
