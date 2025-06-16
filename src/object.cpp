#include "../include/object.h"

const vec<float> object::get_position() {
	return position;
}

const vec<float> object::get_velocity() {
	return velocity;
}

void object::update(sf::RenderWindow& window, float dt) {
	// update velocity first for gravity and air resistance
	float new_vx = velocity.get_x() * exp(-b * dt);
	float new_vy = (velocity.get_y() + g * dt) * exp(-b * dt);

	// update position using new velocity
	float new_px = position.get_x() + new_vx * dt;
	float new_py = position.get_y() + new_vy * dt;

	// check for out of boundary and bounce back
	out_of_bounds(new_px, new_vx, window.getSize().x);
	out_of_bounds(new_py, new_vy, window.getSize().y);

	// apply changes
	position.set_x(new_px);
	position.set_y(new_py);
	shape->setPosition(new_px, new_py);
	velocity.set_x(new_vx);
	velocity.set_y(new_vy);
}

void object::render(sf::RenderWindow& window, float dt) {
	update(window, dt);
	window.draw(*shape);
}
