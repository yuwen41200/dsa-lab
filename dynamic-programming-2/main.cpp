/**
 * Introduction to Algorithms 2016 Spring
 * Homework #5 Dynamic Programming 2
 * by Yu-wen Pwu (rev1)
 */

#include <fstream>
#include <msgpack.hpp>
#include <sstream>
#include <string>
#include <sys/stat.h>
#include <unordered_set>

typedef std::unordered_set<int>(*fp)(std::unordered_set<int>, std::unordered_set<int>);
inline int operand_count(std::string);
std::unordered_set<int> add(std::unordered_set<int>, std::unordered_set<int>);
std::unordered_set<int> subtract(std::unordered_set<int>, std::unordered_set<int>);
std::unordered_set<int> multiply(std::unordered_set<int>, std::unordered_set<int>);
std::unordered_set<int> bit_and(std::unordered_set<int>, std::unordered_set<int>);
std::unordered_set<int> bit_or(std::unordered_set<int>, std::unordered_set<int>);

int main() {
	std::fstream is("input.txt", std::ios::in | std::ios::binary);
	assert(is.is_open());

	struct stat st;
	stat("input.txt", &st);
	size_t len = (size_t) st.st_size;

	char *data = new char[len];
	is.read(data, len);
	assert(is.good());
	is.close();

	msgpack::unpacked result;
	size_t off = 0;
	msgpack::sbuffer sbuf;

	int count;
	msgpack::unpack(result, data, len, off);
	result.get().convert(&count);

	for (int i = 0; i < count; i++) {
		// TODO: This has fucking high complexity !!! Better solution ?
		/**
		 * ######################### Algorithm #########################
		 * ans[i][j] : The set of all possible answers for operand i..j
		 *     op[i] : operator i
		 * -------------------------------------------------------------
		 * ans[i][j] = op[k](ans[i][k], ans[k+1][j]) where i <= k < j
		 * ########################## Example ##########################
		 * Input : 1 + 3 * 4
		 * -------------------------------------------------------------
		 * ans[0][0] = { 1 }
		 * ans[1][1] = { 3 }
		 * ans[2][2] = { 4 }
		 * op[0] = +
		 * op[1] = *
		 * ans[0][1] = { +(1, 3) } = { 4 }
		 * ans[1][2] = { *(3, 4) } = { 12 }
		 * ans[0][2] = { +(1, 12), *(4, 4) } = { 13, 16 }
		 * -------------------------------------------------------------
		 * Output : 2
		 * ########################## Example ##########################
		 * Input : 3 + 4 * 1
		 * -------------------------------------------------------------
		 * ans[0][0] = { 3 }
		 * ans[1][1] = { 4 }
		 * ans[2][2] = { 1 }
		 * op[0] = +
		 * op[1] = *
		 * ans[0][1] = { +(3, 4) } = { 7 }
		 * ans[1][2] = { *(4, 1) } = { 4 }
		 * ans[0][2] = { +(3, 4), *(7, 1) } = { 7 }
		 * -------------------------------------------------------------
		 * Output : 1
		 * #############################################################
		 */

		std::string expression;
		msgpack::unpack(result, data, len, off);
		result.get().convert(&expression);

		int length = operand_count(expression);
		std::unordered_set<int>** ans = new std::unordered_set<int>*[length];
		for (int j = 0; j < length; ++j)
			ans[j] = new std::unordered_set<int>[length-j];
		fp* op = new fp[length-1];

		std::stringstream ss(expression);
		std::string operation;
		int operand;
		int k = 0;
		ss >> operand;
		ans[k][0].insert(operand);
		while (!ss.eof()) {
			ss >> operation;
			switch (operation[0]) {
				case '+' : op[k] = add; break;
				case '-' : op[k] = subtract; break;
				case '*' : op[k] = multiply; break;
				case '&' : op[k] = bit_and; break;
				default  : op[k] = bit_or; break;
			}
			ss >> operand;
			ans[++k][0].insert(operand);
		}
		assert(k + 1 == length);

		for (int l = 1; l < length; ++l) {
			for (int m = 0; m < length - l; ++m) {
				int n = m + l;
				for (int j = m; j < n; ++j)
					ans[m][n-m] = op[j](ans[m][j-m], ans[j+1][n-j-1]);
			}
		}
		msgpack::pack(sbuf, ans[0][length-1].size());

		for (int j = 0; j < length; ++j)
			delete[] ans[j];
		delete[] ans;
		delete[] op;
	}
	assert(off == len);

	std::fstream os("output.txt", std::ios::out | std::ios::binary | std::ios::trunc);
	assert(os.is_open());

	os.write(sbuf.data(), sbuf.size());
	assert(os.good());
	os.close();

	delete[] data;
	return 0;
}

inline int operand_count(std::string str) {
	int count = 0;
	for (size_t i = 0; i < str.length(); ++i)
		if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '&' || str[i] == '|')
			count++;
	return count + 1;
}

std::unordered_set<int> add(std::unordered_set<int> a, std::unordered_set<int> b) {
	std::unordered_set<int> c;
	for (auto i = a.begin(); i != a.end(); ++i)
		for (auto j = b.begin(); j != b.end(); ++j)
			c.insert(*i + *j);
	return c;
}

std::unordered_set<int> subtract(std::unordered_set<int> a, std::unordered_set<int> b) {
	std::unordered_set<int> c;
	for (auto i = a.begin(); i != a.end(); ++i)
		for (auto j = b.begin(); j != b.end(); ++j)
			c.insert(*i - *j);
	return c;
}

std::unordered_set<int> multiply(std::unordered_set<int> a, std::unordered_set<int> b) {
	std::unordered_set<int> c;
	for (auto i = a.begin(); i != a.end(); ++i)
		for (auto j = b.begin(); j != b.end(); ++j)
			c.insert(*i * *j);
	return c;
}

std::unordered_set<int> bit_and(std::unordered_set<int> a, std::unordered_set<int> b) {
	std::unordered_set<int> c;
	for (auto i = a.begin(); i != a.end(); ++i)
		for (auto j = b.begin(); j != b.end(); ++j)
			c.insert(*i & *j);
	return c;
}

std::unordered_set<int> bit_or(std::unordered_set<int> a, std::unordered_set<int> b) {
	std::unordered_set<int> c;
	for (auto i = a.begin(); i != a.end(); ++i)
		for (auto j = b.begin(); j != b.end(); ++j)
			c.insert(*i | *j);
	return c;
}
