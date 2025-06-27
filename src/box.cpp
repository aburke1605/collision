#include "../include/box.h"

box::box() {
	position = vec<float>(250.0, 0.0);
	velocity = vec<float>(0.0, 0.0);
	length = 50.0;

	shape = std::make_unique<sf::RectangleShape>(sf::Vector2f(length, length));
	shape->setFillColor(sf::Color::Red);
}

box::box(vec<float> p, vec<float> v, float l): box() {
	position = p;
	velocity = v;
	length = l;
}

box::box(vec<float> p, vec<float> v, float l, sf::Color c) {
	position = p;
	velocity = v;
	length = l;

	shape = std::make_unique<sf::RectangleShape>(sf::Vector2f(length, length));
	shape->setFillColor(c);
}

float box::get_dimension() {
	return length;
}

void box::set_dimension(float l) {
	length = l;
}
