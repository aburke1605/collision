#include <cmath>

#include <SFML/Graphics.hpp>


#define dt 0.025
#define g  9.8
#define b  0.1 // air resistance

void parse_user_input(sf::RenderWindow& window) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
				window.close();
		}
}

template <typename T> class vec {
	private:
		T x;
		T y;

	public:
		vec() = default;
		vec(T X, T Y) {
			x = X;
			y = Y;
		}
		T get_x() {return x;}
		T get_y() {return y;}
		void set_x(T X) {x = X;}
		void set_y(T Y) {y = Y;}
};

class ball {
	private:
		sf::CircleShape circle;
		vec<float> position;
		vec<float> velocity;

	public:
		ball() {
			position = vec<float>(10.0, 10.0);
			velocity = vec<float>(1.0, 1.0);

			circle = sf::CircleShape(10.0);
			circle.setPosition(5.0, 5.0);
			circle.setFillColor(sf::Color::White);
		}

		const sf::Shape& get_shape_handle() {
			return circle;
		}
		const vec<float> get_position() {
			return position;
		}
		const vec<float> get_velocity() {
			return velocity;
		}

		void update(sf::RenderWindow& window) {
			// update velocity first for gravity and air resistance
			float new_vx = velocity.get_x() * exp(-b * dt);
			float new_vy = (velocity.get_y() + g * dt) * exp(-b * dt);

			// update position using new velocity
			float new_px = position.get_x() + new_vx * dt;
			float new_py = position.get_y() + new_vy * dt;
			
			// check for out of boundary and bounce back
			if (new_px < 0 || new_px >= window.getSize().x) {
				new_vx = -new_vx;
				new_px = new_px < 0 ? -new_px : -new_px + 2 * window.getSize().x;
			}
			if (new_py < 0 || new_py >= window.getSize().y) {
				new_vy = -new_vy;
				new_py = new_py < 0 ? -new_py : -new_py + 2 * window.getSize().y;
			}

			// apply changes
			position.set_x(new_px);
			position.set_y(new_py);
			circle.setPosition(new_px, new_py);
			velocity.set_x(new_vx);
			velocity.set_y(new_vy);
		}

		void render(sf::RenderWindow& window) {
			update(window);
			window.draw(circle);
		}
};

class scene {
	private:
		ball _b;
	public:
		scene() {}
		void update(sf::RenderWindow& window) {
			_b.render(window);
		}

};

int main() {

	uint width, height;
	width = height= 500;
	sf::RenderWindow window(sf::VideoMode(width, height), "collision");

	scene scene;
	while (window.isOpen()) {
		window.clear();
		parse_user_input(window);
		scene.update(window);
		window.display();
	}

	return 0;
}