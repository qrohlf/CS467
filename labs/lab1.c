#include <FPT.h>
#include <D3d_matrix.h>

// Constants

    double h = .001;

void circle(double p[3], double u) {
    p[0] = cos(u);
    p[1] = sin(u);
    p[2] = 0;
}

void sum4(double p[3], double u) {
    p[0] = sqrt(fabs(cos(u)))*((cos(u)<0)?-1.0:1.0); 
    p[1] = sqrt(fabs(sin(u)))*((sin(u)<0)?-1.0:1.0); 
    p[2] = 0;
}

void square(double p[3], double u) {
    p[0] = pow(cos(u), 2)*((cos(u)<0)?-1.0:1.0); 
    p[1] = pow(sin(u), 2)*((sin(u)<0)?-1.0:1.0); 
    p[2] = 0;
}

void astroid(double p[3], double u) {
    p[0] = pow(cos(u), 4)*((cos(u)<0)?-1.0:1.0); 
    p[1] = pow(sin(u), 4)*((sin(u)<0)?-1.0:1.0); 
    p[2] = 0;
}

void hyperbola(double p[3], double u) {
    p[0] = cosh(u);
    p[1] = sinh(u);
    p[2] = 0;
}

void parabola(double p[3], double u) {
    p[0] = u;
    p[1] = pow(u, 2);
    p[2] = 0;
}

void lemon(double p[3], double u) {
    p[0] = pow(cos(u), 3);
    p[1] = sin(u);
    p[2] = 0;
}

double magnitude(double vec[3]) {
    return sqrt(pow(vec[0], 2)+pow(vec[1], 2)+pow(vec[2], 2));
}

void unit_vector(double a[3], double b[3]) {
    double m = magnitude(a);
    b[0] = a[0]/m;
    b[1] = a[1]/m;
    b[2] = a[2]/m;
}

//Gives slope vector for function
void slope(void (*func)(double[3], double), double m[4][4], double u, double vec[3]) {
    double p[3];
    double x1, y1, x2, y2;
    (*func)(p, u-h);
    D3d_mat_mult_pt(p, m, p);
    x1 = p[0];
    y1 = p[1];
    (*func)(p, u+h);
    D3d_mat_mult_pt(p, m, p);
    x2 = p[0];
    y2 = p[1];
    vec[0] = x2 - x1;
    vec[1] = y2 - y1;
    vec[2] = 0;
}

void graph_normals(void (*func)(double[3], double), double m[4][4], double start, double end, double interval) {
    double p[3];
    double vec[3];
    double mat[4][4], minv[4][4];
    double s;
    for (double u=start+h*2; u<end-h*2; u+=interval) {
        (*func)(p, u);
        D3d_mat_mult_pt(p, m, p);
        slope(func, m, u, vec);

        //unit_vector(vec, vec);

        // D3d_make_identity(mat);
        // D3d_translate(mat, minv, -p[0], -p[1], -p[2]);
        // D3d_rotate_z(mat, minv, -M_PI/2.0);
        // D3d_translate(mat, minv, p[0], p[1], p[2]);
        // D3d_mat_mult_pt(vec, mat, vec);

        unit_vector(vec, vec);

        
        G_line(p[0], p[1], p[0]+vec[1]*30, p[1]-vec[0]*30);
    }
}

void graph(void (*func)(double[3], double), double m[4][4], double start, double end, double interval) {
    double p[3];
    for (double u=start; u<end; u+=interval) {
        (*func)(p, u);
        D3d_mat_mult_pt(p, m, p);
        G_point(p[0], p[1]);
    }
    graph_normals(func, m, start, end, interval*20);
}

