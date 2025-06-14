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
			float new_x = position.get_x() + dt * velocity.get_x();
			float new_y = position.get_y() + dt * velocity.get_y();

			position.set_x(new_x);
			position.set_y(new_y);

			circle.setPosition(new_x, new_y);

			// update velocity for gravity
			float vx = velocity.get_x();
			float new_vx = vx * exp(-b * dt);
			new_vx = std::abs(new_vx - vx) > 0.001 ? new_vx : 0.0;
			float vy = velocity.get_y();
			float new_vy = vy * exp(-b * dt) + dt * g;
			new_vy = std::abs(new_vy - vy) > 0.001 ? new_vy : 0.0;
			if (new_x < 0 || new_x >= window.getSize().x) new_vx *= -1;
			if (new_y < 0 || new_y >= window.getSize().y) new_vy *= -1;
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