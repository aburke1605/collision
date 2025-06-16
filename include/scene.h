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

	public:
		scene();
		void update(sf::RenderWindow& window);
};