// lab 3 (raytracing of pancakes)
#include <FPT.h>
#include <pi.h>
#include <D3d_matrix.h>
#include <limits.h>
#include <vectors.h>
#include <math.h>
#include <light_model_student.h>
#define false 0
#define true 1


// Globals
double VIEW[4][4], VIEW_INV[4][4];
double fov;
double R, G, B;
int VERBOSE = false;

double spheres[4][4][4]; //sphere matrices
double spheres_inv[4][4][4];
double sphere_colors[4][3];

void init_scene() {
    int Tn;
    int Ttypelist[10];
    double Tvlist[10];
    double (*Mat)[4] = spheres[0];
    double (*Imat)[4] = spheres_inv[0];
    //////////////////////////////////////////////
    // unit sphere

    Tn = 0 ; // number of transformations
    Ttypelist[Tn] = SX ; Tvlist[Tn] =  100    ; Tn++ ;
    Ttypelist[Tn] = SY ; Tvlist[Tn] =   10    ; Tn++ ;
    Ttypelist[Tn] = SZ ; Tvlist[Tn] =  100    ; Tn++ ;
    Ttypelist[Tn] = RX ; Tvlist[Tn] =  -70    ; Tn++ ;
    Ttypelist[Tn] = TZ ; Tvlist[Tn] =  400    ; Tn++ ;

    D3d_make_movement_sequence_matrix (
        Mat,
        Imat,
        Tn,
        Ttypelist,
        Tvlist) ;

    sphere_colors[0][0] = 0.00;
    sphere_colors[0][1] = 0.00;
    sphere_colors[0][2] = 1.00;
    Mat = spheres[1];
    Imat = spheres_inv[1];

    ////////////////////////////////////////////////////
    // unit sphere

    Tn = 0 ; // number of transformations
    Ttypelist[Tn] = SX ; Tvlist[Tn] =   10    ; Tn++ ;
    Ttypelist[Tn] = SY ; Tvlist[Tn] =  100    ; Tn++ ;
    Ttypelist[Tn] = SZ ; Tvlist[Tn] =  100    ; Tn++ ;
    Ttypelist[Tn] = RY ; Tvlist[Tn] =    0    ; Tn++ ;
    Ttypelist[Tn] = RX ; Tvlist[Tn] =  -70    ; Tn++ ;
    Ttypelist[Tn] = TZ ; Tvlist[Tn] =  400    ; Tn++ ;

    D3d_make_movement_sequence_matrix (
        Mat,
        Imat,
        Tn,
        Ttypelist,
        Tvlist) ;


    sphere_colors[1][0] = 0.00;
    sphere_colors[1][1] = 1.00;
    sphere_colors[1][2] = 0.25;
    Mat = spheres[2];
    Imat = spheres_inv[2];

    ////////////////////////////////////////////////////
    // unit sphere

    Tn = 0 ; // number of transformations
    Ttypelist[Tn] = SX ; Tvlist[Tn] =   10    ; Tn++ ;
    Ttypelist[Tn] = SY ; Tvlist[Tn] =  100    ; Tn++ ;
    Ttypelist[Tn] = SZ ; Tvlist[Tn] =  100    ; Tn++ ;
    Ttypelist[Tn] = RY ; Tvlist[Tn] =   60    ; Tn++ ;

    Ttypelist[Tn] = RX ; Tvlist[Tn] =  -70    ; Tn++ ;
    Ttypelist[Tn] = TZ ; Tvlist[Tn] =  400    ; Tn++ ;

    D3d_make_movement_sequence_matrix (
        Mat,
        Imat,
        Tn,
        Ttypelist,
        Tvlist) ;



    sphere_colors[2][0] = 1.00;
    sphere_colors[2][1] = 1.00;
    sphere_colors[2][2] = 1.00;
    Mat = spheres[3];
    Imat = spheres_inv[3];

    ////////////////////////////////////////////////////
    // unit sphere

    Tn = 0 ; // number of transformations
    Ttypelist[Tn] = SX ; Tvlist[Tn] =   10    ; Tn++ ;
    Ttypelist[Tn] = SY ; Tvlist[Tn] =  100    ; Tn++ ;
    Ttypelist[Tn] = SZ ; Tvlist[Tn] =  100    ; Tn++ ;
    Ttypelist[Tn] = RY ; Tvlist[Tn] =  120    ; Tn++ ;
    Ttypelist[Tn] = RX ; Tvlist[Tn] =  -70    ; Tn++ ;
    Ttypelist[Tn] = TZ ; Tvlist[Tn] =  400    ; Tn++ ;

    D3d_make_movement_sequence_matrix (
        Mat,
        Imat,
        Tn,
        Ttypelist,
        Tvlist) ;


    sphere_colors[2][0] = 1.00;
    sphere_colors[2][1] = 0.00;
    sphere_colors[2][2] = 1.00;
}

void render(int frame_number) {
    G_rgb(0, 0, 0);
    G_clear();
    fov = (80-2*frame_number)*M_PI/180;
    

    ////////////////////////////////////////////////////

}

int main(int argc, char const *argv[]) {
    char prefix[100], sequence_name[100] ;
    int s,e,i ;
    double f ;

    if (argc == 4) {
        strcpy(prefix, argv[1]);
        s = atoi(argv[2]);
        e = atoi(argv[3]);
    } else {
        printf("enter prefix name ") ;
        scanf("%s",prefix) ;

        printf("enter starting integer ") ;
        scanf("%d",&s) ;

        printf("enter ending integer ") ;
        scanf("%d",&e) ;
    }

    

    G_init_graphics(600, 600);

    init_scene();

    //Set up light
    light_in_eye_space[0] = 100 ; light_in_eye_space[1] = 200 ; light_in_eye_space[2] = -50 ;
    AMBIENT  = 0.2 ;
    MAX_DIFFUSE = 0.5 ;
    SPECPOW = 80 ;

    for (i = s ; i <= e ; i++) {
        render(i);
        sprintf(sequence_name, "%s%04d.xwd", prefix, i) ;
        // G_save_image_to_file(sequence_name) ;
        printf("done rendering frame %d\n", i);
    }

    G_close() ;
    return 0;
}