#pragma once

#include <cmath>

#include <SFML/Graphics.hpp>

#include "vec.h"

class ball {
	private:
		sf::CircleShape circle;
		vec<float> position;
		vec<float> velocity;

	public:
		ball();

		const sf::Shape& get_shape_handle();
		const vec<float> get_position();
		const vec<float> get_velocity();

		void update(sf::RenderWindow&, float);

		void render(sf::RenderWindow&, float);
};