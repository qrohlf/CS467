#include <stdio.h>
#include <stdlib.h>
#include <X11/X.h>
#include <X11/Xlib.h>



#define MAXNUMXWDMAPS 100
static  XImage xwdmap[MAXNUMXWDMAPS] ;
static  int    numxwdmaps = 0 ;


static int fgetint (FILE *fp)
{
   char *p ;
   int c[4],i ;
   int x ;
   char q ;

   for (i = 3 ; i >= 0 ; i--) {
        c[i] = fgetc(fp) ;
   }



   p = (char *) &x ;

   for (i = 0 ; i < 4 ; i++) {
        q = c[i] ;
        *p = q ;;
        p++ ;
   }

   return x ;
}







static int Set_color_into_XImage
                (XImage *p_buffer_ximage,
                 int xk, int yk,
                 double r, double g, double b)
{
 int numx, numy ;
 unsigned int red, green, blue ;
 unsigned int pixel ;
 unsigned int *pixel_array ;

 numx = p_buffer_ximage->width ;
 numy = p_buffer_ximage->height ;

 if ((xk < 0) || (xk >= numx)) return -1 ;
 if ((yk < 0) || (yk >= numy)) return -1 ;

 pixel_array =  (unsigned int *) p_buffer_ximage->data ;

 // this must be used as otherwise, p_buffer_ximage->data is viewed as 
 // an array of characters with erroneous consequences for both array subscript
 // calculation and data storage ... see below 

 red   = (unsigned int) (r*256) ;
 green = (unsigned int) (g*256) ;
 blue  = (unsigned int) (b*256) ;
 if (red >= 256)   red   = 255 ;
 if (green >= 256) green = 255 ;
 if (blue >= 256)  blue  = 255 ;
 red   &= 0xff ;   green &= 0xff ;   blue  &= 0xff ;
 pixel = (red << 16) | (green << 8) | blue ; 

 pixel_array [(numy - 1 - yk)*numx + xk]  = pixel ;

 return 1 ;
}






static int Get_color_from_XImage
                  (XImage *p_buffer_ximage,
                   int xk, int yk,
                   double rgb[3])
{
 int numx, numy ;
 unsigned int red, green, blue ;
 unsigned int pixel ;
 unsigned int *pixel_array ;

 numx = p_buffer_ximage->width ;
 numy = p_buffer_ximage->height ;

 if ((xk < 0) || (xk >= numx)) return -1 ;
 if ((yk < 0) || (yk >= numy)) return -1 ;

 pixel_array =  (unsigned int *) p_buffer_ximage->data ;
 // this must be used as otherwise, p_buffer_ximage->data is viewed as 
 // an array of characters with erroneous consequences for both array subscript
 // calculation and data storage ... see below 

 pixel =  pixel_array [(numy - 1 - yk)*numx + xk] ;
 blue  =  pixel & 0xff ;
 green =  (pixel >> 8) & 0xff ;
 red   =  (pixel >> 16) & 0xff ;

 rgb[0] = red   / 256.0 ;
 rgb[1] = green / 256.0 ;
 rgb[2] = blue  / 256.0 ;

 return 1 ; 
}










static void err()
{
  printf("Acquire_Image_From_XWD_File : error...may not be correct style of xwd file\n") ;
}







/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// Functions Below are the ones that users would normally want to call
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////




