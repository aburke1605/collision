#pragma once

#include <chrono>
typedef std::chrono::high_resolution_clock clk;
#include <memory>

#include <SFML/Graphics.hpp>

#include "ball.h"
#include "box.h"

class scene {
	private:
		std::vector<std::shared_ptr<object>> objects;
		clk::time_point time;
		std::shared_ptr<object> selected_object;

	public:
		scene();
		void parse_user_input(sf::RenderWindow&);
		void update(sf::RenderWindow&);
};