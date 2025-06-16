#pragma once

#include <SFML/Graphics.hpp>

#include "object.h"

class ball: public object {
	private:
		float radius;

	public:
		ball();

		float get_dimension();
};
