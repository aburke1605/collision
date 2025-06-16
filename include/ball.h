#pragma once

#include <SFML/Graphics.hpp>

#include "object.h"

class ball: public object {
	private:
		float radius;

	public:
		ball();

		void out_of_bounds(float&, float&, float, float);
};
