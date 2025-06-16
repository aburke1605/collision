#pragma once

template <typename T>
class vec {
	private:
		T x;
		T y;

	public:
		vec(): x(0), y(0) {}
		vec(T X, T Y): x(X), y(Y) {}
		T get_x() {return x;}
		T get_y() {return y;}
		void set_x(T X) {x = X;}
		void set_y(T Y) {y = Y;}
};
