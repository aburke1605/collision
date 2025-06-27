#pragma once

#include <SFML/Graphics.hpp>

#include "object.h"

class ball: public object {
	private:
		float radius;

	public:
		ball();
		ball(vec<float>, vec<float>, float);
		ball(vec<float>, vec<float>, float, sf::Color);

		float get_dimension();
		void set_dimension(float);
};
