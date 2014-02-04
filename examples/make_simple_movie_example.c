#include <FPT.h>

// seth pellegrino had this better idea

int main ()
{
  char prefix[100], sequence_name[100] ;
  int s,e,i ;
  double f ;


  printf("enter prefix name ") ;
  scanf("%s",prefix) ;

  printf("enter starting integer ") ;
  scanf("%d",&s) ;

  printf("enter ending integer ") ;
  scanf("%d",&e) ;

  /*
  printf("\n") ;
  for (i = s ; i <= e ; i++) {
    sprintf(sequence_name, "%s%04d.xwd", prefix, i) ;
    printf("%s\n",sequence_name) ;
  }
  */


  G_init_graphics(400,400) ;

  for (i = s ; i <= e ; i++) {
    G_rgb(0,0,0) ;
    G_clear() ;
    f = 1.0*i/(e - s + 1) ;
    G_rgb(1,f,0) ;
    G_fill_circle(200,200,i) ;
    sprintf(sequence_name, "%s%04d.xwd", prefix, i) ;
    G_save_image_to_file(sequence_name) ;
  }

  G_close() ;

}
