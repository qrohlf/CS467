#include "vectors.h"
#include "D3d_matrix.h"

void unit_vector(double a[3], double b[3]) {
    double m = magnitude(a);
    b[0] = a[0]/m;
    b[1] = a[1]/m;
    b[2] = a[2]/m;
}

double magnitude(double vec[3]) {
    return sqrt(pow(vec[0], 2)+pow(vec[1], 2)+pow(vec[2], 2));
}

void cross_product(double a[3], double b[3], double c[3]) {
    D3d_x_product(c, a, b);
}