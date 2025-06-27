#include "../include/scene.h"

scene::scene() {
	time = clk::now();

	objects.push_back(std::make_shared<ball>(vec<float>(250.0, 500.0), vec<float>(0.0, 0.0), 25));
	objects.push_back(std::make_shared<ball>(vec<float>(250.0, 500.0), vec<float>(0.0, 0.0), 25, sf::Color::Red));
	objects.push_back(std::make_shared<box>(vec<float>(250.0, 500.0), vec<float>(0.0, 0.0), 50, sf::Color::Blue));
	objects.push_back(std::make_shared<box>(vec<float>(250.0, 500.0), vec<float>(0.0, 0.0), 50, sf::Color::Green));
}

void scene::parse_user_input(sf::RenderWindow& window) {
	sf::Event event;
	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
			window.close();

		switch (event.type) {
			case sf::Event::MouseButtonPressed:
				if (event.mouseButton.button == sf::Mouse::Left) {
					// identify clicked object
					sf::Vector2i mouse_position = sf::Mouse::getPosition(window);
					auto which = std::find_if(objects.begin(), objects.end(), [mouse_position](auto& it) -> bool {
						if (
							(float)mouse_position.x > it->get_position().get_x() &&
							(float)mouse_position.x < it->get_position().get_x() + it->get_dimension() &&
							(float)mouse_position.y > it->get_position().get_y() &&
							(float)mouse_position.y < it->get_position().get_y() + it->get_dimension()
						) return true;
						return false;
					});
					if (which != objects.end()) selected_object = *which;
					break;
				}

			case sf::Event::MouseButtonReleased:
				if (event.mouseButton.button == sf::Mouse::Left) {
					selected_object = nullptr;
					// move the selected object to the top of the objects vector?
					// maybe use a linked list
					break;
				}

			default:
				break;
		}
	}
}

void scene::update(sf::RenderWindow& window) {
	// calculate time passed since last scene update
	clk::time_point current_time = clk::now();
	std::chrono::duration<float> delta = current_time - time;
	float dt = delta.count(); // in seconds
	time = current_time;

	// object dragging
	parse_user_input(window);
	if (selected_object != nullptr) {
		sf::Vector2i mouse_position = sf::Mouse::getPosition(window);
		selected_object->set_position(vec<float>(mouse_position.x - selected_object->get_dimension() / 2, mouse_position.y - selected_object->get_dimension() / 2));
		selected_object->set_velocity(vec<float>(0.0, 0.0));
	}

	// render each object
	for (std::vector<std::shared_ptr<object>>::iterator it = objects.begin(); it != objects.end(); it++) {
		// handle collisions first
		if (selected_object == nullptr) {
			for (std::vector<std::shared_ptr<object>>::iterator jt = objects.begin(); jt != objects.end(); jt++) {
				if (it == jt) continue;
				collide(**it, **jt);
			}
		}

		(*it)->render(window, dt);
	}
}
