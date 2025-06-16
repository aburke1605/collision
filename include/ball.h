#pragma once

#include <cmath>

#include <SFML/Graphics.hpp>

#include "object.h"

class ball: public object {
	private:
		float radius;

	public:
		ball();

		void update(sf::RenderWindow&, float);
};
