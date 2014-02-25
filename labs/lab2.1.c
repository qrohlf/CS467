#include <FPT.h>
#include <pi.h>
#include <D3d_matrix.h>
#include <limits.h>
#include <vectors.h>
#include <light_model_student.h>


// Globals
double Z_BUF[600][600];
double VIEW[4][4], VIEW_INV[4][4];
double fov;
double R, G, B;

// test value: .03
// render value: .003
double hyperboloid_interval = .003;
// test value: .05
// render value: .005
double sphere_interval = .005;


// Equation for a sphere
void sphere(double p[3], double u, double v) {
    p[0] = cos(u)*cos(v);
    p[1] = sin(u);
    p[2] = cos(u)*sin(v);
}

void hyperboloid(double p[3], double u, double v) {
    const static double H = 1;  
    const static double r = .25; //small radius
    const static double R = 1;  //large radius
    double b = sqrt((pow(r, 2)*pow(H, 2))/(pow(R,2)-pow(r,2)));
    double d = (r/b)*sqrt(pow(u, 2)+pow(b, 2));
    p[0] = d*cos(v);
    p[1] = u;
    p[2] = d*sin(v);
}

// Equation for the path of the camera
void path (int frame_number, double path_xyz[3])
{
  double u,v,r ;
  double x,y,z ;

  u = 5*frame_number*M_PI/180 ;
  v = 0.3*u ;
  r = 2.0 + 1.4*sin(u) ;

  x = r*cos(u)*cos(v) ;
  y = r*sin(u) ;
  z = r*cos(u)*sin(v) ;
 
  path_xyz[0] = x ;
  path_xyz[1] = y ;
  path_xyz[2] = z ;

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

void graph(
    void (*func)(double[3], double, double), 
    double m[4][4], 
    double interval, 
    double u0, 
    double uf, 
    double v0, 
    double vf) {
    double p[3];
    double irgb[3] = {R, G, B};     // Inherent color of object
    double argb[3];                 // Actual color of object
    double s[3] = {0, 0, 0};        // "s = location of start of ray"
    double n[3];                    // normal vector
    for (double u=u0; u<uf; u+=interval) {
        for (double v= v0; v<vf; v+=interval) {
            (*func)(p, u, v);
            D3d_mat_mult_pt(p, m, p);
            normal(func, m, u, v, n);
            nu_light_model(irgb, s, p, n, argb);
            G_rgb(argb[0], argb[1], argb[2]);

            // printf("point: %f %f %f -> ", p[0], p[1], p[2]);
            flatten(p);
            // printf("%d %d\n", (int)p[0], (int)p[1]);
            // check the z-buffer
            if (p[0] >= 600 || p[0] < 0 || p[1] >= 600 || p[1] < 0) {
                // printf("point out of bounds\n");
                continue;
            }
            if (Z_BUF[(int)p[0]][(int)p[1]] > p[2]) {
                // update the z-buffer
                Z_BUF[(int)p[0]][(int)p[1]] = p[2]; 
                // draw stuff
                G_point(p[0], p[1]);
            };
        }
    }
    set_color(R, G, B); //Reset the color to what it was before the graphing
}

// graph a sphere of radius r at point p
void sphere_at(double p[3], double r) {
    double m[4][4], m_inv[4][4];
    int type[6];
    double value[6];
    
    int n = 0 ; // number of transformations
    type[n] = SX ; value[n] =  r    ; n++ ;
    type[n] = SY ; value[n] =  r    ; n++ ;
    type[n] = SZ ; value[n] =  r    ; n++ ;
    type[n] = TX ; value[n] =  p[0]    ; n++ ;
    type[n] = TY ; value[n] =  p[1]    ; n++ ;
    type[n] = TZ ; value[n] =  p[2]    ; n++ ;

    D3d_make_movement_sequence_matrix(m, m_inv, n, type, value);
    D3d_mat_mult(m, VIEW, m);

    graph(sphere, m, sphere_interval, 0, M_PI*2.0, -M_PI/2.0, M_PI/2.0);
}

// hyperboloid at point p
void hyp_base(double p[3], double length, double rz, double ry) {
    double m[4][4], m_inv[4][4];
    double ab[3]; //the vector between the two points
    int type[100];
    double value[100];
    
    int n = 0 ; // number of transformations

    // make the hyperboloid thinner
    type[n] = SX ; value[n] =  0.03    ; n++ ;
    type[n] = SZ ; value[n] =  0.03    ; n++ ;

    // get it on top of the x axis
    type[n] = TY; value[n] = 1; n++;

    // fit it to the right length
    type[n] = SY ; value[n] =  length/2.0    ; n++ ;

    // rotate
    type[n] = RZ ; value[n] =  rz    ; n++ ;
    type[n] = RY ; value[n] =  ry    ; n++ ;

    // translate to point p
    type[n] = TX ; value[n] =  p[0]    ; n++ ;
    type[n] = TY ; value[n] =  p[1]    ; n++ ;
    type[n] = TZ ; value[n] =  p[2]    ; n++ ;

    D3d_make_movement_sequence_matrix(m, m_inv, n, type, value);
    D3d_mat_mult(m, VIEW, m);

    graph(hyperboloid, m, hyperboloid_interval, -1, 1, 0, M_PI*2.0);
}

void hyp_top(double length, double ry, double rz) {
    double m[4][4], m_inv[4][4];
    double ab[3]; //the vector between the two points
    int type[100];
    double value[100];
    
    int n = 0 ; // number of transformations

    // make the hyperboloid thinner
    type[n] = SX ; value[n] =  0.03    ; n++ ;
    type[n] = SZ ; value[n] =  0.03    ; n++ ;

    // get it on top of the x axis
    type[n] = TY; value[n] = 1; n++;

    // fit it to the right length
    type[n] = SY ; value[n] =  length/2.0    ; n++ ;

    // tilt
    type[n] = RZ ; value[n] =  rz; n++ ; 

    // translate to first vertex
    type[n] = TX ; value[n] =  1    ; n++ ;
    type[n] = TY ; value[n] =  0    ; n++ ;
    type[n] = TZ ; value[n] =  0    ; n++ ;

    // rotate
    type[n] = RY ; value[n] =  ry    ; n++ ;

    D3d_make_movement_sequence_matrix(m, m_inv, n, type, value);
    D3d_mat_mult(m, VIEW, m);

    graph(hyperboloid, m, hyperboloid_interval, -1, 1, 0, M_PI*2.0);
}

void render(int frame_number) {
    // ################################
    // 0. Black background
    // ################################
    set_color(0, 0, 0);
    G_clear();

    // ################################
    // 1. Set the view matrix
    // ################################
    double eye[3], coi[3], up[3];

    // set eye point
    path (frame_number, eye);

    // set center of interest
    coi[0] = 0;
    coi[1] = 0.25;
    coi[2] = 0;

    // set the up point
    path (frame_number + 1, up) ; 

    // compute the view matrix
    D3d_view(VIEW, VIEW_INV, eye, coi, up); 

    // ################################
    // 2. Set the light model
    // ################################
    double light_position_world[3];

    // set constants
    AMBIENT  = 0.2 ;
    MAX_DIFFUSE = 0.5 ;
    SPECPOW = 80 ;
    fov = 25 * M_PI/180;

    // get the light's position in world space
    path (frame_number + 10, light_position_world);

    // set the light's position in eye space
    D3d_mat_mult_pt(light_in_eye_space, VIEW, light_position_world);

    // ################################
    // 3. Build the tetrahedron vertices
    // 
    // tetrahedron side length is sqrt(3)
    // tetrahedron height is 
    // ################################
    double vertices[4][3];
    double vertex_radius = 0.08;

    // compute the locations of the base
    for (int i = 0 ; i < 3 ; i++) {
        double theta = M_PI*i*2.0/3.0;
        vertices[i][0] = cos(theta);
        vertices[i][1] = 0;
        vertices[i][2] = sin(theta);
    }    

    // set the location of the top
    vertices[3][0] = 0;
    vertices[3][1] = sqrt(2);
    vertices[3][2] = 0;

    // graph all the vertices
    set_color(0.00, 0.00, 1.00);
    for (int i=0; i<4; i++) {
        sphere_at(vertices[i], vertex_radius);
    }

    // ################################
    // 4. Build the tetrahedron edges
    // ################################
    set_color(0.00, 1.00, 1.00);

    // connect the three base vertices to each other and the top
    double rot[3] = {30, 270, 150};
    for (int i=0; i<3; i++) {
        hyp_base(vertices[i], sqrt(3), 90, rot[i]);
        hyp_top(sqrt(3), rot[i]-30, 35.26); //acos(sqrt(2/3)) == 35.26 (in degrees)
    }

    // ################################
    // 5. Build the tetrahedron center
    // ################################
    double center_radius  = 0.20;
    set_color(1.00, 0.50, 0.00);
    sphere_at(coi, center_radius);
    // set_color(1,1,1); sphere_at(coi, center_radius/3.0); //debug only

    // ################################
    // 6. connect the vertices to the center
    // ################################
    set_color(1.0, 1.0, 1.0);
    double length = sqrt(pow(.25, 2)+1);
    double angle = 90 - (atan(0.25)*180.0/M_PI);
    //the base
    for (int i=0; i<3; i++) {
        hyp_top(length, rot[i]-30, angle); //acos(sqrt(2/3)) == 35.26 (in degrees)
    }
    //and the top
    hyp_base(coi, length, 0, 0);

}

void init_zbuf() {
    for (int x=0; x<600; x++) {
        for (int y=0; y<600; y++) {
            Z_BUF[x][y] = 9999999999999;
        }
    }
}

// usage: lab2.1 [prefix] [framenumber]
int main(int argc, char const *argv[]) {
    char prefix[100], sequence_name[100];
    int start, end;


    //Read the prefix and frame number from argv
    strcpy(prefix, argv[1]); 
    start = atoi(argv[2]); 
    if (argc == 4) {
        end = atoi(argv[3]);
    } else {
        end = start;
    }

    //Initialize the Z-buffer
    init_zbuf();

    //Initialize the graphics
    G_init_graphics(600, 600);    

    for (int i=start; i<=end; i++) {
        printf("rendering frame %d...\n", i);
        // Render the image
        render(i);
        printf("done rendering frame %d\n", i);

        // Save the image
        sprintf(sequence_name, "%s%04d.xwd", prefix, i) ;
        G_save_image_to_file(sequence_name) ;
    }
    G_close() ;
    return 0;
}