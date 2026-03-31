#include "../include/object.h"

#include "../include/box.h"
#include "../include/ball.h"
#include "../include/utils.h"

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
	// out_of_bounds(new_px, new_vx, window.getSize().x);
	// out_of_bounds(new_py, new_vy, window.getSize().y);

	// apply changes
	position.set_x(new_px);
	position.set_y(new_py);
	shape->setPosition(new_px, new_py);
	velocity.set_x(new_vx);
	velocity.set_y(new_vy);

	// float large_number = 50;
	float large_number = 200.0f;
	std::vector<std::shared_ptr<object>> A = {
		// std::make_shared<box>(vec<float>(window.getSize().x / 2 - large_number / 2,      -large_number + 5), vec<float>(0.0f, 0.0f), large_number, sf::Color::White), // ceiling
		// std::make_shared<box>(vec<float>(window.getSize().x / 2 - large_number / 2, window.getSize().y - 250), vec<float>(0.0f, 0.0f), large_number, sf::Color::Red),   // floor
		// std::make_shared<box>(vec<float>(- large_number + 5, window.getSize().y / 2 - large_number / 2), vec<float>(0.0f, 0.0f), large_number, sf::Color::Blue), // left wall
		// std::make_shared<box>(vec<float>(window.getSize().x - 5, window.getSize().y / 2 - large_number / 2), vec<float>(0.0f, 0.0f), large_number, sf::Color::Green)  // right wall
		std::make_shared<ball>(vec<float>(window.getSize().x / 2 - large_number / 2 / 2,                              -large_number), vec<float>(0.0f, 0.0f), large_number / 2, sf::Color::White), // ceiling
		std::make_shared<ball>(vec<float>(window.getSize().x / 2 - large_number / 2 / 2,                         window.getSize().y), vec<float>(0.0f, 0.0f), large_number / 2, sf::Color::Red),   // floor
		std::make_shared<ball>(vec<float>(                            -large_number,  window.getSize().y / 2 - large_number / 2 / 2), vec<float>(0.0f, 0.0f), large_number / 2, sf::Color::Blue),  // left wall
		std::make_shared<ball>(vec<float>(                       window.getSize().x,  window.getSize().y / 2 - large_number / 2 / 2), vec<float>(0.0f, 0.0f), large_number / 2, sf::Color::Green), // right wall
	};
	for (auto it = A.begin(); it != A.end(); it++) {
		collide(*this, **it);
		auto p = (*it)->get_position();
		auto d = (*it)->get_dimension();
		// (*it)->set_position(vec<float>(p.get_x()-d/2, p.get_y()-d/2));
		(*it)->shape->setPosition(p.get_x()-d/4, p.get_y()-d/4);
		window.draw(*(*it)->shape);
	}
}

void object::render(sf::RenderWindow& window, float dt) {
	update(window, dt);
	window.draw(*shape);
}
