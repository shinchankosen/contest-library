class random_devicer {
	int seed;
	std::mt19937 engine;

public:
	random_devicer(const int seed = 0): seed(seed), engine(seed) {}

	// [lower, upper] 中の整数から一様ランダムに選ぶ。
	int next(int lower, int upper) {
		std::uniform_int_distribution<> dist(lower, upper);
		return dist(engine);
	}
	std::vector<int> next(int n, int lower, int upper) {
		std::vector<int> a(n);
		for(auto& e: a) e = next(lower, upper);
		return std::move(a);
	}

	bool next_bool() { return next(0, 1); }

	// [lower, upper] 中の実数から一様ランダムに選ぶ。
	double next_double(double lower, double upper) {
		std::uniform_real_distribution<> dist(lower, upper);
		return dist(engine);
	}

	// char
	char next_char_lower_case() { return next('a', 'z'); }
	char next_char_upper_case() { return next('A', 'Z'); }
	char next_char() {
		if(next_bool()) return next_char_lower_case();
		return next_char_upper_case();
	}
	char next_char(const std::string& chars) {
		assert(not chars.empty());
		return chars[next(0, chars.size() - 1)];
	}

	// string
	std::string next_string_lower_case(const int len) {
		std::string s(len, ' ');
		for(auto& c: s) c = next_char_lower_case();
		return std::move(s);
	}
	std::string next_string_upper_case(const int len) {
		std::string s(len, ' ');
		for(auto& c: s) c = next_char_upper_case();
		return std::move(s);
	}
	std::string next_string(const int len) {
		std::string s(len, ' ');
		for(auto& c: s) c = next_char();
		return std::move(s);
	}
	std::string next_string(const int len, const std::string& chars) {
		std::string s(len, ' ');
		for(auto& c: s) c = next_char(chars);
		return std::move(s);
	}

	// 頂点数 order の木を生成する。
	// p[i] := 頂点 i + 1 の親
	std::vector<int> next_tree(const int order) {
		std::vector<int> p(order - 1);
		for(size_t i = 0; i < p.size(); i++) p[i] = next(0, i);
		return std::move(p);
	}

	// 頂点数 order 辺数 size のグラフを生成する。
	std::vector<std::pair<int, int>> next_graph(const int order, const int size,
								bool is_connected = true,
								bool is_simple = true)
	{
		std::vector<std::pair<int, int>> edges;
		std::set<std::pair<int, int>> edges_set;
		if(is_connected) {
			assert(order - 1 <= size);

			auto p = next_tree(order);
			for(size_t i = 0; i < p.size(); i++) {
				edges.push_back({p[i], i + 1});
				edges_set.insert({p[i], i + 1});
				edges_set.insert({i + 1, p[i]});
			}
		}

		while((int)edges.size() != size) {
			if(is_simple) {
				int a = next(0, order - 1);
				int b = next(a + 1, order - 1);
				if(edges_set.count({a, b})) continue;

				edges.push_back({a, b});
				edges_set.insert({a, b});
				edges_set.insert({b, a});
			} else {
				int a = next(0, order - 1);
				int b = next(0, order - 1);

				edges.push_back({a, b});
				edges_set.insert({a, b});
				edges_set.insert({b, a});
			}
		}

		return std::move(edges);
	}

	// 頂点数 order のなもりグラフを生成する。
	std::vector<std::pair<int, int>> next_namori(const int order) {
		return next_graph(order, order);
	}
};

// random_devicer rnd(seed);
// rnd.next(0, n) [0, n]