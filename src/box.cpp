#include "../include/box.h"

box::box() {
	position = vec<float>(30.0, 0.0);
	velocity = vec<float>(-1000.0, 0.0);
	length = 20.0;

	shape = std::make_unique<sf::RectangleShape>(sf::Vector2f(length, length));
	shape->setFillColor(sf::Color::Red);
}

float box::get_dimension() {
	return length;
}
