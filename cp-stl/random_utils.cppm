export module random_utils;

import std;

export template <typename T>
std::vector<T> get_random_data(size_t times, T lower, T upper) {
	static std::random_device rd;
	static std::mt19937 gen(rd());

	std::vector<T> res;
	res.reserve(times);

	if constexpr (std::is_integral_v<T>) {
		std::uniform_int_distribution<T> dist(lower, upper);
		for (size_t i = 0; i < times; ++i) res.push_back(dist(gen));
	}
	else {
		std::uniform_real_distribution<T> dist(lower, upper);
		for (size_t i = 0; i < times; ++i) res.push_back(dist(gen));
	}

	return res;
}

export template <typename T, typename Generator>
std::vector<T> get_custom_data(size_t times, Generator gen_func) {
	std::vector<T> res;
	res.reserve(times);

	for (size_t i = 0; i < times; ++i) res.push_back(gen_func());

	return res;
}