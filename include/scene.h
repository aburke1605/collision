#pragma once

#include <chrono>
typedef std::chrono::high_resolution_clock clk;

#include <SFML/Graphics.hpp>

#include "ball.h"

class scene {
	private:
		ball B;
		clk::time_point time;

	public:
		scene();
		void update(sf::RenderWindow& window);
};