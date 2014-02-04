#include <FPT.h>
#include <D3d_matrix.h>
#include <limits.h>

/*
Sphere: 
x^2+y^2+z^2-1=0

Parametric form:
x = cos(u)*cos(v)
y = sin(u)
z = cos(u)*sin(v)
*/

// Globals

double h = .001;
int Z_BUF[600][600];


// Equation for a sphere
void sphere(double p[3], double u, double v) {
    p[0] = cos(u)*cos(v);
    p[1] = sin(u);
    p[2] = cos(u)*sin(v);
}

// gives the unit vector for the normal vector of func at u, v
void normal(void (*func)(double[3], double, double), double m[4][4], double u, double v, double vec[3]) {

}

void graph(void (*func)(double[3], double, double), double m[4][4], double start, double end, double interval) {
    double p[3];
    for (double u=start; u<end; u+=interval) {
        // (*func)(p, u);
        // D3d_mat_mult_pt(p, m, p);
        // G_point(p[0], p[1]);
    }
}

int main(int argc, char const *argv[]) {
    G_init_graphics(600, 600);
    G_rgb(0, 0, 0);
    G_clear();

    //Initialize the Z-buffer
    for (int x=0; x<600; x++) {
        for (int y=0; y<600; y++) {
            Z_BUF[x][y] = INT_MAX;
        }
    }

    G_wait_key();
    return 0;
}