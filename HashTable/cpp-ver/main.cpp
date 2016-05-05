/**
 * Introduction to Algorithms 2016 Spring
 * Homework #3 Same Pattern
 * by Yu-wen Pwu (cpp-ver)
 */

#include <fstream>
#include <msgpack.hpp>
#include <string>
#include <sys/stat.h>

std::string map[26];

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
		std::string pattern;
		msgpack::unpack(result, data, len, off);
		result.get().convert(&pattern);
		unsigned long length = pattern.length();

		int wordLength;
		msgpack::unpack(result, data, len, off);
		msgpack::object_array wordArray = result.get().via.array;
		wordLength = wordArray.size;

		if (wordLength != length) {
			msgpack::pack(sbuf, (int) 0);
			continue;
		}

		for (int j = 0; j < 26; j++)
			map[j].clear();
		int match = 1;

		for (int j = 0; j < length; j++) {
			int key = pattern[j] - 'a';
			std::string value;
			(wordArray.ptr[j]).convert(&value);

			if (match == 1 && map[key].empty()) {
				for (int k = 0; k < 26; k++)
					if (!map[k].empty() && map[k] == value) {
						match = 0;
						break;
					}
				map[key] = value;
			}
			else if (match == 1 && map[key] != value)
				match = 0;
		}

		msgpack::pack(sbuf, match);
	}
	assert(len == off);

	std::fstream os("output.txt", std::ios::out | std::ios::binary | std::ios::trunc);
	assert(os.is_open());

	os.write(sbuf.data(), sbuf.size());
	assert(os.good());
	os.close();

	delete[] data;
	return 0;
}