int Acquire_Image_From_XWD_File (FILE *fp)
// will return -1 on error
// otherwise returns the id number of the allocated xwd map
{
  /* unlike Recall_Image_From_XWD_File(fp), this rooutine acquires
     the data but does not render it onto the display, leaving it
     instead in the global variable, xwdmap[numxwdmaps]
     Assumes full color files .. 24 bit color

     return -1 for failure, otherwise return index of pixmap used
     ... this will aid for future reference
  */
 // assumes full color but uses full 32 bits per pixel
 int header_size, file_version, format, depth ;
 int xoffset, byte_order, bitmap_unit, bitmap_order, bitmap_pad ;
 int bits_per_pixel, bytes_per_line, visual_class ;
 int redmask, greenmask, bluemask ;
 int bitsperrgb, numentriesincolormap, numcolorstructures ;
 int windowwidth, windowheight, windowx, windowy, windowborderwidth ;
 int numbytestowrite ;
 int width,height ;
 int c, de, numbytestoread ;
 int retval ;

 header_size = fgetint(fp) ;
 file_version = fgetint(fp) ;
 format = fgetint(fp) ;
 depth = fgetint(fp) ;
 width =  fgetint(fp) ;
 height =  fgetint(fp) ;
 xoffset = fgetint(fp) ;
 byte_order = fgetint(fp) ;
 bitmap_unit = fgetint(fp) ;
 bitmap_order = fgetint(fp) ;
 bitmap_pad = fgetint(fp) ;
 bits_per_pixel = fgetint(fp) ;
 bytes_per_line = fgetint(fp) ;
 visual_class = fgetint(fp) ;
 redmask = fgetint(fp) ;
 greenmask = fgetint(fp) ;
 bluemask = fgetint(fp) ;
 bitsperrgb = fgetint(fp) ;
 numentriesincolormap = fgetint(fp) ;
 numcolorstructures = fgetint(fp) ;
 windowwidth = fgetint(fp) ;
 windowheight = fgetint(fp) ;
 windowx = fgetint(fp) ;
 windowy = fgetint(fp) ;
 windowborderwidth = fgetint(fp) ;

 // null terminated window name fleshed out to multiple of 4 bytes
 c = fgetc(fp) ; c = fgetc(fp) ; c = fgetc(fp) ; c = fgetc(fp) ;


 if (header_size != 104) { err() ; retval = -1 ; goto LLL ; }
 if (file_version != 7) { err() ; retval = -1 ; goto LLL ; }
 if (format != 2) { err() ; retval = -1 ; goto LLL ; } 
 if (depth != 24) { err() ; retval = -1 ; goto LLL ; }
 if (xoffset != 0) { err() ; retval = -1 ; goto LLL ; }
 if (byte_order != 0) { err() ; retval = -1 ; goto LLL ; }
 if (bitmap_unit != 32) { err() ; retval = -1 ; goto LLL ; }
 if (bitmap_order != 0) { err() ; retval = -1 ; goto LLL ; }
 if (bitmap_pad != 32) { err() ; retval = -1 ; goto LLL ; }
 if (bits_per_pixel != 32) { err() ; retval = -1 ; goto LLL ; }
 if (bytes_per_line != width * 4) { err() ; retval = -1 ; goto LLL ; }
 if (visual_class != 5) { err() ; retval = -1 ; goto LLL ; }
 if (redmask != 0x00ff0000) { err() ; retval = -1 ; goto LLL ; }
 if (greenmask != 0x0000ff00) { err() ; retval = -1 ; goto LLL ; }
 if (bluemask != 0x000000ff) { err() ; retval = -1 ; goto LLL ; }
 if (bitsperrgb != 24) { err() ; retval = -1 ; goto LLL ; }
 if (numentriesincolormap != 0) { err() ; retval = -1 ; goto LLL ; }
 if (numcolorstructures != 0) { err() ; retval = -1 ; goto LLL ; }
 if (windowwidth != width) { err() ; retval = -1 ; goto LLL ; }
 if (windowheight != height) { err() ; retval = -1 ; goto LLL ; }
 if (windowx != 0) { err() ; retval = -1 ; goto LLL ; }
 if (windowy != 0) { err() ; retval = -1 ; goto LLL ; }
 if (windowborderwidth != 0) { err() ; retval = -1 ; goto LLL ; }


 
 xwdmap[numxwdmaps].width = width ;
 xwdmap[numxwdmaps].height = height ;
 xwdmap[numxwdmaps].depth = depth ;
 xwdmap[numxwdmaps].xoffset = xoffset ;
 xwdmap[numxwdmaps].format = format ;
 xwdmap[numxwdmaps].bitmap_unit = bitmap_unit ;
 xwdmap[numxwdmaps].bitmap_pad = bitmap_pad ;
 xwdmap[numxwdmaps].bytes_per_line = bytes_per_line ;
 xwdmap[numxwdmaps].bits_per_pixel = bits_per_pixel ;
 xwdmap[numxwdmaps].byte_order = byte_order ;
 xwdmap[numxwdmaps].bitmap_bit_order = bitmap_order ;


 numbytestoread =   xwdmap[numxwdmaps].bytes_per_line *
                                  xwdmap[numxwdmaps].height ;

 xwdmap[numxwdmaps].data = (char *)malloc(numbytestoread) ;

 if (xwdmap[numxwdmaps].data == NULL) {
    printf("\ncan't malloc space for xwdmap\n\n");
    retval = -1 ;
    goto LLL ;
 }

 fread(xwdmap[numxwdmaps].data, numbytestoread, 1, fp) ;

 retval = numxwdmaps ;

 numxwdmaps++ ;



 LLL :

 fclose(fp) ; 

 return retval ;

}






int init_xwd_map_from_file (char *fname)
{
  FILE *fp ;
  int idnum ;

  fp = fopen(fname,"r") ;
  if (fp == NULL) {
    printf("init_xwdmap_from_file : error, can't open file %s\n",fname) ;
    return -1 ;
  }

  idnum = Acquire_Image_From_XWD_File (fp) ;
  return idnum ;
}



int get_xwd_map_color (int xwd_id_number, int x, int y,  double rgb[3])
{
  XImage *p ;
  int s ;

  if ((xwd_id_number < 0) || (xwd_id_number >= numxwdmaps)) return -1 ;
  p = &(xwdmap[xwd_id_number]) ;
  s = Get_color_from_XImage (p, x,y, rgb) ;

  return s ;
}


int get_xwd_map_dimensions (int xwd_id_number, int dimensions[2])
{
  XImage *p ;
  int s ;

  if ((xwd_id_number < 0) || (xwd_id_number >= numxwdmaps)) return -1 ;
  dimensions[0] = xwdmap[xwd_id_number].width ;
  dimensions[1] = xwdmap[xwd_id_number].height ;

  return 1 ;
}






