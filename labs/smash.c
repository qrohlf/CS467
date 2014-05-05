#include "xwd_tools.h"
#define HEIGHT 6000
#define WIDTH 6000


void xwd_copy(double x_offset, double y_offset, int source, int target) {
	double rgb[3];
	for(double x = 0; x < WIDTH/10; x++) {
		for(double y = 0; y < HEIGHT/10; y++) {
			get_xwd_map_color(source, x, y, rgb);
			set_xwd_map_color(target, x+x_offset, y+y_offset, rgb[0], rgb[1], rgb[2]);
		}
	}
}

int main(int argc, char const *argv[]) {
	int big_image = create_new_xwd_map(WIDTH, HEIGHT);
	double x_offset;
	double y_offset;
	for (int i=0; i<100; i++) {
		printf("smashing segment %d\n", i);
		x_offset = (i%10)*WIDTH/10;
		y_offset = (i/10)*HEIGHT/10;
		int source = init_xwd_map_from_file("0001.xwd");
		xwd_copy(x_offset, y_offset, source, big_image);
	}
	xwd_map_to_named_xwd_file(big_image, "output.xwd");
	/* code */
	return 0;
}