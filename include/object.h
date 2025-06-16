#pragma once

#include <cmath>

#include <SFML/Graphics.hpp>

#include "vec.h"
#include "constants.h"

class object {
    protected:
        std::unique_ptr<sf::Shape> shape;
		vec<float> position;
		vec<float> velocity;
    
    public:
        virtual ~object() = default;

		const vec<float> get_position();
		const vec<float> get_velocity();

        // changes for each shape
		virtual void out_of_bounds(sf::RenderWindow&, float&, float&, float&, float&) = 0;
		void update(sf::RenderWindow&, float);

		void render(sf::RenderWindow&, float);
};
