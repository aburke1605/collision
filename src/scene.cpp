#include "../include/scene.h"

scene::scene(): interacting(false) {
	time = clk::now();

	objects.push_back(std::make_shared<ball>());
	objects.push_back(std::make_shared<box>());
}

void scene::parse_user_input(sf::RenderWindow& window) {
	sf::Event event;
	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
			window.close();

		if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
			interacting = true;
		}

		else if (event.type == sf::Event::MouseButtonReleased)
			interacting = false;
	}
}

void scene::update(sf::RenderWindow& window) {
	parse_user_input(window);

	clk::time_point current_time = clk::now();
	std::chrono::duration<float> delta = current_time - time;
	float dt = delta.count(); // in seconds
	time = current_time;

	if (interacting)
		move_object(sf::Mouse::getPosition(window));

	for (std::vector<std::shared_ptr<object>>::iterator it = objects.begin(); it != objects.end(); it++)
		(*it)->render(window, dt);
}

void scene::move_object(sf::Vector2i mouse_position) {
	auto which = std::find_if(objects.begin(), objects.end(), [mouse_position](auto& it) -> bool {
		if (
			(float)mouse_position.x > it->get_position().get_x() &&
			(float)mouse_position.x < it->get_position().get_x() + it->get_dimension() &&
			(float)mouse_position.y > it->get_position().get_y() &&
			(float)mouse_position.y < it->get_position().get_y() + it->get_dimension()
		) return true;
		return false;
	});
	if (which != objects.end()) {
		(*which)->set_position(vec<float>(mouse_position.x - (*which)->get_dimension() / 2, mouse_position.y - (*which)->get_dimension() / 2));
		(*which)->set_velocity(vec<float>(0.0, 0.0));
	}
}
