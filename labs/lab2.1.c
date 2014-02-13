#include <FPT.h>
#include <pi.h>
#include <D3d_matrix.h>
#include <limits.h>
#include <vectors.h>
#include <light_model_student.h>


// Globals
double Z_BUF[600][600];
double fov;
double R, G, B;


// Equation for a sphere
void sphere(double p[3], double u, double v) {
    p[0] = cos(u)*cos(v);
    p[1] = sin(u);
    p[2] = cos(u)*sin(v);
}

void hyperb(double p[3], double u, double v) {
    p[0] = 0;
    p[1] = 0;
    p[2] = 0;
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

void graph(void (*func)(double[3], double, double), double m[4][4], double interval) {
    double p[3];
    double irgb[3] = {R, G, B};     // Inherent color of object
    double argb[3];                 // Actual color of object
    double s[3] = {0, 0, 0};        // "s = location of start of ray"
    double n[3];                    // normal vector
    for (double u=0; u<M_PI*2.0; u+=interval) {
        for (double v= -M_PI/2.0; v<M_PI/2.0; v+=interval) {
            (*func)(p, u, v);
            D3d_mat_mult_pt(p, m, p);
            normal(func, m, u, v, n);
            nu_light_model(irgb, s, p, n, argb);
            G_rgb(argb[0], argb[1], argb[2]);

            flatten(p);
            // check the z-buffer
            // printf("previous z-val at %d %d: %f\n", (int)p[0], (int)p[1], Z_BUF[(int)p[0]][(int)p[1]]);
            // printf("current z-val: %f\n", p[2]);
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

void render(int frame_number, double interval) {
    set_color(0, 0, 0);
    G_clear();
    fov = 25.0*M_PI/180.0;
    double degrees_of_half_angle ;
    double eye[3],coi[3],up[3] ;
    double light_position[3], amb, diff, spow ;
    double view[4][4], view_inv[4][4];

    // model variables
    double xcen[4],ycen[4],zcen[4] ; // four nodes of tetrahedron
    double ccx,ccy,ccz,ccr ; // location of center of center sphere and radius
    double theta;
    double brad = 0.08 ; // radius of the 4 verts of the tetrahedron
    ccr  = 0.20 ; // the radius of the center node of the model
    


    for (int k = 0 ; k < 3 ; k++) {
        theta = 2*M_PI*k/3 ;
        xcen[k] = cos(theta) ;
        ycen[k] = 0 ;
        zcen[k] = sin(theta) ;
      }

    xcen[3] = 0 ; ycen[3] = sqrt(3)/2.0 ; zcen[3] = 0 ;
    ccx = 0 ; ccy = 1.0/4.0 ; ccz = 0 ;

    // set eye point
    eye[0] = 0; eye[1] = 0; eye[2] = 0;
    path (frame_number, eye) ;

    // set coi 
    coi[0] = (xcen[0] + xcen[1] + xcen[2])/3.0; 
    coi[1] = (ycen[0] + ycen[1] + ycen[2])/3.0; 
    coi[2] = (zcen[0] + zcen[1] + zcen[2])/3.0;

    // set up point
    up[0] = 0; up[1] = 1; up[2] = 0;
    path (frame_number + 1, up) ; 

    D3d_view(view, view_inv, eye, coi, up); 


    int Tn;
    int Ttypelist[10];
    double Tvlist[10];
    double Mat[4][4];
    double Imat[4][4];

      //////////////////////////////////////////////
      //////////////////////////////////////////////
      // build a ball and stick model of a tetrahedron
      //////////////////////////////////////////////
      //////////////////////////////////////////////
      // 3 equally spaced pts around unit circle in the xz-plane 
      // form the base
      
      for (int k = 0 ; k < 4 ; k++) {
        Tn = 0 ; // number of transformations
        Ttypelist[Tn] = SX ; Tvlist[Tn] =  brad    ; Tn++ ;
        Ttypelist[Tn] = SY ; Tvlist[Tn] =  brad    ; Tn++ ;
        Ttypelist[Tn] = SZ ; Tvlist[Tn] =  brad    ; Tn++ ;
        Ttypelist[Tn] = TX ; Tvlist[Tn] =  xcen[k]    ; Tn++ ;
        Ttypelist[Tn] = TY ; Tvlist[Tn] =  ycen[k]    ; Tn++ ;
        Ttypelist[Tn] = TZ ; Tvlist[Tn] =  zcen[k]    ; Tn++ ;

        D3d_make_movement_sequence_matrix (
            Mat,
            Imat,
            Tn,
            Ttypelist,
            Tvlist) ;
        D3d_mat_mult(Mat, view, Mat);
        set_color(0.00, 0.00, 1.00);
        graph(sphere, Mat, interval);
      }

    // CENTER BALL
    Tn = 0 ; // number of transformations
    Ttypelist[Tn] = SX ; Tvlist[Tn] =  ccr    ; Tn++ ;
    Ttypelist[Tn] = SY ; Tvlist[Tn] =  ccr    ; Tn++ ;
    Ttypelist[Tn] = SZ ; Tvlist[Tn] =  ccr    ; Tn++ ;
    Ttypelist[Tn] = TX ; Tvlist[Tn] =  ccx    ; Tn++ ;
    Ttypelist[Tn] = TY ; Tvlist[Tn] =  ccy    ; Tn++ ;
    Ttypelist[Tn] = TZ ; Tvlist[Tn] =  ccz    ; Tn++ ;

    D3d_make_movement_sequence_matrix (
        Mat,
        Imat,
        Tn,
        Ttypelist,
        Tvlist) ;
    D3d_mat_mult(Mat, view, Mat);
    set_color(0.00, 1.00, 1.00);
    graph(sphere, Mat, interval);      

}

// usage: lab2.1 [prefix] [framenumber]
int main(int argc, char const *argv[]) {
    char prefix[100], sequence_name[100] ;
    int i ;
    double f ;

    strcpy(prefix, argv[1]);
    i = atoi(argv[2]);

    

    G_init_graphics(600, 600);
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

    double res = 0.01;
    render(i, res);
    sprintf(sequence_name, "%s%04d.xwd", prefix, i) ;
    G_save_image_to_file(sequence_name) ;
    printf("done rendering frame %d\n", i);

    G_close() ;
    return 0;
}