/**
 * Introduction to Algorithms 2016 Spring
 * Homework #6 Minimal Cover
 * by Yu-wen Pwu (rev1)
 */

#include <cmath>
#include <cstdio>
#include <utility>

int main() {
	FILE *input = fopen("input.txt", "r");
	FILE *output = fopen("output.txt", "w");
	if (!input || !output) {
		perror("cannot open files");
		return 1;
	}

	int circle, length, width;
	while (fscanf(input, "%d %d %d", &circle, &length, &width) == 3) {
		std::pair<float, float> *range = new std::pair<float, float>[circle];
		for (int i = 0; i < circle; ++i) {
			int position, radius;
			fscanf(input, "%d %d", &position, &radius);
			if (radius <= width / 2.0f)
				continue;
			float project = sqrtf(powf(radius, 2) - powf(width / 2.0f, 2));
			range[i] = std::make_pair(position - project, position + project);
		}

		// TODO: sort range by its second element
	}

	fclose(input);
	fclose(output);
	return 0;
}
