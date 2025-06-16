#pragma once

#include <SFML/Graphics.hpp>

#include "vec.h"

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
		virtual void update(sf::RenderWindow&, float) = 0;

		void render(sf::RenderWindow&, float);
};
