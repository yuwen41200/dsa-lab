/**
 * Introduction to Algorithms 2016 Spring
 * Homework #4 Dynamic Programming
 * by Yu-wen Pwu (rev1)
 */

#include <fstream>
#include <limits>
#include <msgpack.hpp>
#include <string>
#include <sys/stat.h>

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
	msgpack::packer<msgpack::sbuffer> packer(&sbuf);

	int count;
	msgpack::unpack(result, data, len, off);
	result.get().convert(&count);

	for (int i = 0; i < count; i++) {
		int length;
		msgpack::unpack(result, data, len, off);
		result.get().convert(&length);

		msgpack::unpack(result, data, len, off);
		msgpack::object_array arr_obj = result.get().via.array;
		assert(arr_obj.size == length);

		long arr[length];
		for (int j = 0; j < length; j++)
			(arr_obj.ptr[j]).convert(&arr[j]);

		int query;
		msgpack::unpack(result, data, len, off);
		result.get().convert(&query);
		packer.pack_array((uint32_t) query);

		for (int j = 0; j < query; j++) {
			msgpack::unpack(result, data, len, off);
			arr_obj = result.get().via.array;
			assert(arr_obj.size == 2);

			int begin, end;
			(arr_obj.ptr[0]).convert(&begin);
			(arr_obj.ptr[1]).convert(&end);

			long max_sum = std::numeric_limits<long>::min();
			long curr_sum = 0;

			for (int k = begin - 1; k < end; k++) {
				curr_sum += arr[k];
				if (curr_sum > max_sum)
					max_sum = curr_sum;
				if (curr_sum < 0)
					curr_sum = 0;
			}

			packer.pack(max_sum);
		}

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
