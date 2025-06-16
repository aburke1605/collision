#include "../include/scene.h"

scene::scene() {
	time = clk::now();
}

void scene::update(sf::RenderWindow& window) {
	clk::time_point current_time = clk::now();
	std::chrono::duration<float> delta = current_time - time;
	float dt = delta.count(); // in seconds
	time = current_time;

	Ball.render(window, dt);
	Box.render(window, dt);
}