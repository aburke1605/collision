#include "../include/object.h"

const vec<float> object::get_position() {
	return position;
}

const vec<float> object::get_velocity() {
	return velocity;
}

void object::render(sf::RenderWindow& window, float dt) {
	update(window, dt);
	window.draw(*shape);
}
