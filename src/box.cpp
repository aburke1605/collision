#include "../include/box.h"

box::box() {
	position = vec<float>(30.0, 0.0);
	velocity = vec<float>(-1000.0, 0.0);
	length = 20.0;

	shape = std::make_unique<sf::RectangleShape>(sf::Vector2f(length, length));
	shape->setFillColor(sf::Color::Red);
}

void box::out_of_bounds(float& p, float& v, float edge_upper, float edge_lower = 0.0) {
	if (p < edge_lower || p + length >= edge_upper) {
		v = -v;
		p = p < edge_lower ? -p : -p + 2 * (edge_upper - length);
	}
}
