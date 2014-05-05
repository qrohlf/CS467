#include <math.h>
#include "xwd_tools.h"
#define HEIGHT 900
#define WIDTH 900

int black(double rgb[3]) {
	return fabs(rgb[0]) < 0.0001 && fabs(rgb[1]) < 0.0001 && fabs(rgb[2]) < 0.0001;
}

void xwd_copy(int source, int target) {
	double rgb[3];
	for(double x = 0; x < WIDTH; x++) {
		for(double y = 0; y < HEIGHT; y++) {
			get_xwd_map_color(target, x, y, rgb);

			if (!black(rgb)) {
				continue;
			}
			get_xwd_map_color(source, x, y, rgb);
			set_xwd_map_color(target, x, y, rgb[0], rgb[1], rgb[2]);
		}
	}
}

int main(int argc, char const *argv[]) {
	int big_image = init_xwd_map_from_file("output.xwd");
	if (big_image == -1) big_image = create_new_xwd_map(WIDTH, HEIGHT);
	double x_offset;
	double y_offset;
	char sequence_name[100];

	//Read the frame number from argv
	int start = atoi(argv[1]); 
	int end = atoi(argv[2]);

	for (int i=start; i<=end; i++) {
		printf("smashing segment %d\n", i);
		sprintf(sequence_name, "%04d.xwd", i);
		int source = init_xwd_map_from_file(sequence_name);
		xwd_copy(source, big_image);
	}
	xwd_map_to_named_xwd_file(big_image, "output.xwd");
	/* code */
	return 0;
}