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


//splat
double dot (double a[3], double b[3]) {
    return a[0]*b[0]+a[1]*b[1]+a[2]*b[2];
}

double solve (double a, double b, double c) {
    double i = (-b+sqrt(b*b - 4.0*a*c)) / 2.0*a;
    double j = (-b-sqrt(b*b - 4.0*a*c)) / 2.0*a;
    return fmax(i, j);
}

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

void render_pixel(double row, double col) {
    double p_world[3], p_object[3];
    double origin_world[3], origin_object[3];

    // set eye point for a screen pixel
    double p_eye[3] = {
        (col - 300)/(300 / tan(fov)),
        (row - 300)/(300 / tan(fov)),
        1
    };

    // set eye origin - eye is always (0,0,0) in eyespace
    double origin_eye[3] = {0, 0, 0};

    // get the world point and world origin for a screen pixel
    D3d_mat_mult_pt(p_world, VIEW_INV, p_eye);
    D3d_mat_mult_pt(origin_world, VIEW_INV, origin_eye);

    double smallest_t = -99999999999;

    int i = 0;
    // for (int i=0; i<4; i++) {
        // test sphere matrix
        double (*obj_mat)[4] = spheres[i];
        double (*obj_inv)[4] = spheres[i];

        // get the object point and object origin for a screen pixel
        D3d_mat_mult_pt(p_object, obj_inv, p_world);
        D3d_mat_mult_pt(origin_object, obj_inv, origin_world);
        // get the vector from object origin to object point
        double v_object[3] = {
            p_object[0] - origin_object[0],
            p_object[1] - origin_object[1],
            p_object[2] - origin_object[2]
        };


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
            // if (t > smallest_t) continue;
            double p[3] = {t*p_eye[0], t*p_eye[1], t*p_eye[2]}; // point in eyespace
            double n[3] = {t*p_object[0], t*p_object[1], t*p_object[2]}; // intersection point of object is also the normal vector for spheres
            double *irgb = sphere_colors[0];     // Inherent color of object
            double argb[3];                 // Actual color of object
            double s[3] = {0, 0, 0};        // "s = location of start of ray"
            D3d_mat_mult_pt(n, obj_mat, n);
            D3d_mat_mult_pt(n, VIEW, n);
            nu_light_model(irgb, s, p, n, argb);
            G_rgb(argb[0], argb[1], argb[2]);
            G_point(col, row);
        }
    // }

}

void render_frame(int frame_number) {
    G_rgb(0, 0, 0);
    G_clear();
    fov = (80-2*frame_number)*M_PI/180;
    for (double row=0; row < 600; row++) {
        for (double col=0; col < 600; col++) {
            // printf("Tracing ray through col=%f row=%f\n", col, row);
            render_pixel(row, col);
        }
    }
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
    //Set up view
    double eye[3] = {0, 0, 0};
    double coi[3] = {0, 0, 1};
    double up[3] = {0, 1, 0};
    D3d_view(VIEW, VIEW_INV, eye, coi, up); 

    for (i = s ; i <= e ; i++) {
        render_frame(i);
        sprintf(sequence_name, "%s%04d.xwd", prefix, i) ;
        // G_save_image_to_file(sequence_name) ;
        printf("done rendering frame %d\n", i);
        G_wait_key();
    }

    G_close() ;
    return 0;
}