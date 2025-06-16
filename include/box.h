#pragma once

#include <SFML/Graphics.hpp>

#include "object.h"

class box: public object {
	private:
		float length;

	public:
		box();

		float get_dimension();
};