int main(int argc, char const *argv[]) {
    G_init_graphics(800, 800);
    G_rgb(0, 0, 0);
    G_clear();
    G_rgb(1, 1, 1);
    //circle();
    double m[4][4], minv[4][4] ;
    int num ;
    int tlist[100] ;
    double plist[100] ;

  //////////////////////////////////////////////
  //circle 
    tlist[num] = SX ; plist[num] = 50 ; num++ ;
    tlist[num] = SY ; plist[num] = 100 ; num++ ;
    tlist[num] = TX ; plist[num] =  300 ; num++ ;
    tlist[num] = TY ; plist[num] =  500 ; num++ ;

    D3d_make_movement_sequence_matrix(m,minv, num, tlist, plist) ;
    graph(&circle, m, 0.25*M_PI, 1.50*M_PI, 0.01);

  //////////////////////////////////////////////
  //sum4 
    num = 0;
    tlist[num] = SX ; plist[num] = 30 ; num++ ;
    tlist[num] = SY ; plist[num] = 60 ; num++ ;
    tlist[num] = TX ; plist[num] =  300 ; num++ ;
    tlist[num] = TY ; plist[num] =  300 ; num++ ;

    D3d_make_movement_sequence_matrix(m,minv, num, tlist, plist) ;
    graph(&sum4, m, 0.50*M_PI, 1.75*M_PI, 0.01);


  //////////////////////////////////////////////
  //square
    num = 0;
    tlist[num] = SX ; plist[num] = 150 ; num++ ;
    tlist[num] = SY ; plist[num] = 100 ; num++ ;
    tlist[num] = TX ; plist[num] =  500 ; num++ ;
    tlist[num] = TY ; plist[num] =  500 ; num++ ;

    D3d_make_movement_sequence_matrix(m,minv, num, tlist, plist) ;
    graph(&square, m, 0, 2.0*M_PI, 0.01);

  //////////////////////////////////////////////
  //astroid
    num = 0;
    tlist[num] = SX ; plist[num] = 80 ; num++ ;
    tlist[num] = SY ; plist[num] = 40 ; num++ ;
    tlist[num] = RZ ; plist[num] = 45 ; num++ ;
    tlist[num] = TX ; plist[num] =  500 ; num++ ;
    tlist[num] = TY ; plist[num] =  300 ; num++ ;

    D3d_make_movement_sequence_matrix(m,minv, num, tlist, plist) ;
    graph(&astroid, m, 0, 2.0*M_PI, 0.01);

  //////////////////////////////////////////////
  //hyperbola  {right branch}
    num = 0;
    tlist[num] = NY ; plist[num] =     0.0  ; num++ ;
    tlist[num] = SX ; plist[num] =   100.0  ; num++ ;
    tlist[num] = SY ; plist[num] =   100.0  ; num++ ;
    tlist[num] = RZ ; plist[num] =     0.0  ; num++ ;
    tlist[num] = TX ; plist[num] =   250.0  ; num++ ;
    tlist[num] = TY ; plist[num] =   250.0  ; num++ ;

    D3d_make_movement_sequence_matrix(m,minv, num, tlist, plist) ;
    graph(&hyperbola, m, -1, 2, 0.01);

  //////////////////////////////////////////////
  //parabola
    num = 0;
    tlist[num] = SX ; plist[num] =   150.0  ; num++ ;
    tlist[num] = SY ; plist[num] =   50.0  ; num++ ;
    tlist[num] = RZ ; plist[num] =     60.0  ; num++ ;
    tlist[num] = TX ; plist[num] =   250.0  ; num++ ;
    tlist[num] = TY ; plist[num] =   250.0  ; num++ ;

    D3d_make_movement_sequence_matrix(m,minv, num, tlist, plist) ;
    graph(&parabola, m, -1, 2, 0.01);

  //////////////////////////////////////////////
  //lemon
    num = 0;
    tlist[num] = SX ; plist[num] = 150 ; num++ ;
    tlist[num] = SY ; plist[num] = 150 ; num++ ;
    tlist[num] = RZ ; plist[num] = 60 ; num++ ;
    tlist[num] = TX ; plist[num] =  600 ; num++ ;
    tlist[num] = TY ; plist[num] =  150 ; num++ ;

    D3d_make_movement_sequence_matrix(m,minv, num, tlist, plist) ;
    graph(&lemon, m, 0, 2.0*M_PI, 0.01);


    G_wait_key();
    return 0;
}