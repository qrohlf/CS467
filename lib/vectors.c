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

double dot_product_2d(double a[2], double b[2]) {
    return a[0]*b[0] + a[1]*b[1];
}

//vec = a-b;
void vector_subtract(double a[3], double b[3], double vec[3]) {
    vec[0] = a[0] - b[0];
    vec[1] = a[1] - b[1];
    vec[2] = a[2] - b[2];
}

// gives the unit vector for the normal vector of func at u, v
// (where func is a parametric function with the signature void func(result[x, y, z], u, v))
void normal(void (*func)(double[3], double, double), double m[4][4], double u, double v, double vec[3]) {
    double p[3]; // used to store points
    double uvec[3]; // slope vector in u direction
    double vvec[3]; // slope vector in v direction
    double x1, y1, z1, x2, y2, z2;

    //compute slope in u direction
    (*func)(p, u, v);
    D3d_mat_mult_pt(p, m, p);
    x1 = p[0]; y1 = p[1]; z1 = p[2];
    (*func)(p, u+.001, v);
    D3d_mat_mult_pt(p, m, p);
    x2 = p[0]; y2 = p[1]; z2 = p[2];
    uvec[0] = x2-x1;
    uvec[1] = y2-y1;
    uvec[2] = z2-z1;

    //compute slope in v direction
    (*func)(p, u, v);
    D3d_mat_mult_pt(p, m, p);
    x1 = p[0]; y1 = p[1]; z1 = p[2];
    (*func)(p, u, v+.001);
    D3d_mat_mult_pt(p, m, p);
    x2 = p[0]; y2 = p[1]; z2 = p[2];
    vvec[0] = x2-x1;
    vvec[1] = y2-y1;
    vvec[2] = z2-z1;
    cross_product(uvec, vvec, vec);
    unit_vector(vec, vec);
}