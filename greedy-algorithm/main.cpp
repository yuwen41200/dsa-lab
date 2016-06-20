/**
 * Introduction to Algorithms 2016 Spring
 * Homework #6 Minimal Cover
 * by Yu-wen Pwu (rev1)
 */

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <utility>

typedef std::pair<double, double> Range;

int compare(const void*, const void*);

int main() {
	FILE *input = fopen("input.txt", "r");
	FILE *output = fopen("output.txt", "w");
	if (!input || !output) {
		perror("cannot open files");
		return 1;
	}

	int circle, length, width;
	while (fscanf(input, "%d %d %d", &circle, &length, &width) == 3) {
		Range *range = new Range[circle];
		int valid = 0;

		for (int i = 0; i < circle; ++i) {
			int position, radius;
			fscanf(input, "%d %d", &position, &radius);
			if (radius <= width / 2.0)
				continue;
			double projection = sqrt(pow(radius, 2) - pow(width / 2.0, 2));
			if (position - projection >= length)
				continue;
			range[valid++] = std::make_pair(position - projection, position + projection);
		}

		// sort range by its second element in decreasing order
		qsort(range, valid, sizeof(Range), compare);

		int i = 0, sum = 0;
		double margin = 0;
		while (margin < length && i < valid) {
			// printf("%d -> (%f, %f)\n", i, range[i].first, range[i].second);
			if (range[i].first <= margin) {
				margin = range[i].second;
				valid = i;
				i = 0;
				++sum;
			}
			else {
				++i;
			}
		}

		delete [] range;
		sum = (margin >= length) ? sum : -1;
		fprintf(output, "%d\n", sum);
	}

	fclose(input);
	fclose(output);
	return 0;
}

int compare(const void *a, const void *b) {
	if (((Range*) a)->second == ((Range*) b)->second)
		return (int) (((Range*) a)->first - ((Range*) b)->first);
	else
		return (int) (((Range*) b)->second - ((Range*) a)->second);
}
