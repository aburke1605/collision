#include <SFML/Graphics.hpp>

#define dt 0.1

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

		void update() {
			float new_x = position.get_x() + dt * velocity.get_x();
			float new_y = position.get_y() + dt * velocity.get_y();

			position.set_x(new_x);
			position.set_y(new_y);

			circle.setPosition(new_x, new_x);
		}

		void render(sf::RenderWindow& window) {
			update();
			window.draw(circle);
		}
};

class scene {
	private:
		ball b;
	public:
		scene() {}
		void update(sf::RenderWindow& window) {
			b.render(window);
		}

};

int main() {

	float width, height;
	width = height= 500.0;
	sf::RenderWindow window(sf::VideoMode(width, height), "collision");

	scene scene;
	while (window.isOpen()) {
		parse_user_input(window);
		scene.update(window);
		window.display();
	}

	return 0;
}