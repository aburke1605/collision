#pragma once

#include <chrono>
typedef std::chrono::high_resolution_clock clk;

#include <SFML/Graphics.hpp>

#include "ball.h"
#include "box.h"

class scene {
	private:
		std::vector<std::unique_ptr<object>> objects;
		clk::time_point time;
		bool interacting;

	public:
		scene();
		void parse_user_input(sf::RenderWindow&);
		void update(sf::RenderWindow&);
		void move_object(sf::Vector2i);
};