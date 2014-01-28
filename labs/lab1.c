#include <FPT.h>
#include <D3d_matrix.h>

void circle(double p[3], double u) {
    p[0] = cos(u);
    p[1] = sin(u);
    p[3] = 0;
}

void sum4(double p[3], double u) {
    p[0] = sqrt(fabs(cos(u)))*((cos(u)<0)?-1.0:1.0); 
    p[1] = sqrt(fabs(sin(u)))*((sin(u)<0)?-1.0:1.0); 
    p[3] = 0;
}

void square(double p[3], double u) {
    p[0] = pow(cos(u), 2)*((cos(u)<0)?-1.0:1.0); 
    p[1] = pow(sin(u), 2)*((sin(u)<0)?-1.0:1.0); 
    p[3] = 0;
}

void astroid(double p[3], double u) {
    p[0] = pow(cos(u), 4)*((cos(u)<0)?-1.0:1.0); 
    p[1] = pow(sin(u), 4)*((sin(u)<0)?-1.0:1.0); 
    p[3] = 0;
}

void hyperbola(double p[3], double u) {
    p[0] = cosh(u);
    p[1] = sinh(u);
    p[3] = 0;
}

void parabola(double p[3], double u) {
    p[0] = u;
    p[1] = pow(u, 2);
    p[3] = 0;
}

void lemon(double p[3], double u) {
    p[0] = pow(cos(u), 3);
    p[1] = sin(u);
    p[3] = 0;
}

void graph(void (*func)(double[2], double), double m[4][4], double start, double end, double interval) {
    double p[3];
    for (double u=start; u<end; u+=interval) {
        (*func)(p, u);
        D3d_mat_mult_pt(p, m, p);
        G_point(p[0], p[1]);

    }
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