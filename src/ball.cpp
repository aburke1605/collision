#include "../include/ball.h"
#include "../include/constants.h"

ball::ball() {
	position = vec<float>(10.0, 10.0);
	velocity = vec<float>(1.0, 1.0);

	circle = sf::CircleShape(10.0);
	circle.setPosition(5.0, 5.0);
	circle.setFillColor(sf::Color::White);
}

const sf::Shape& ball::get_shape_handle() {
	return circle;
}

const vec<float> ball::get_position() {
	return position;
}

const vec<float> ball::get_velocity() {
	return velocity;
}

void ball::update(sf::RenderWindow& window, float dt) {
	// update velocity first for gravity and air resistance
	float new_vx = velocity.get_x() * exp(-b * dt);
	float new_vy = (velocity.get_y() + g * dt) * exp(-b * dt);

	// update position using new velocity
	float new_px = position.get_x() + new_vx * dt;
	float new_py = position.get_y() + new_vy * dt;

	// check for out of boundary and bounce back
	if (new_px < 0 || new_px + 2 * circle.getRadius() >= window.getSize().x) {
		new_vx = -new_vx;
		new_px = new_px < 0 ? -new_px : -new_px + 2 * (window.getSize().x - 2 * circle.getRadius());
	}
	if (new_py < 0 || new_py + 2 * circle.getRadius() >= window.getSize().y) {
		new_vy = -new_vy;
		new_py = new_py < 0 ? -new_py : -new_py + 2 * (window.getSize().y - 2 * circle.getRadius());
	}

	// apply changes
	position.set_x(new_px);
	position.set_y(new_py);
	circle.setPosition(new_px, new_py);
	velocity.set_x(new_vx);
	velocity.set_y(new_vy);
}

void ball::render(sf::RenderWindow& window, float dt) {
	update(window, dt);
	window.draw(circle);
}