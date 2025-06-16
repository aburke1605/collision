#include "../include/scene.h"

scene::scene() {
	time = clk::now();

	objects.push_back(std::make_unique<ball>());
	objects.push_back(std::make_unique<box>());
}

void scene::parse_user_input(sf::RenderWindow& window) {
	sf::Event event;
	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
			window.close();
	}
}

void scene::update(sf::RenderWindow& window) {
	parse_user_input(window);

	clk::time_point current_time = clk::now();
	std::chrono::duration<float> delta = current_time - time;
	float dt = delta.count(); // in seconds
	time = current_time;

	for (std::vector<std::unique_ptr<object>>::iterator it = objects.begin(); it != objects.end(); it++)
		(*it)->render(window, dt);
}