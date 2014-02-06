#include <FPT.h>
#include <D3d_matrix.h>
#include <limits.h>
#include <vectors.h>



// Globals
double h = .001;
double Z_BUF[600][600];
double fov;
double R, G, B;

// Globals from light model
extern double light_in_eye_space[3] ;
extern double AMBIENT;
extern double MAX_DIFFUSE;
extern double SPECPOW;


// Equation for a sphere
void sphere(double p[3], double u, double v) {
    /*
    Sphere: 
    x^2+y^2+z^2-1=0

    Parametric form:
    x = cos(u)*cos(v)
    y = sin(u)
    z = cos(u)*sin(v)

    u from 0 to 2pi
    v from -pi/2 to pi/2
    */
    p[0] = cos(u)*cos(v);
    p[1] = sin(u);
    p[2] = cos(u)*sin(v);
}

// gives the unit vector for the normal vector of func at u, v
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
    x2 = p[0]; y2 = p[2]; z2 = p[2];
    uvec[0] = x2-x1;
    uvec[1] = y2-y1;
    uvec[2] = z2-z1;

    //compute slope in v direction
    (*func)(p, u, v);
    D3d_mat_mult_pt(p, m, p);
    x1 = p[0]; y1 = p[1]; z1 = p[2];
    (*func)(p, u, v+.001);
    D3d_mat_mult_pt(p, m, p);
    x2 = p[0]; y2 = p[2]; z2 = p[2];
    vvec[0] = x2-x1;
    vvec[1] = y2-y1;
    vvec[2] = z2-z1;
    cross_product(uvec, vvec, vec);
    unit_vector(vec, vec);
}

void set_color(double a, double b, double c) {
    R = a;
    G = b;
    B = c;
    G_rgb(R, G, B);
}

// flatten a 3d point into a 2d representation
void flatten(double p[3]) {
    p[0] = p[0]*(300/tan(fov))/p[2] + 300;
    p[1] = p[1]*(300/tan(fov))/p[2] + 300;
}

void graph_sphere(double m[4][4], double interval) {
    double p[3];
    double irgb[3] = {R, G, B};     // Inherent color of object
    double argb[3];                 // Actual color of object
    double s[3] = {0, 0, 0};        // "s = location of start of ray"
    double n[3];               // normal vector
    for (double u=0; u<M_PI*2.0; u+=interval) {
        for (double v= -M_PI/2.0; v<M_PI/2.0; v+=interval) {
            sphere(p, u, v);
            D3d_mat_mult_pt(p, m, p);
            normal(&sphere, m, u, v, n);
            nu_light_model(irgb, s, p, n, argb);
            G_rgb(argb[0], argb[1], argb[2]);
            // printf("u: %f v: %f x: %f y: %f z: %f ", u, v, p[0], p[1], p[2]);
            flatten(p);
            // check the z-buffer
            // printf("previous z-val at %d %d: %f\n", (int)p[0], (int)p[1], Z_BUF[(int)p[0]][(int)p[1]]);
            // printf("current z-val: %f\n", p[2]);
            if (Z_BUF[(int)p[0]][(int)p[1]] > p[2]) {
                // update the z-buffer
                Z_BUF[(int)p[0]][(int)p[1]] = p[2];
                // draw stuff
                G_point(p[0], p[1]);
            };
            
            // printf("x': %f y': %f \n", u, v, p[0], p[1], p[2]);
        }
    }
    set_color(R, G, B); //Reset the color to what it was before the light model
}

int main(int argc, char const *argv[]) {
    G_init_graphics(600, 600);
    set_color(0, 0, 0);
    G_clear();
    set_color(0, 1, 1);
    //Initialize the Z-buffer
    for (int x=0; x<600; x++) {
        for (int y=0; y<600; y++) {
            Z_BUF[x][y] = 9999999999999;
        }
    }

    //Set up light
    light_in_eye_space[0] = 100 ; light_in_eye_space[1] = 200 ; light_in_eye_space[2] = -50 ;
    AMBIENT  = 0.2 ;
    MAX_DIFFUSE = 0.5 ;
    SPECPOW = 80 ;

    //Set up view
    fov = M_PI/8.0;

    double m[4][4], minv[4][4];

    D3d_make_identity(m);
    D3d_translate(m, minv, 0, 0, 10);

    graph_sphere(m, .01);

    G_wait_key();
    return 0;
}