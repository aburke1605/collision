#include "../include/scene.h"

scene::scene() {
	time = clk::now();

	objects.push_back(std::make_shared<ball>());
	objects.push_back(std::make_shared<box>());
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

				float px_1 = (*it)->get_position().get_x();
				float py_1 = (*it)->get_position().get_y();
				float px_2 = (*jt)->get_position().get_x();
				float py_2 = (*jt)->get_position().get_y();
				
				// move apart default instantiated objects
				// (which are created in the same position)
				if (px_1 == px_2 && py_1 == py_2) {
					px_1 -= 1.1 * ((*it)->get_dimension() + (*jt)->get_dimension()) / 4;
					py_1 -= 1.1 * ((*it)->get_dimension() + (*jt)->get_dimension()) / 4;
					px_2 += 1.1 * ((*it)->get_dimension() + (*jt)->get_dimension()) / 4;
					py_2 += 1.1 * ((*it)->get_dimension() + (*jt)->get_dimension()) / 4;
					(*it)->set_position(vec<float>(px_1, py_1));
					(*jt)->set_position(vec<float>(px_2, py_2));
					
				// move apart and reflect objects which overlap according
				// to their dimensions and the contact normal vector
				} else if (std::sqrt(std::pow(px_1-px_2, 2) + std::pow(py_1-py_2, 2)) < ((*it)->get_dimension() + (*jt)->get_dimension()) / 2) {
					// contact normal vector:
					//   n = r2 - r1 / abs(r2 - r1)
					// angle:
					//   φ = atan[(r2_y - r1_y) / (r2_x - r1_x)]
					// components of velocity parallel to contact normal vector swap
					// components of velocity perpendicular to contact normal vector remain unchanged
					float phi = atan2(py_2 - py_1, px_2 - px_1);

					float vx_1 = (*it)->get_velocity().get_x();
					float vy_1 = (*it)->get_velocity().get_y();
					float vx_2 = (*jt)->get_velocity().get_x();
					float vy_2 = (*jt)->get_velocity().get_y();

					// convert to new coordinate system
					float v_par_1 = vx_1 * std::cos(phi) + vy_1 * std::sin(phi);
					float v_per_1 = vy_1 * std::cos(phi) - vx_1 * std::sin(phi);
					float v_par_2 = vx_2 * std::cos(phi) + vy_2 * std::sin(phi);
					float v_per_2 = vy_2 * std::cos(phi) - vx_2 * std::sin(phi);

					// swap parallel components after collision
					float new_v_par_1 = v_par_2;
					float new_v_par_2 = v_par_1;
					// keep perpendicular components
					float new_v_per_1 = v_per_1;
					float new_v_per_2 = v_per_2;

					// convert back to x-y
					float new_vx_1 = new_v_par_1 * std::cos(phi) - new_v_per_1 * std::sin(phi);
					float new_vy_1 = new_v_par_1 * std::sin(phi) + new_v_per_1 * std::cos(phi);
					float new_vx_2 = new_v_par_2 * std::cos(phi) - new_v_per_2 * std::sin(phi);
					float new_vy_2 = new_v_par_2 * std::sin(phi) + new_v_per_2 * std::cos(phi);

					(*it)->set_velocity(vec<float>(new_vx_1, new_vy_1));
					(*jt)->set_velocity(vec<float>(new_vx_2, new_vy_2));

					float factor = (((*it)->get_dimension() + (*jt)->get_dimension()) / 2 - std::sqrt(pow(px_2 - px_1, 2) + pow(py_2 - py_1, 2))) / 2;
					factor *= 1.01; // to make it > rather than >= for next scene::update()
					(*it)->set_position(vec<float>(px_1 + (factor * std::cos(phi)) * (px_1>px_2?1:-1), py_1 + (factor * std::sin(phi)) * (py_1>py_2?1:-1)));
					(*jt)->set_position(vec<float>(px_2 + (factor * std::cos(phi)) * (px_1<px_2?1:-1), py_2 + (factor * std::sin(phi)) * (py_1<py_2?1:-1)));
				}
			}
		}

		(*it)->render(window, dt);
	}
}
