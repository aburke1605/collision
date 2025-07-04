#pragma once

#include <SFML/Graphics.hpp>

#include "object.h"

class box: public object {
	private:
		float length;

	public:
		box();
		box(vec<float>, float l);
		box(vec<float>, vec<float>, float);
		box(vec<float>, vec<float>, float, sf::Color);

		float get_dimension();
		void set_dimension(float);
};
