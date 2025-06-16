#include "../include/box.h"

box::box() {
	position = vec<float>(30.0, 0.0);
	velocity = vec<float>(100.0, 0.0);
	length = 20.0;

	shape = std::make_unique<sf::RectangleShape>(sf::Vector2f(length, length));
	shape->setFillColor(sf::Color::Red);
}

void box::update(sf::RenderWindow& window, float dt) {
	// update velocity first for gravity and air resistance
	float new_vx = velocity.get_x() * exp(-b * dt);
	float new_vy = (velocity.get_y() + g * dt) * exp(-b * dt);

	// update position using new velocity
	float new_px = position.get_x() + new_vx * dt;
	float new_py = position.get_y() + new_vy * dt;

	// check for out of boundary and bounce back
	if (new_px < 0 || new_px + length >= window.getSize().x) {
		new_vx = -new_vx;
		new_px = new_px < 0 ? -new_px : -new_px + 2 * (window.getSize().x - length);
	}
	if (new_py < 0 || new_py + length >= window.getSize().y) {
		new_vy = -new_vy;
		new_py = new_py < 0 ? -new_py : -new_py + 2 * (window.getSize().y - length);
	}

	// apply changes
	position.set_x(new_px);
	position.set_y(new_py);
	shape->setPosition(new_px, new_py);
	velocity.set_x(new_vx);
	velocity.set_y(new_vy);
}
