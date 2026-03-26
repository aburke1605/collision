#pragma once

#include <cmath>
#include <memory>

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

		vec<float> get_position() const;
		vec<float> get_velocity() const;
		void set_position(vec<float>);
		void set_velocity(vec<float>);

        // changes for each shape
		virtual float get_dimension() = 0;
		virtual void set_dimension(float) = 0;

		void out_of_bounds(float&, float&, float, float = 0.0);

		void update(sf::RenderWindow&, float);

		void render(sf::RenderWindow&, float);
};
