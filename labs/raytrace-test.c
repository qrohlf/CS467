#include <FPT.h>
#include <pi.h>
#include <D3d_matrix.h>
#include <limits.h>
#include <vectors.h>
#include <math.h>
#include <light_model_student.h>
#define false 0
#define true 1

// implicit equations:
// unit sphere:
// x^2+y^2+z^2-1 = 0
// hyperboloid:
// x^2/r^2 - y^2/b^2 + z^2/r^2 -1 = 0

// Globals
double VIEW[4][4], VIEW_INV[4][4];
double fov;
double R, G, B;
int VERBOSE = false;

// flatten a 3d point into a 2d representation
void flatten(double p[3]) {
    p[0] = p[0]*(300/tan(fov))/p[2] + 300;
    p[1] = p[1]*(300/tan(fov))/p[2] + 300;
}

//splat
double dot (double a[3], double b[3]) {
    return a[0]*b[0]+a[1]*b[1]+a[2]*b[2];
}

double solve (double a, double b, double c) {
    double i = (-b+sqrt(b*b - 4.0*a*c)) / 2.0*a;
    double j = (-b-sqrt(b*b - 4.0*a*c)) / 2.0*a;
    return fmax(i, j);
}

void render_pixel(double row, double col) {
    double p_world[3], p_object[3];
    double origin_world[3], origin_object[3];

    // set eye point for a screen pixel
    double p_eye[3] = {
        (col - 300)/(300 / tan(fov)),
        (row - 300)/(300 / tan(fov)),
        1
    };
    if (VERBOSE) {
        printf("Eye point:\n");
        printf("x=%f\n", p_eye[0]);
        printf("y=%f\n", p_eye[1]);
        printf("z=%f\n", p_eye[2]);
    }
    // set eye origin - eye is always (0,0,0) in eyespace
    double origin_eye[3] = {0, 0, 0};

    // get the world point and world origin for a screen pixel
    D3d_mat_mult_pt(p_world, VIEW_INV, p_eye);
    D3d_mat_mult_pt(origin_world, VIEW_INV, origin_eye);
    if (VERBOSE) {
        printf("\n");
        printf("World point:\n");
        printf("x=%f\n", p_world[0]);
        printf("y=%f\n", p_world[1]);
        printf("z=%f\n", p_world[2]);
        printf("World origin:\n");
        printf("x=%f\n", origin_world[0]);
        printf("y=%f\n", origin_world[1]);
        printf("z=%f\n", origin_world[2]);
    }

    // test sphere matrix
    double obj_mat[4][4], obj_inv[4][4];
    D3d_make_identity(obj_mat);
    D3d_make_identity(obj_inv);
    D3d_scale(obj_mat, obj_inv, 10, 10, 10);
    D3d_translate(obj_mat, obj_inv, 0, 0, 100);

    // get the object point and object origin for a screen pixel
    D3d_mat_mult_pt(p_object, obj_inv, p_world);
    D3d_mat_mult_pt(origin_object, obj_inv, origin_world);
    // get the vector from object origin to object point
    double v_object[3] = {
        p_object[0] - origin_object[0],
        p_object[1] - origin_object[1],
        p_object[2] - origin_object[2]
    };
    // unit_vector(v_object, v_object);

    if (VERBOSE) {
        printf("\n");
        printf("Object point:\n");
        printf("x=%f\n", p_object[0]);
        printf("y=%f\n", p_object[1]);
        printf("z=%f\n", p_object[2]);
        printf("Object origin:\n");
        printf("x=%f\n", origin_object[0]);
        printf("y=%f\n", origin_object[1]);
        printf("z=%f\n", origin_object[2]);
        printf("Object vector:\n");
        printf("x=%f\n", v_object[0]);
        printf("y=%f\n", v_object[1]);
        printf("z=%f\n", v_object[2]);
    }

    // apply the quadratic formula
    double a = dot(v_object, v_object);
    double b = 2*dot(p_object, v_object);
    double c = dot(p_object, p_object)-1;

    // printf("a: %f b: %f c: %f\n", a, b, c);

    // get the discriminant
    double discriminant = pow(b, 2) - 4*a*c;
    // printf("discriminant: %f\n", discriminant);

    //testing
    if (discriminant > 0) {
        double t = solve(a,b,c);
        double p[3] = {t*p_eye[0], t*p_eye[1], t*p_eye[2]}; // point in eyespace
        double n[3] = {t*p_object[0], t*p_object[1], t*p_object[2]}; // intersection point of object is also the normal vector for spheres
        double irgb[3] = {0, 1, 1};     // Inherent color of object
        double argb[3];                 // Actual color of object
        double s[3] = {0, 0, 0};        // "s = location of start of ray"
        D3d_mat_mult_pt(n, obj_mat, n);
        D3d_mat_mult_pt(n, VIEW, n);
        nu_light_model(irgb, s, p, n, argb);
        G_rgb(argb[0], argb[1], argb[2]);
        G_point(col, row);
    }

}

// usage: lab2.1 [prefix] [framenumber]
int main(int argc, char const *argv[]) {

    if (argc > 1) {
        VERBOSE = true;
    }

    //Initialize the graphics
    G_init_graphics(600, 600);    

    //Black background
    G_rgb(0, 0, 0);
    G_clear();

    //Constants
    AMBIENT  = 0.2 ;
    MAX_DIFFUSE = 0.5 ;
    SPECPOW = 100 ;
    fov = 25 * M_PI/180;
    double eye[3] = {0, 0, 0};
    double coi[3] = {0, 0, 1};
    double up[3] = {0, 1, 0};
    D3d_view(VIEW, VIEW_INV, eye, coi, up); 

    // Testing
    for (double row=0; row < 600; row++) {
        for (double col=0; col < 600; col++) {
            // printf("Tracing ray through col=%f row=%f\n", col, row);
            render_pixel(row, col);
        }
    }

    //Show result then close
    G_wait_key();
    G_close();
    return 0;
}