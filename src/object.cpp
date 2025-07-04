#include "../include/object.h"

vec<float> object::get_position() const {
	return position;
}

vec<float> object::get_velocity() const {
	return velocity;
}

void object::set_position(vec<float> p) {
	position = p;
}

void object::set_velocity(vec<float> v) {
	velocity = v;
}

void object::out_of_bounds(float& p, float& v, float edge_upper, float edge_lower) {
	if (p < edge_lower || p + get_dimension() >= edge_upper) {
		v = -v;
		p = p < edge_lower ? -p : -p + 2 * (edge_upper - get_dimension());
	}
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
