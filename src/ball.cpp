#include "../include/ball.h"

ball::ball() {
	position = vec<float>(10.0, 0.0);
	velocity = vec<float>(-500.0, 700.0);
	radius = 10.0;

	shape = std::make_unique<sf::CircleShape>(radius);
	shape->setFillColor(sf::Color::White);
}

void ball::out_of_bounds(float& p, float& v, float edge_upper, float edge_lower = 0.0) {
	if (p < edge_lower || p + 2 * radius >= edge_upper) {
		v = -v;
		p = p < edge_lower ? -p : -p + 2 * (edge_upper - 2 * radius);
	}
}
