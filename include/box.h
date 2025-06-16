#pragma once

#include <SFML/Graphics.hpp>

#include "object.h"

class box: public object {
	private:
		float length;

	public:
		box();

		void out_of_bounds(sf::RenderWindow&, float&, float&, float&, float&);
};
