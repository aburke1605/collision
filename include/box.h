#pragma once

#include <cmath>

#include <SFML/Graphics.hpp>

#include "object.h"
#include "../include/constants.h"

class box: public object {
	private:
		float length;

	public:
		box();

		void update(sf::RenderWindow&, float);
};
