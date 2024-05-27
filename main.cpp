#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <string_view>
#include <optional>

#define OCTETS_COUNT 4

using namespace std;

// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]
vector<string_view> split(const string_view str, char d) {
	vector<string_view> r;

	string::size_type start = 0;
	string::size_type stop = str.find_first_of(d);
	while(stop != string::npos) {
		r.push_back(str.substr(start, stop - start));

		start = stop + 1;
		stop = str.find_first_of(d, start);
	}

	r.push_back(str.substr(start));

	return r;
}

typedef vector<uint8_t> IPAddr;

IPAddr ipFromStringView(const string_view str) {
	IPAddr result;
	result.resize(OCTETS_COUNT);
	auto octets = split(str, '.');
	transform(octets.begin(), octets.end(),
			  result.begin(),
			  [](const string_view octet) {
		return atoi(octet.begin());
	});
	return result;
}

ostream& operator<<(ostream &os, const IPAddr &addr) {
	for(int i = 0; i < OCTETS_COUNT; ++i) {
		if (i != 0) {
			os << '.';
		}
		os << to_string(addr[i]);
	}
	return os;
}

int main() {
	try {
		vector<IPAddr> ip_pool;

		for(string line; getline(cin, line);)
		{
			vector<string_view> v = split(line, '\t');
			ip_pool.push_back(ipFromStringView(v.at(0)));
		}

		sort(ip_pool.begin(), ip_pool.end(),
				  [] (const IPAddr &rhs, const IPAddr &lhs) {
			for (int i = 0; i < OCTETS_COUNT; ++i) {
				if (rhs[i] == lhs[i]) {
					continue;
				}
				return rhs[i] > lhs[i];
			}
			return false;
		});

		for(auto ip = ip_pool.cbegin(); ip != ip_pool.cend(); ++ip)
		{
			cout << *ip << '\n';
		}

		// 222.173.235.246
		// 222.130.177.64
		// 222.82.198.61
		// ...
		// 1.70.44.170
		// 1.29.168.152
		// 1.1.234.8

		// TODO filter by first byte and output
		// ip = filter(1)
		auto filter = [&ip_pool](uint8_t filter1, optional<uint8_t> filter2 = nullopt) {
			for (const auto &addr : ip_pool) {
				if ((addr.at(0) == filter1) &&
						(!filter2.has_value() || (addr.at(1) == filter2.value()))) {
					cout << addr << '\n';
				}
			}
		};
		filter(1);

		// 1.231.69.33
		// 1.87.203.225
		// 1.70.44.170
		// 1.29.168.152
		// 1.1.234.8

		// TODO filter by first and second bytes and output
		// ip = filter(46, 70)

		filter(46, 70);

		// 46.70.225.39
		// 46.70.147.26
		// 46.70.113.73
		// 46.70.29.76

		// TODO filter by any byte and output
		// ip = filter_any(46)
		auto filter_any = [&ip_pool](uint8_t filter) {
			for (const auto &addr : ip_pool) {
				for (int i = 0; i < OCTETS_COUNT; ++i) {
					if (addr.at(i) == filter) {
						cout << addr << '\n';
						break;
					}
				}
			}
		};

		filter_any(46);

		// 186.204.34.46
		// 186.46.222.194
		// 185.46.87.231
		// 185.46.86.132
		// 185.46.86.131
		// 185.46.86.131
		// 185.46.86.22
		// 185.46.85.204
		// 185.46.85.78
		// 68.46.218.208
		// 46.251.197.23
		// 46.223.254.56
		// 46.223.254.56
		// 46.182.19.219
		// 46.161.63.66
		// 46.161.61.51
		// 46.161.60.92
		// 46.161.60.35
		// 46.161.58.202
		// 46.161.56.241
		// 46.161.56.203
		// 46.161.56.174
		// 46.161.56.106
		// 46.161.56.106
		// 46.101.163.119
		// 46.101.127.145
		// 46.70.225.39
		// 46.70.147.26
		// 46.70.113.73
		// 46.70.29.76
		// 46.55.46.98
		// 46.49.43.85
		// 39.46.86.85
		// 5.189.203.46
	} catch(const exception &e) {
		cerr << e.what() << endl;
	}

	return 0;
}
