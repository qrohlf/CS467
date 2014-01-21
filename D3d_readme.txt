
Finish implementing the funtions,

  D3d_mat_mult_pt
  D3d_x_product
  D3d_make_movement_sequence_matrix
  D3d_view

in the file, D3d_matrix_Student.c

then compile it with the file, D3d_matrix_test01.c  

(cc -I. D3d_matrix_Student.c D3d_matrix_test01.c -lm)

and run it  (a.out > result).  Compare your output

with that in the file D3d_matrix_test01.res  

(diff result D3d_matrix_test01.res)

The files should be identical and if they are, the diff

program should output nothing.

The header file, D3d_matrix.h, shows the parameters that

each of the above four functions needs and a small description

of their purposes.  The test file should elaborate on this,

showing how to use each of these functions.





